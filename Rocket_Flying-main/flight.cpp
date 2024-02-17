#include "flight.h"

flight ::flight ()
{

}

void flight ::flight_calculations(double (&kalph)[3], double (&kpeng)[2])
{
    //
    double peng [2];
    peng[0] = kpeng[0] * 9.81 * (mpn+mb[0]+mb[1]);
    peng[1] = kpeng[1] * 9.81 * (mpn+mb[1]);
    // Рассчитываемые параметры конструкции
    double m_fuel[2];
    double m_dry[2];
    double T_fuel[2];
    double m_furet = 33200/*2200*/, m_reC = m_furet*1/4.5, m_reO = m_furet*3.5/4.5;
    M_Rocket=mpn;
    fir->m_t = M_Rocket;
    sec->m_t = M_Rocket;
    //
    // Время действия тормозных импульсов

    //
    // Поле локальных переменных
    Smid = M_PI*pow(D,2)/4;
    fir->V = 0.1;
    sec->V = 0.6;
    count =0;
    //
    // Создание объектов

    mass M;
    //
    // Определение габаритов ракеты
    M.MCI_f(0, h, mpn, D, mb[0], mb[1], s[0], s[1], peng[0], peng[1]);
    Lmax = M.get_lenght();
    //double L = Lmax;
    double L1= M.get_lst1();
    double L2= M.get_lst2();
    //
    // Определение основных мцих
    for (int i=0;i<=1;i++)
    {
        m_fuel[i] = mb[i] * (s[i] - 1) / s[i];
        m_O[i] = m_fuel[i]*Ratio/(Ratio+1);
        m_C[i] = m_fuel[i]*1/(Ratio+1);
        m_dry[i] = mb[i]-m_fuel[i];
    }
    m_dry[0]-=m_furet;
    M_Rocket+=m_fuel[0]+m_dry[0]+m_fuel[1]+m_dry[1] + m_furet;

    double zap = 0;
    m_dry [1]+=zap;

    double onefu = m_fuel[0];
    M_stage [0] = M_Rocket;
    M_stage [1] = M_Rocket - mb[0];

    fir->S_dry[0] = M.fun_S (M.K[6], M.K[12], m_dry[0]);
    fir->S_dry[1] = M.fun_S (M.K[1], M.K[6], m_dry[1]);
    sec->S_dry[0] = M.fun_S (M.K[6]-21.5, M.K[12]-21.5, m_dry[0]);
    sec->S_dry[1] = M.fun_S (M.K[1]-21.5, M.K[6]-21.5, m_dry[1]);
    S_o[0] = M.fun_S (M.K[8], M.K[9], m_O[0]);
    S_c[0] = M.fun_S (M.K[10], M.K[11], m_C[0]);
    S_o[1] = M.fun_S (M.K[3], M.K[4], m_O[1]);
    S_c[1] = M.fun_S (M.K[5], M.K[6], m_C[1]);
    fir->S_reO = M.fun_S (M.K[9], M.K[10], m_reO);
    fir->S_reC = M.fun_S (M.K[11], M.K[13], m_reC);
    sec->S_reO = M.fun_S (M.K[9 ]-21.5, M.K[10]-21.5, m_reO);
    sec->S_reC = M.fun_S (M.K[11]-21.5, M.K[13]-21.5, m_reC);

    fir->Ssumm  = M.get_SGO() + fir->S_dry[0] + fir->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + fir->S_reO + fir->S_reC;
    Sx = fir->Ssumm;
    fir->gl_c = fir->Ssumm/M_Rocket;
    gl_cmax = fir->gl_c;
    //std::cout<<Sx<<std::endl;
    //std::cout<<fir->gl_c<<std::endl;

    fir->I_dry[0] = M.fun_I (M.K[6], M.K[12], m_dry[0], D);
    fir->I_dry[1] = M.fun_I (M.K[1], M.K[6], m_dry[1], D);

    sec->I_dry[0] = M.fun_I (M.K[6]-6, M.K[12]-6, m_dry[0], D);

    I_o[0] = M.fun_I (M.K[8], M.K[9], m_O[0], D);
    I_c[0] = M.fun_I (M.K[10], M.K[11], m_C[0], D);
    I_o[1] = M.fun_I (M.K[3], M.K[4], m_O[1], D);
    I_c[1] = M.fun_I (M.K[5], M.K[6], m_C[1], D);
    fir->I_reO = M.fun_I (M.K[9], M.K[10], m_reO, D);
    fir->I_reC = M.fun_I (M.K[11], M.K[13], m_reC, D);
    sec->I_reO = M.fun_I (M.K[9 ]-21.5, M.K[10]-21.5, m_reO, D);
    sec->I_reC = M.fun_I (M.K[11]-21.5, M.K[13]-21.5, m_reC, D);
    fir->Isumm  = M.get_IGO() + fir->I_dry[0] + fir->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + fir->I_reO + fir->I_reC - M_Rocket*pow(gl_cmax,2);
    Iz = fir->Isumm;
    Izmax = Iz;
    Ix = M_Rocket * pow(D/2, 2);
    Ixmax = Ix;

    T_fuel[0] = m_fuel[0]/(peng [0]/Imp[0]);
    T_stage [0] = T_fuel [0] + T_sep [0];
    T_fuel[1] = m_fuel[1]/(peng [1]/Imp[1]);
    T_stage [1] = T_fuel [1] + T_sep [1];
    //
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
    int i = 0;
    int value = 0;
    d_O[1] = 0;
    double K1, K2, K3, K4;
    //while (sec->tY>=0.5 && sec->V>=0.5) sec->tY>=0.5
    while (sec->tY>0 && sec->V>0)
    {


        focus F;


        eastwind W1 (fir->tY/1000);
        eastwind W2 (sec->tY/1000);


        // Участок работы ДУ-1
        if (time<=T_fuel[0])
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
            sec->focus = F.Focus(Mah[0], D, M.get_lengo(), M.get_wgo(), M.get_CIL(), CILCON);
            X_oneC = sec->gl_c - sec->focus;
            X_twoC = sec->L - sec->gl_c;
        }
        // Участок разделения 1-2
        if (time >T_fuel[0] && time<=T_fuel[0] + T_sep[0])
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
        if (time>T_fuel[0] + T_sep[0] && time<=T_fuel[0] + T_sep[0]+T_fuel[1])
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
        if (time>T_fuel[0] + T_sep[0]+T_fuel[1] && time<=T_fuel[0] + T_sep[0]+T_fuel[1] + T_sep[1])
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
        if (time>T_fuel[0] + T_sep[0]+T_fuel[1] + T_sep[1])
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

        // std::cout<<"t = "<<count*h<<std::endl;
        // std::cout<<"H = "<<sec->tY/1000<<std::endl;
        // std::cout<<"V = "<<sec->V<<std::endl;
        // std::cout<<"m = "<<m_reC+m_reO<<std::endl;


        pit.pitch_calculations();
        fir->focus = F.Focus(Mah[0], D, M.get_lengo(), M.get_wgo(), M.get_CIL(), CILCON);

        //qDebug()<<sec->tY;
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
        w.push_back(Wind2);
        H1.push_back(fir->tY/1000);
        H2.push_back(sec->tY/1000);
        angle.push_back(pitch_angle*57.3);
        b1.push_back(HSP_1*Smid*CX_1);
        b2.push_back(HSP_2*Smid*CX_2);
        lin.push_back(Ix);
        ALI_1.push_back(alph_1.A());
        ALI_2.push_back(alph_2.A());
        //ALI.push_back(fir->Peng_t/ (fir->m_t*Atm_1.get_AOG()));
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
        //std::cout << CY_2 << std::endl;
        dyn1.push_back(X_oneC);
        dyn2.push_back(X_twoC);

        //std::cout<<fir->gl_c<<std::endl;
        amax = alph_1.A();
        count+=1;
        MaxTime = count*h;
    }
}
