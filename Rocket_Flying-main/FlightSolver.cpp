#include "FlightSolver.h"

#include "Constants.h"

namespace {
constexpr auto components_ratio = 4.5;
constexpr auto first_block_length = 42.9;
constexpr auto second_block_length = 10.5;
constexpr auto second_stage_length = 21.5;
constexpr auto extra_mass = 33200; /*2200*/
}

FlightSolver::FlightSolver(double (&kalph_)[3], double (&kpeng_)[2])
    : FlightInit(kalph_, kpeng_)
 {

    std::copy(std::begin(kalph_), std::end(kalph_), std::begin(kalph));
    std::copy(std::begin(kpeng_), std::end(kpeng_), std::begin(kpeng));

    file1.setFileName("C:/Users/smeta/OneDrive/Рабочий стол/M/BalDyn/output/air.txt");
    file1.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file1.resize(0);

    calculate_initial_values(kpeng);
    M.MCI_f(0, h, mpn, D, mb[0], mb[1], s[0], s[1], peng[0], peng[1]);
    calculate_length();
    calculate_mass_parameters();
    calculate_area_and_inertia();
    initialize_time_parameters();
}

FlightSolver::~FlightSolver()
{
    file1.close();
}

void FlightSolver::calculate_initial_values(double (&kpeng)[2]) {
    peng[0] = kpeng[0] * constants::acceleration_of_gravity * (mpn + mb[0] + mb[1]);
    peng[1] = kpeng[1] * constants::acceleration_of_gravity * (mpn + mb[1]);

    m_furet = extra_mass;
    m_reC = m_furet / components_ratio;
    m_reO = m_furet * (components_ratio - 1) / components_ratio;
    M_Rocket = mpn;
    fir->m_t = M_Rocket;
    sec->m_t = M_Rocket;
    Smid = M_PI * pow(D, 2) / 4;
    fir->V = 0;
    sec->V = 0;
    count = 0;
}

void FlightSolver::calculate_length() {
    // Определение габаритов ракеты
    Lmax = M.get_length();
    L1 = first_block_length;
    L2 = second_block_length;
}

void FlightSolver::calculate_mass_parameters() {
    for (int i = 0; i <= 1; i++) {
        m_fuel[i] = mb[i] * (s[i] - 1) / s[i];
        m_O[i] = m_fuel[i] * Ratio / (Ratio + 1);
        m_C[i] = m_fuel[i] / (Ratio + 1);
        m_dry[i] = mb[i] - m_fuel[i];
    }
    m_dry[0] -= m_furet;
    M_Rocket += m_fuel[0] + m_dry[0] + m_fuel[1] + m_dry[1] + m_furet;
    m_dry[1] += zap;

    M_stage[0] = M_Rocket;
    M_stage[1] = M_Rocket - mb[0];
}

void FlightSolver::calculate_area_and_inertia() {
    fir->S_dry[0] = M.fun_S(M.K[6], M.K[12], m_dry[0]);
    fir->S_dry[1] = M.fun_S(M.K[1], M.K[6], m_dry[1]);
    sec->S_dry[0] = M.fun_S(M.K[6] - second_stage_length, M.K[12] - second_stage_length, m_dry[0]);
    sec->S_dry[1] = M.fun_S(M.K[1] - second_stage_length, M.K[6] - second_stage_length, m_dry[1]);

    // Calculate areas for oxygen and carbon
    S_o[0] = M.fun_S(M.K[8], M.K[9], m_O[0]);
    S_c[0] = M.fun_S(M.K[10], M.K[11], m_C[0]);
    S_o[1] = M.fun_S(M.K[3], M.K[4], m_O[1]);
    S_c[1] = M.fun_S(M.K[5], M.K[6], m_C[1]);

    fir->S_reO = M.fun_S(M.K[9], M.K[10], m_reO);
    fir->S_reC = M.fun_S(M.K[11], M.K[13], m_reC);
    sec->S_reO = M.fun_S(M.K[9] - second_stage_length, M.K[10] - second_stage_length, m_reO);
    sec->S_reC = M.fun_S(M.K[11] - second_stage_length, M.K[13] - second_stage_length, m_reC);

    fir->Ssumm = M.get_SGO() + fir->S_dry[0] + fir->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + fir->S_reO + fir->S_reC;

    calculate_inertia();
}

