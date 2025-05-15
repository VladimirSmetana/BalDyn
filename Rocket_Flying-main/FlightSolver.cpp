#include "FlightSolver.h"

#include "focus.h"
#include "equations.h"
#include "mass.h"
#include "qdebug.h"
#include "Constants.h"

#include <QDebug>


FlightSolver::FlightSolver(double (&kalph_)[3],
                           double (&kpeng_)[2])
    : FlightInit(kalph_, kpeng_)
 {

    std::copy(std::begin(kalph_), std::end(kalph_), std::begin(kalph));
    std::copy(std::begin(kpeng_), std::end(kpeng_), std::begin(kpeng));

    file1.setFileName("C:/Users/smeta/OneDrive/Рабочий стол/M/BalDyn/output/air.txt");
    file1.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file1.resize(0);
}

FlightSolver::~FlightSolver()
{
    file1.close();
}

void FlightSolver::pitch_calculations()
{
    QTextStream out1(&file1);

    qDebug() << "start of flight";
    do
    {
        Airforce Qus_1 (Mah_1);
        Airforce Qus_2 (Mah_2);

        focus F;

        atmosphere Atm_1 (insertion->tY);
        atmosphere Atm_2 (landing->tY);
        eastwind W1 (insertion->tY/1000);
        eastwind W2 (landing->tY/1000);


        // Участок работы ДУ-1
        if (time<=T[0])
        {
            insertion->Peng_t = peng[0];
            landing->Peng_t = peng[0];
            landing->Peng_control = landing->Peng_t/2;
            Imp_t = Imp[0];
            CF = insertion->Peng_t/Imp_t;
            insertion-> m_t = m_fuel[0]+m_fuel[1]+m_dry[0]+m_dry[1]+ m_reC + m_reO +mpn;
            landing->m_t = m_fuel[0]+m_fuel[1]+m_dry[0]+m_dry[1]+ m_reC + m_reO +mpn;
            m_O[0] = Ratio*m_fuel[0]/(Ratio+1);
            m_C[0] = m_fuel[0]/(Ratio+1);
            m_fuel[0] -= CF*h;
            d_O[0] += Ratio*CF*h/(constants::density::liquid_oxygen*Smid)/(Ratio+1);
            d_C[0] += CF*h/(constants::density::kerosene*Smid)/(Ratio+1);
            S_o[0] = M.fun_S (M.K[8]+d_O[0], M.K[9], m_O[0]);
            S_c[0] = M.fun_S (M.K[10]+d_C[0], M.K[11], m_C[0]);
            // fir в landing->e не ошибка, а условность СК
            insertion->Ssumm  = M.get_SGO() + insertion->S_dry[0] + insertion->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + insertion->S_reO + insertion->S_reC;
            landing->Ssumm = M.get_SGO() + insertion->S_dry[0] + insertion->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + insertion->S_reO + insertion->S_reC;
            insertion->gl_c = insertion->Ssumm/insertion->m_t;
            landing->gl_c = landing->Ssumm/landing->m_t;

            I_o[0] = M.fun_I (M.K[8]+d_O[0], M.K[9], m_O[0], D);
            I_c[0] = M.fun_I (M.K[10]+d_C[0], M.K[11], m_C[0], D);
            insertion->Isumm  = M.get_IGO() + insertion->I_dry[0] + insertion->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + insertion->I_reC +insertion->I_reO - insertion->m_t*pow (insertion->gl_c,2);

            landing->Isumm = M.get_IGO() + insertion->I_dry[0] + insertion->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + insertion->I_reC +insertion->I_reO - landing->m_t*pow(landing->gl_c,2);
            Ix = insertion->m_t * pow(D/2, 2);
            insertion->L  = Lmax;
            landing->L = Lmax;
            Ott_1 = insertion->anY;
            H_1 = insertion->tY/1000;
            CILCON = 12.88;
            dep = count*h;
            landing->focus = F.Focus(Mah_1, D, M.get_lengo(), M.get_wgo(), M.get_CIL(), CILCON);
            X_oneC = landing->gl_c - landing->focus;
            X_twoC = landing->L - landing->gl_c;
        }

        // Участок разделения 1-2
        if (time >T[0] && time<=T[1])
        {
            insertion->Peng_t = 0;
            landing->Peng_t = 0;
            landing->Peng_control = landing->Peng_t/2;
            Imp_t = 0;
            CF = 0;
            insertion->m_t = m_fuel[1]+m_fuel[0]+m_dry[1]+mpn;
            landing->m_t = m_dry[0] + m_reC + m_reO;
            insertion->Ssumm  = M.get_SGO() + insertion->S_dry[1]+ S_o[0] + S_c[0] + S_o[1] + S_c[1];
            landing->Ssumm = landing->S_dry[0] + landing->S_reC + landing->S_reO;
            insertion->gl_c = insertion->Ssumm/insertion->m_t;
            landing->gl_c = landing->Ssumm/landing->m_t;
            insertion->L = Lmax - L1;
            landing->L = L1;
            CILCON = 3.42;
            X_oneC = 0;
            X_twoC = 0;
        }

        // Участок работы ДУ-2
        if (time>T[1] && time<=T[2])
        {
            insertion->Peng_t = peng[1];
            landing->Peng_t = 0;
            landing->Peng_control = landing->Peng_t/2;
            Imp_t = Imp[1];
            CF = insertion->Peng_t/Imp_t;
            insertion->m_t = m_fuel[1]+m_fuel[0]+m_dry[1]+mpn;
            landing->m_t = m_dry[0] + m_reC + m_reO;

            m_O[1] = Ratio*m_fuel[1]/(Ratio+1);
            m_C[1] = 1*m_fuel[1]/(Ratio+1);

            m_fuel[1] -= CF*h;
            d_O[1] += CF*h *Ratio/(constants::density::liquid_oxygen*Smid)/(Ratio+1);
            d_C[1] += CF*h /(constants::density::kerosene*Smid)/(Ratio+1);
            S_o[1] = M.fun_S (M.K[3]+d_O[1], M.K[4], m_O[1]);
            S_c[1] = M.fun_S (M.K[5]+d_C[1], M.K[6], m_C[1]);
            insertion->Ssumm = M.get_SGO() + insertion->S_dry[1]+ S_o[0] + S_c[0] + S_o[1] + S_c[1];

            // std::cout << CF*h *Ratio/(constants::density::liquid_oxygen*Smid)/(Ratio+1) << CF << std::endl;

            landing->Ssumm = landing->S_dry[0] + landing->S_reC + landing->S_reO;
            insertion->gl_c = insertion->Ssumm/insertion->m_t;
            landing->gl_c = landing->Ssumm/landing->m_t;
            insertion->gl_c = insertion->gl_c/2;
            landing->gl_c = landing->gl_c/2;
            I_o[1] = M.fun_I (M.K[3]+d_O[1], M.K[4], m_O[1], D);
            I_c[1] = M.fun_I (M.K[5]+d_C[1], M.K[6], m_C[1], D);
            insertion->Isumm = M.get_IGO() +insertion->I_dry[1]+ I_o[0] + I_c[0] + I_o[1] + I_c[1]- insertion->m_t*pow(insertion->gl_c,2);
            landing->Isumm = landing->I_dry[0] + landing->I_reC + landing->I_reO - landing->m_t*pow(landing->gl_c,2);
            insertion->Isumm = insertion->Isumm;
            landing->Isumm = landing->Isumm;
            Ix = insertion->m_t * pow(D/2, 2);
            insertion->L = Lmax - L1;
            landing->L = L1;

            Ott_2 = insertion->anY;
            CILCON = 3.42;
            X_oneC = 0;
            X_twoC = 0;
        }
        // Участок разделения 2-ПН
        if (time>T[2] && time<=T[3])
        {
            insertion->Peng_t = 0;
            landing->Peng_t = 0;
            landing->Peng_control = landing->Peng_t/2;
            Imp_t = 0;
            CF = 0;
            insertion->m_t = m_dry[1]+mpn;
            landing->m_t = m_dry[0] + m_reC + m_reO;
            insertion->Ssumm = M.get_SGO() + insertion->S_dry[1]+ S_o[0] + S_c[0] + S_o[1] + S_c[1] ;
            landing->Ssumm = landing->S_dry[0] + landing->S_reC + landing->S_reO;
            insertion->gl_c = insertion->Ssumm/insertion->m_t;
            landing->gl_c = landing->Ssumm/landing->m_t;
            insertion->L = Lmax - L1 - L2;
            landing->L = L1;

            CILCON = 1.4;
            X_oneC = 0;
            X_twoC = 0;
        }
        // Участок полета ПН
        if (time>T[3])
        {
            insertion->Peng_t = 0;
            landing->Peng_t = 0;
            landing->Peng_control = landing->Peng_t/2;
            Imp_t = 0;
            CF = 0;
            insertion->m_t = mpn;
            landing->m_t = m_dry[0];
            insertion->Ssumm = M.get_SGO() + S_o[0] + S_c[0] + S_o[1] + S_c[1];
            landing->Ssumm = landing->S_dry[0] + landing->S_reC + landing->S_reO;
            insertion->gl_c = insertion->Ssumm/insertion->m_t;
            insertion->L = Lmax - L1 - L2;
            landing->L = L1;
            CILCON = 1.4;
            X_oneC = 0;
            X_twoC = 0;
        }
        //Участок возвращения

        if ((time>k1 && time<k2) || (time>k3 && time<k4))
        {
            if (m_furet>=0)
            {
                if (time>k1 && time<k2) (landing->Peng_t = kk1*peng[0]);
                if (time>k3 && time<k4) (landing->Peng_t = kk2*peng[0]);
                landing->Peng_control = landing->Peng_t;
                Imp_t = Imp[0];
                CF = landing->Peng_t/Imp_t;
                m_reC -= CF*h * 1/(Ratio+1);
                m_reO -= CF*h * Ratio/(Ratio+1);
                m_furet = m_reC + m_reO;
                landing->m_t = m_dry[0] + m_reC + m_reO;
                deo += CF*h *Ratio/(constants::density::liquid_oxygen*Smid)/(Ratio+1);
                dec += CF*h /(constants::density::kerosene*Smid)/(Ratio+1);
                landing->S_reO = M.fun_S (M.K[9 ]-21.5 + deo, M.K[10]-21.5, m_reO);
                landing->S_reC = M.fun_S (M.K[11]-21.5 + dec, M.K[13]-21.5, m_reC);
                landing->Ssumm = landing->S_dry[0] + landing->S_reC + landing->S_reO;
                landing->gl_c = landing->Ssumm/landing->m_t;
                landing->I_reO = M.fun_I (M.K[9 ]-21.5 + deo, M.K[10]-21.5, m_reO, D);
                landing->I_reC = M.fun_I (M.K[11]-21.5 + dec, M.K[13]-21.5, m_reC, D);
                landing->Isumm = landing->I_dry[0] + landing->I_reC + landing->I_reO - landing->m_t*pow(landing->gl_c,2);
                landing->Isumm = landing->Isumm;
                landing->L = L1;
                landing->focus = 0.7*landing->L;
                X_oneC = landing->gl_c - landing->focus;
                X_twoC = landing->L - landing->gl_c;
            };


        }

        // Программа угла атаки
        alpha alph_1 (insertion->V,  kalph [1], kalph [2], time, T_stage [0], 0, k3);
        alpha alph_2 (landing->V, kalph [1],              0, time, 200, 180, k3);

        // Учет параметров атмосферы
        HSP_p_1 = HSP_1;
        HSP_1 = (Atm_1.get_density()/2)*pow(insertion->V,2);
        HSP_p_2 = HSP_2;
        HSP_2 = (Atm_2.get_density()/2)*pow(landing->V,2);
        Mah_1 = insertion->V/Atm_1.get_SV();
        Mah_2 = landing->V/Atm_2.get_SV();

        insertion->focus = F.Focus(Mah_1, D, M.get_lengo(), M.get_wgo(), M.get_CIL(), CILCON);
        if (time<T_stage[0]) {CX_1=Qus_1.GetCX();  } else {CX_1=0;  }
        if (time<T_stage[0]) {CY_1=Qus_1.GetCY();  } else {CY_1=0;  }
        CX_2=Qus_2.GetCX();
        CY_2=Qus_2.GetCY();
        bpr = ((Atm_1.get_density()/2*pow(insertion->V,2))*Smid*insertion->L*CY_1*insertion->alpha)/(insertion->Peng_t*(insertion->L-insertion->gl_c));

        equations B_1 (Atm_1.get_density(), Smid, Atm_1.get_AOG(), insertion->m_t, CX_1, CY_1, insertion->Peng_t, alph_1.A(), Wind1);
        equations B_2 (Atm_2.get_density(), Smid, Atm_2.get_AOG(), landing->m_t, CX_2, CY_2, landing->Peng_t, alph_2.A(), Wind2);

        //dV = B_1.fdV(insertion->V, insertion->anY);
        dN = B_1.fdN(insertion->tY, insertion->V, insertion->anY);

        Ott = insertion->anY-Na;
        pitch_angle = Ott-insertion->alpha/57.3;

        insertion->tX += h * (insertion->V* cos(insertion->anY)+X1)/2;
        landing->tX += h * (landing->V* cos(landing->anY)+X2)/2;

        X1 = insertion->V* cos(insertion->anY);
        X2 = landing->V* cos(landing->anY);


        Wind1 = W1.WSol();
        Wind2 = W2.WSol();
        out1 << Wind2 << "\t" << landing->V << "\n";

        if (time<120 &&  HSP_1<HSP_p_1 && e<1)
        {

            MHSP_1 = HSP_1;
            VHSP_1 = insertion->V;
            e+=1;
        }

        if (time<120 &&  HSP_2<HSP_p_2 && e<1)
        {

            MHSP_2 = HSP_2;
            VHSP_2 = landing->V;
            e+=1;
        }
        //  if  (HSP_2>90000)  {HSP_2=HSP_1;}
        time+=h;
        Na  += dN*h;
        if (insertion->m_t>mpn)
        {

            //double me = insertion->anY;

            insertion->tY += insertion->V* sin(insertion->anY) *h;

            insertion->V   += (B_1.fdV(insertion->V, insertion->anY) + V1)/2*h;
            insertion->anY += (B_1.fdY(insertion->tY, insertion->V, insertion->anY)+Y1)/2*h;



            H11 = insertion->V* sin(insertion->anY);
            V1 = B_1.fdV(insertion->V, insertion->anY);
            Y1 = B_1.fdY(insertion->tY, insertion->V, insertion->anY);


            VX += h*B_1.dVX(velXY, Ott, Na);
            VY += h*B_1.dVY(velXY, Ott, Na);
            VZ += h*B_1.dVZ(velXY, Ott, Na);
            velXY = sqrt(VX*VX+VY*VY+VZ*VZ);
            trjXY = acos(VX/velXY);
            xXY += h*VX * cos(insertion->anY) / cos(Ott);
            yXY += h*VY * sin(insertion->anY) / sin(Ott);
            zXY += h*VZ;
            norXY = atan(xXY/(6371000+yXY));
        }

        if (time >T_fuel[0])
        {
            landing->tY += (landing->V* sin(landing->anY)+H22)/2*h;
            landing->V  += (B_2.returndV(landing->V, landing->anY)+V2)/2*h; //return
            landing->anY  += (B_2.returndY(landing->tY, landing->V, landing->anY)+Y2)/2*h;  //return

            V2 = B_2.returndV(landing->V, landing->anY);
            Y2 = B_2.returndY(landing->tY, landing->V, landing->anY);
            H22 = landing->V* sin(landing->anY);

        }
        else
        {
            landing->tY += (landing->V* sin(landing->anY)+H22)/2*h;
            landing->V  += (B_2.fdV(landing->V, landing->anY)+V2)/2*h;
            landing->anY  += (B_2.fdY(landing->tY, landing->V, landing->anY)+Y2)/2*h;

            V2 = B_2.fdV(landing->V, landing->anY);
            Y2 = B_2.fdY(landing->tY, landing->V, landing->anY);
            H22 = landing->V* sin(landing->anY);
        }
        //qDebug() << time;
         m_insertion_data -> time.push_back(time);
         m_insertion_data -> altitude.push_back(insertion->tY/1000);
         m_insertion_data -> x_moment.push_back(Ix);
         m_insertion_data -> attack_angle.push_back(alph_1.A());
         m_insertion_data -> trajectory_angle.push_back(insertion->anY*57.3);
         m_insertion_data -> center_of_mass.push_back(insertion->gl_c);
         m_insertion_data -> dynamic_pressure.push_back(HSP_1);
         m_insertion_data -> mass.push_back(insertion->m_t);
         m_insertion_data -> stability_margin.push_back(X_oneC);
         m_insertion_data -> thrust.push_back(insertion->Peng_t);
         m_insertion_data -> longitude.push_back(insertion->tX/1000);
         m_insertion_data -> velocity.push_back(insertion->V);
         m_insertion_data -> wind_velocity.push_back(Wind1);
         m_insertion_data -> g_force.push_back(insertion->Peng_t/(insertion->m_t*Atm_1.get_AOG()));
         m_insertion_data -> yz_moment.push_back(insertion->Isumm);
         m_insertion_data -> static_moment.push_back(insertion->Ssumm);
         m_insertion_data -> engine_angle.push_back(bpr*57.3);
         m_insertion_data -> pitch_angle.push_back(pitch_angle*57.3);
         m_insertion_data -> focus.push_back(insertion->focus);
         //m_insertion_data -> control_thrust;
         //m_insertion_data -> drug_coefficient;
         //m_insertion_data -> rocket_lenght;
         m_insertion_data -> lift_force.push_back(HSP_1*Smid*CX_1);

         m_recovery_data -> time.push_back(time);
         m_recovery_data -> altitude.push_back(landing->tY/1000);
         //m_recovery_data -> x_moment;
         m_recovery_data -> attack_angle.push_back(alph_2.A());
         m_recovery_data -> trajectory_angle.push_back(landing->anY*57.3);
         m_recovery_data -> center_of_mass.push_back(landing->gl_c);
         m_recovery_data -> dynamic_pressure.push_back(HSP_2);
         m_recovery_data -> mass.push_back(landing->m_t);
         m_recovery_data -> stability_margin.push_back(X_twoC);
         m_recovery_data -> thrust.push_back(landing->Peng_t);
         m_recovery_data -> longitude.push_back(landing->tX/1000);
         m_recovery_data -> velocity.push_back(landing->V);
         m_recovery_data -> wind_velocity.push_back(Wind2);
         m_recovery_data -> g_force.push_back(landing->Peng_t/(landing->m_t*Atm_2.get_AOG()));
         m_recovery_data -> yz_moment.push_back(landing->Isumm);
         //m_recovery_data -> static_moment;
         //m_recovery_data -> engine_angle;
         //m_recovery_data -> pitch_angle;
         //m_recovery_data -> focus;
         m_recovery_data -> control_thrust.push_back(landing->Peng_control);
         m_recovery_data -> drug_coefficient.push_back(CY_2);
         m_recovery_data -> rocket_length.push_back(landing->L);
         m_recovery_data -> lift_force.push_back(HSP_2*Smid*CX_2);


        amax = alph_1.A();
        count+=1;
        MaxTime = count*h;
    }
    while (landing->tY>0 && landing->V>0);
}

std::shared_ptr<Dataset> FlightSolver::GetInsertionData()   {
    return m_insertion_data;
}

std::shared_ptr<Dataset> FlightSolver::GetRecoveryData()   {
    return m_recovery_data;
}
