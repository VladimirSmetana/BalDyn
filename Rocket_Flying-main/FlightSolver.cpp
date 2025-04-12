#include "FlightSolver.h"

#include "Constants.h"



FlightSolver::FlightSolver(double (&attackValue)[3], double (&thrustToWeight)[2])
    : FlightInit(thrustToWeight)
 {

    std::copy(std::begin(m_attack_value), std::end(m_attack_value), std::begin(attackValue));

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
    std::cout << "Fuel mass (1 sg): " << m_fuel[0] << "\n";
    std::cout << "Fuel mass (2 sg): " << m_fuel[1] << "\n";
    std::cout << "Dry mass (1 sg): " << m_dry[0] << "\n";
    std::cout << "Dry mass (2 sg): " << m_dry[1] << "\n";
    std::cout << "Extra mass (landing): " << m_furet << "\n";
    std::cout << "Full rocket mass: " << M_Rocket << "\n";
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
        alpha alph_1 (fir->V,  m_attack_value [1], m_attack_value [2], time, T_stage [0], 0, k2, k3);
        alpha alph_2 (sec->V,  m_attack_value [1],                  0, time, 200, 180, k2, k3);

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