void FlightSolver::calculate_inertia() {
    fir->I_dry[0] = M.fun_I(M.K[6], M.K[12], m_dry[0], D);
    fir->I_dry[1] = M.fun_I(M.K[1], M.K[6], m_dry[1], D);
    sec->I_dry[0] = M.fun_I(M.K[6] - second_stage_length, M.K[12] - second_stage_length, m_dry[0], D);

    I_o[0] = M.fun_I(M.K[8], M.K[9], m_O[0], D);
    I_c[0] = M.fun_I(M.K[10], M.K[11], m_C[0], D);
    I_o[1] = M.fun_I(M.K[3], M.K[4], m_O[1], D);
    I_c[1] = M.fun_I(M.K[5], M.K[6], m_C[1], D);

    fir->I_reO = M.fun_I(M.K[9], M.K[10], m_reO, D);
    fir->I_reC = M.fun_I(M.K[11], M.K[13], m_reC, D);
    sec->I_reO = M.fun_I(M.K[9] - second_stage_length, M.K[10] - second_stage_length, m_reO, D);
    sec->I_reC = M.fun_I(M.K[11] - second_stage_length, M.K[13] - second_stage_length, m_reC, D);

    fir->Isumm = M.get_IGO() + fir->I_dry[0] + fir->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + fir->I_reO + fir->I_reC - M_Rocket * pow(fir->gl_c, 2);
    Iz = fir->Isumm;
    Ix = M_Rocket * pow(D / 2, 2);
    Izmax = Iz;
    Ixmax = Ix;
}

void FlightSolver::initialize_time_parameters() {
    std::cout << "set start flight parameters\n";

    T_fuel[0] = m_fuel[0]/(peng [0]/Imp[0]);
    T_stage [0] = T_fuel [0] + T_sep [0];
    T_fuel[1] = m_fuel[1]/(peng [1]/Imp[1]);
    T_stage [1] = T_fuel [1] + T_sep [1];
    // ИД итеративного расчета
    fir->m_t = M_Rocket;
    sec->m_t = M_Rocket;
    fir->anY = M_PI/2;
    sec->anY = M_PI/2;
    //double p_ground = 101325;
    sec->tY = 1;
    //
    // Итеративный расчет
    H1.clear();
    H2.clear();
    xn.clear();
    count = 0;
    fir->tY = 0;
    sec->tX = 0;
    d_O[1] = 0;
    T[0] = T_fuel[0];
    T[1] = T_fuel[0] + T_sep[0];
    T[2] = T_fuel[0] + T_sep[0]+T_fuel[1];
    T[3] = T_fuel[0] + T_sep[0]+T_fuel[1] + T_sep[1];
}


void FlightSolver::pitch_calculations()
{
    QTextStream out1(&file1);
    do
    {
        Airforce Qus_1 (Mah_1);
        Airforce Qus_2 (Mah_2);

        focus F;

        atmosphere Atm_1 (fir->tY);
        atmosphere Atm_2 (sec->tY);
        eastwind W1 (fir->tY/1000);
        eastwind W2 (sec->tY/1000);


        // Участок работы ДУ-1
        if (time<=T[0])
        {
            //if (m_t > M_Rocket-onefu )
            //{
            fir->Peng_t = peng[0];
            sec->Peng_t = peng[0];
            sec->Peng_control = sec->Peng_t/2;
            //+ (p_ground - P.get_pressure()) * Smid/2;
            Imp_t = Imp[0];
            CF = fir->Peng_t/Imp_t;
            fir-> m_t = m_fuel[0]+m_fuel[1]+m_dry[0]+m_dry[1]+ m_reC + m_reO +mpn;
            sec->m_t = m_fuel[0]+m_fuel[1]+m_dry[0]+m_dry[1]+ m_reC + m_reO +mpn;
            m_O[0] = Ratio*m_fuel[0]/(Ratio+1);
            m_C[0] = m_fuel[0]/(Ratio+1);
            m_fuel[0] -= CF*h;
            d_O[0] += Ratio*CF*h/(1100*Smid)/(Ratio+1);
            d_C[0] += CF*h/(440*Smid)/(Ratio+1);
            S_o[0] = M.fun_S (M.K[8]+d_O[0], M.K[9], m_O[0]);
            S_c[0] = M.fun_S (M.K[10]+d_C[0], M.K[11], m_C[0]);
            // fir в sec->e не ошибка, а условность СК
            fir->Ssumm  = M.get_SGO() + fir->S_dry[0] + fir->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + fir->S_reO + fir->S_reC;
            sec->Ssumm = M.get_SGO() + fir->S_dry[0] + fir->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + fir->S_reO + fir->S_reC;
            fir->gl_c = fir->Ssumm/fir->m_t;
            sec->gl_c = sec->Ssumm/sec->m_t;

            I_o[0] = M.fun_I (M.K[8]+d_O[0], M.K[9], m_O[0], D);
            I_c[0] = M.fun_I (M.K[10]+d_C[0], M.K[11], m_C[0], D);
            fir->Isumm  = M.get_IGO() + fir->I_dry[0] + fir->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + fir->I_reC +fir->I_reO - fir->m_t*pow (fir->gl_c,2);

            sec->Isumm = M.get_IGO() + fir->I_dry[0] + fir->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + fir->I_reC +fir->I_reO - sec->m_t*pow(sec->gl_c,2);
            Ix = fir->m_t * pow(D/2, 2);
            //}
            //else T_fuel[0] = time;
            //if (abs(m_t - (M_Rocket-m_fuel[0])) < 100) T_fuel[0] = time;
            fir->L  = Lmax;
            sec->L = Lmax;
            Ott_1 = fir->anY;
            H_1 = fir->tY/1000;
            CILCON = 12.88;
            dep = count*h;
            sec->focus = F.Focus(Mah_1, D, M.get_lengo(), M.get_wgo(), M.get_CIL(), CILCON);
            X_oneC = sec->gl_c - sec->focus;
            X_twoC = sec->L - sec->gl_c;
        }

        // Участок разделения 1-2
        if (time >T[0] && time<=T[1])
        {
            fir->Peng_t = 0;
            sec->Peng_t = 0;
            sec->Peng_control = sec->Peng_t/2;
            Imp_t = 0;
            CF = 0;
            fir->m_t = m_fuel[1]+m_fuel[0]+m_dry[1]+mpn;
            sec->m_t = m_dry[0] + m_reC + m_reO;
            fir->Ssumm  = M.get_SGO() + fir->S_dry[1]+ S_o[0] + S_c[0] + S_o[1] + S_c[1];
            sec->Ssumm = sec->S_dry[0] + sec->S_reC + sec->S_reO;
            fir->gl_c = fir->Ssumm/fir->m_t;
            sec->gl_c = sec->Ssumm/sec->m_t;
            fir->L = Lmax - L1;
            sec->L = L1;
            CILCON = 3.42;
            X_oneC = 0;
            X_twoC = 0;
        }

        // Участок работы ДУ-2
        if (time>T[1] && time<=T[2])
        {
            fir->Peng_t = peng[1];
            sec->Peng_t = 0;
            sec->Peng_control = sec->Peng_t/2;
            Imp_t = Imp[1];
            CF = fir->Peng_t/Imp_t;
            fir->m_t = m_fuel[1]+m_fuel[0]+m_dry[1]+mpn;
            sec->m_t = m_dry[0] + m_reC + m_reO;

            m_O[1] = Ratio*m_fuel[1]/(Ratio+1);
            m_C[1] = 1*m_fuel[1]/(Ratio+1);

            m_fuel[1] -= CF*h;
            d_O[1] += CF*h *Ratio/(1100*Smid)/(Ratio+1);
            d_C[1] += CF*h /(440*Smid)/(Ratio+1);
            S_o[1] = M.fun_S (M.K[3]+d_O[1], M.K[4], m_O[1]);
            S_c[1] = M.fun_S (M.K[5]+d_C[1], M.K[6], m_C[1]);
            fir->Ssumm = M.get_SGO() + fir->S_dry[1]+ S_o[0] + S_c[0] + S_o[1] + S_c[1];

            // std::cout << CF*h *Ratio/(1100*Smid)/(Ratio+1) << CF << std::endl;

            sec->Ssumm = sec->S_dry[0] + sec->S_reC + sec->S_reO;
            fir->gl_c = fir->Ssumm/fir->m_t;
            sec->gl_c = sec->Ssumm/sec->m_t;
            fir->gl_c = fir->gl_c/2;
            sec->gl_c = sec->gl_c/2;
            I_o[1] = M.fun_I (M.K[3]+d_O[1], M.K[4], m_O[1], D);
            I_c[1] = M.fun_I (M.K[5]+d_C[1], M.K[6], m_C[1], D);
            fir->Isumm = M.get_IGO() +fir->I_dry[1]+ I_o[0] + I_c[0] + I_o[1] + I_c[1]- fir->m_t*pow(fir->gl_c,2);
            sec->Isumm = sec->I_dry[0] + sec->I_reC + sec->I_reO - sec->m_t*pow(sec->gl_c,2);
            fir->Isumm = fir->Isumm;
            sec->Isumm = sec->Isumm;
            Ix = fir->m_t * pow(D/2, 2);
            fir->L = Lmax - L1;
            sec->L = L1;

            Ott_2 = fir->anY;
            CILCON = 3.42;
            X_oneC = 0;
            X_twoC = 0;
        }
        // Участок разделения 2-ПН
        if (time>T[2] && time<=T[3])
        {
            fir->Peng_t = 0;
            sec->Peng_t = 0;
            sec->Peng_control = sec->Peng_t/2;
            Imp_t = 0;
            CF = 0;
            fir->m_t = m_dry[1]+mpn;
            sec->m_t = m_dry[0] + m_reC + m_reO;
            fir->Ssumm = M.get_SGO() + fir->S_dry[1]+ S_o[0] + S_c[0] + S_o[1] + S_c[1] ;
            sec->Ssumm = sec->S_dry[0] + sec->S_reC + sec->S_reO;
            fir->gl_c = fir->Ssumm/fir->m_t;
            sec->gl_c = sec->Ssumm/sec->m_t;
            fir->L = Lmax - L1 - L2;
            sec->L = L1;

            CILCON = 1.4;
            X_oneC = 0;
            X_twoC = 0;
        }
        // Участок полета ПН
        if (time>T[3])
        {
            fir->Peng_t = 0;
            sec->Peng_t = 0;
            sec->Peng_control = sec->Peng_t/2;
            Imp_t = 0;
            CF = 0;
            fir->m_t = mpn;
            sec->m_t = m_dry[0];
            fir->Ssumm = M.get_SGO() + S_o[0] + S_c[0] + S_o[1] + S_c[1];
            sec->Ssumm = sec->S_dry[0] + sec->S_reC + sec->S_reO;
            fir->gl_c = fir->Ssumm/fir->m_t;
            fir->L = Lmax - L1 - L2;
            sec->L = L1;
            CILCON = 1.4;
            X_oneC = 0;
            X_twoC = 0;
        }
        //Участок возвращения

        if ((time>k1 && time<k2) || (time>k3 && time<k4))
        {
            if (m_furet>=0)
            {
                if (time>k1 && time<k2) (sec->Peng_t = kk1*peng[0]);
                if (time>k3 && time<k4) (sec->Peng_t = kk2*peng[0]);
                sec->Peng_control = sec->Peng_t;
                Imp_t = Imp[0];
                CF = sec->Peng_t/Imp_t;
                m_reC -= CF*h * 1/(3.5+1);
                m_reO -= CF*h * 3.5/(3.5+1);
                m_furet = m_reC + m_reO;
                sec->m_t = m_dry[0] + m_reC + m_reO;
                deo += CF*h *Ratio/(1100*Smid)/(Ratio+1);
                dec += CF*h /(440*Smid)/(Ratio+1);
                sec->S_reO = M.fun_S (M.K[9 ]-21.5 + deo, M.K[10]-21.5, m_reO);
                sec->S_reC = M.fun_S (M.K[11]-21.5 + dec, M.K[13]-21.5, m_reC);
                sec->Ssumm = sec->S_dry[0] + sec->S_reC + sec->S_reO;
                sec->gl_c = sec->Ssumm/sec->m_t;
                sec->I_reO = M.fun_I (M.K[9 ]-21.5 + deo, M.K[10]-21.5, m_reO, D);
                sec->I_reC = M.fun_I (M.K[11]-21.5 + dec, M.K[13]-21.5, m_reC, D);
                sec->Isumm = sec->I_dry[0] + sec->I_reC + sec->I_reO - sec->m_t*pow(sec->gl_c,2);
                sec->Isumm = sec->Isumm;
                sec->L = L1;
                sec->focus = 0.7*sec->L;
                X_oneC = sec->gl_c - sec->focus;
                X_twoC = sec->L - sec->gl_c;
            };


        }

        // Программа угла атаки
        alpha alph_1 (fir->V,  kalph [1], kalph [2], time, T_stage [0], 0, k2, k3);
        alpha alph_2 (sec->V, kalph [1],              0, time, 200, 180, k2, k3);

        // Учет параметров атмосферы
        HSP_p_1 = HSP_1;
        HSP_1 = (Atm_1.get_density()/2)*pow(fir->V,2);
        HSP_p_2 = HSP_2;
        HSP_2 = (Atm_2.get_density()/2)*pow(sec->V,2);
        Mah_1 = fir->V/Atm_1.get_SV();
        Mah_2 = sec->V/Atm_2.get_SV();

        fir->focus = F.Focus(Mah_1, D, M.get_lengo(), M.get_wgo(), M.get_CIL(), CILCON);
        if (time<T_stage[0]) {CX_1=Qus_1.GetCX();  } else {CX_1=0;  }
        if (time<T_stage[0]) {CY_1=Qus_1.GetCY();  } else {CY_1=0;  }
        CX_2=Qus_2.GetCX();
        CY_2=Qus_2.GetCY();
        bpr = ((Atm_1.get_density()/2*pow(fir->V,2))*Smid*fir->L*CY_1*fir->alpha)/(fir->Peng_t*(fir->L-fir->gl_c));

        equations B_1 (Atm_1.get_density(), Smid, Atm_1.get_AOG(), fir->m_t, CX_1, CY_1, fir->Peng_t, alph_1.A(), Wind1);
        equations B_2 (Atm_2.get_density(), Smid, Atm_2.get_AOG(), sec->m_t, CX_2, CY_2, sec->Peng_t, alph_2.A(), Wind2);

        //dV = B_1.fdV(fir->V, fir->anY);
        dN = B_1.fdN(fir->tY, fir->V, fir->anY);

        Ott = fir->anY-Na;
        pitch_angle = Ott-fir->alpha/57.3;

        fir->tX += h * (fir->V* cos(fir->anY)+X1)/2;
        sec->tX += h * (sec->V* cos(sec->anY)+X2)/2;

        X1 = fir->V* cos(fir->anY);
        X2 = sec->V* cos(sec->anY);


        Wind1 = W1.WSol();
        Wind2 = W2.WSol();
        out1 << Wind2 << "\t" << sec->V << "\n";

        if (time<120 &&  HSP_1<HSP_p_1 && e<1)
        {

            MHSP_1 = HSP_1;
            VHSP_1 = fir->V;
            e+=1;
        }

        if (time<120 &&  HSP_2<HSP_p_2 && e<1)
        {

            MHSP_2 = HSP_2;
            VHSP_2 = sec->V;
            e+=1;
        }
        //  if  (HSP_2>90000)  {HSP_2=HSP_1;}
        time+=h;
        Na  += dN*h;
        if (fir->m_t>mpn)
        {

            //double me = fir->anY;

            fir->tY += fir->V* sin(fir->anY) *h;

            fir->V   += (B_1.fdV(fir->V, fir->anY) + V1)/2*h;
            fir->anY += (B_1.fdY(fir->tY, fir->V, fir->anY)+Y1)/2*h;



            H11 = fir->V* sin(fir->anY);
            V1 = B_1.fdV(fir->V, fir->anY);
            Y1 = B_1.fdY(fir->tY, fir->V, fir->anY);


            std::cout << zXY/1000  << std::endl;
            VX += h*B_1.dVX(velXY, Ott, Na);
            VY += h*B_1.dVY(velXY, Ott, Na);
            VZ += h*B_1.dVZ(velXY, Ott, Na);
            velXY = sqrt(VX*VX+VY*VY+VZ*VZ);
            trjXY = acos(VX/velXY);
            xXY += h*VX * cos(fir->anY) / cos(Ott);
            yXY += h*VY * sin(fir->anY) / sin(Ott);
            zXY += h*VZ;
            norXY = atan(xXY/(6371000+yXY));
        }

        if (time >T_fuel[0])
        {
            sec->tY += (sec->V* sin(sec->anY)+H22)/2*h;
            sec->V  += (B_2.returndV(sec->V, sec->anY)+V2)/2*h; //return
            sec->anY  += (B_2.returndY(sec->tY, sec->V, sec->anY)+Y2)/2*h;  //return

            V2 = B_2.returndV(sec->V, sec->anY);
            Y2 = B_2.returndY(sec->tY, sec->V, sec->anY);
            H22 = sec->V* sin(sec->anY);

        }
        else
        {
            sec->tY += (sec->V* sin(sec->anY)+H22)/2*h;
            sec->V  += (B_2.fdV(sec->V, sec->anY)+V2)/2*h;
            sec->anY  += (B_2.fdY(sec->tY, sec->V, sec->anY)+Y2)/2*h;

            V2 = B_2.fdV(sec->V, sec->anY);
            Y2 = B_2.fdY(sec->tY, sec->V, sec->anY);
            H22 = sec->V* sin(sec->anY);
        }


        xn.push_back(time);
        yu_1.push_back(HSP_1);
        yu_2.push_back(HSP_2);
        center_1.push_back(fir->gl_c);
        center_2.push_back(sec->gl_c);
        v_1.push_back(fir->V);
        v_2.push_back(sec->V);
        sinn.push_back(fir->Ssumm);
        jinn.push_back(fir->Isumm);
        jinn2.push_back(sec->Isumm);
        CM.push_back(fir->Ssumm/fir->m_t);
        mass_1.push_back(fir->m_t);
        mass_2.push_back(sec->m_t);
        Long_1.push_back(fir->tX/1000);
        Long_2.push_back(sec->tX/1000);
        vec_wind1.push_back(Wind1);
        vec_wind2.push_back(Wind2);
        H1.push_back(fir->tY/1000);
        H2.push_back(sec->tY/1000);
        angle.push_back(pitch_angle*57.3);
        b1.push_back(HSP_1*Smid*CX_1);
        b2.push_back(HSP_2*Smid*CX_2);
        lin.push_back(Ix);
        ALI_1.push_back(alph_1.A());
        ALI_2.push_back(alph_2.A());
        res.push_back(sec->Peng_t/(sec->m_t*Atm_2.get_AOG()));
        TET_1.push_back(fir->anY*57.3);
        TET_2.push_back(sec->anY*57.3);
        be.push_back(bpr*57.3);
        pi.push_back(pitch_angle*57.3);
        P1.push_back(fir->Peng_t);
        P2.push_back(sec->Peng_t);
        f1.push_back(fir->focus);
        Lon.push_back(fir->Peng_t/(fir->m_t*Atm_1.get_AOG()));
        Lonre.push_back(sec->Peng_t/(sec->m_t*Atm_2.get_AOG()));
        pc2.push_back(sec->Peng_control);
        cy2.push_back(CY_2);
        dyn1.push_back(X_oneC);
        dyn2.push_back(X_twoC);
        lenght_R.push_back(sec->L);
        amax = alph_1.A();
        count+=1;
        MaxTime = count*h;
    }
    while (sec->tY>0 && sec->V>0);
}
