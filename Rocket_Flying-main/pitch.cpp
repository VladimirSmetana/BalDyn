#include "pitch.h"
#include <QDebug>
pitch::pitch()
{

}

void pitch::pitch_calculations(double (&kalph)[3], double (&kpeng)[2])
{
    //
    double m_t;
    double V;
    double S_dry[2];

    double peng;
    peng = 636;
    // Рассчитываемые параметры конструкции
    double m_fuel;
    double m_dry;

    M_Rocket=5.32;
    m_t = M_Rocket;

    //
    // Время действия тормозных импульсов

    //
    // Поле локальных переменных
    Smid = M_PI*pow(D,2)/4;

    V = 0.6;
    count =0;
    //
    // Создание объектов

    mass M;
    //
    // Определение габаритов ракеты
    //M.MCI_f(0, h, mpn, D, mb[0], mb[1], s[0], s[1], peng[0], peng[1]);
    //double L = Lmax;
    double L= 1.2;//M.get_lst1();



    //
    // Определение основных мцих

        m_fuel = 0.7;
        m_dry = M_Rocket-m_fuel;

        double m_fuel_start = 0.7;

//    S_dry[0] = M.fun_S (M.K[6]-21.5, M.K[12]-21.5, m_dry[0]);
//    S_dry[1] = M.fun_S (M.K[1]-21.5, M.K[6]-21.5, m_dry[1]);
//    S_o[0] = M.fun_S (M.K[8], M.K[9], m_O[0]);
//    S_c[0] = M.fun_S (M.K[10], M.K[11], m_C[0]);
//    S_o[1] = M.fun_S (M.K[3], M.K[4], m_O[1]);
//    S_c[1] = M.fun_S (M.K[5], M.K[6], m_C[1]);
//    fir->S_reO = M.fun_S (M.K[9], M.K[10], m_reO);
//    fir->S_reC = M.fun_S (M.K[11], M.K[13], m_reC);
//    sec->S_reO = M.fun_S (M.K[9 ]-21.5, M.K[10]-21.5, m_reO);
//    sec->S_reC = M.fun_S (M.K[11]-21.5, M.K[13]-21.5, m_reC);

//    fir->Ssumm  = M.get_SGO() + fir->S_dry[0] + fir->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + fir->S_reO + fir->S_reC;
//    Sx = fir->Ssumm;
//    fir->gl_c = fir->Ssumm/M_Rocket;
//    gl_cmax = fir->gl_c;
    //std::cout<<Sx<<std::endl;
    //std::cout<<fir->gl_c<<std::endl;

//    fir->I_dry[0] = M.fun_I (M.K[6], M.K[12], m_dry[0], D);
//    fir->I_dry[1] = M.fun_I (M.K[1], M.K[6], m_dry[1], D);

//    sec->I_dry[0] = M.fun_I (M.K[6]-6, M.K[12]-6, m_dry[0], D);

//    I_o[0] = M.fun_I (M.K[8], M.K[9], m_O[0], D);
//    I_c[0] = M.fun_I (M.K[10], M.K[11], m_C[0], D);
//    I_o[1] = M.fun_I (M.K[3], M.K[4], m_O[1], D);
//    I_c[1] = M.fun_I (M.K[5], M.K[6], m_C[1], D);
//    fir->I_reO = M.fun_I (M.K[9], M.K[10], m_reO, D);
//    fir->I_reC = M.fun_I (M.K[11], M.K[13], m_reC, D);
//    sec->I_reO = M.fun_I (M.K[9 ]-21.5, M.K[10]-21.5, m_reO, D);
//    sec->I_reC = M.fun_I (M.K[11]-21.5, M.K[13]-21.5, m_reC, D);
//    fir->Isumm  = M.get_IGO() + fir->I_dry[0] + fir->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + fir->I_reO + fir->I_reC - M_Rocket*pow(gl_cmax,2);
//    Iz = fir->Isumm;
//    Izmax = Iz;
//    Ix = M_Rocket * pow(D/2, 2);
//    Ixmax = Ix;

    T_fuel = 2.17;
    //
    // ИД итеративного расчета
    anY = M_PI/2-10/57.3;

    //double p_ground = 101325;
    tY = 1;
    //
    // Итеративный расчет
    H1.clear();
    H2.clear();
    xn.clear();
    count = 0;
    tY = 1;
    tX = 1;
    int i = 0;
    int value = 0;
    d_O = 0;
    double K1, K2, K3, K4;
    //while (sec->tY>=0.5 && sec->V>=0.5) sec->tY>=0.5
    while (tY>0 && V>0)
    {
        airforce Qus_1 (Mah_1);
//        airforce Qus_2 (Mah_2);

        focus F;

        atmosphere Atm_1 (tY);
//        atmosphere Atm_2 (tY);
        eastwind W1 (tY/1000);
//        eastwind W2 (tY/1000);


        // Участок работы ДУ-1
        if (time<=T_fuel)
        {
            //if (m_t > M_Rocket-onefu )
            //{
            Peng_control = peng;
            //+ (p_ground - P.get_pressure()) * Smid/2;

            m_t = m_fuel+m_dry;

            m_fuel -= m_fuel_start/T_fuel*h;
//            d_O[0] += Ratio*CF*h/(1100*Smid)/(Ratio+1);
//            d_C[0] += CF*h/(440*Smid)/(Ratio+1);
//            S_o[0] = M.fun_S (M.K[8]+d_O[0], M.K[9], m_O[0]);
//            S_c[0] = M.fun_S (M.K[10]+d_C[0], M.K[11], m_C[0]);
//            // fir в sec->e не ошибка, а условность СК
//            fir->Ssumm  = M.get_SGO() + fir->S_dry[0] + fir->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + fir->S_reO + fir->S_reC;
//            sec->Ssumm = M.get_SGO() + fir->S_dry[0] + fir->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + fir->S_reO + fir->S_reC;
//            fir->gl_c = fir->Ssumm/fir->m_t;
//            sec->gl_c = sec->Ssumm/sec->m_t;

//            I_o[0] = M.fun_I (M.K[8]+d_O[0], M.K[9], m_O[0], D);
//            I_c[0] = M.fun_I (M.K[10]+d_C[0], M.K[11], m_C[0], D);
//            fir->Isumm  = M.get_IGO() + fir->I_dry[0] + fir->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + fir->I_reC +fir->I_reO - fir->m_t*pow (fir->gl_c,2);

//            sec->Isumm = M.get_IGO() + fir->I_dry[0] + fir->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + fir->I_reC +fir->I_reO - sec->m_t*pow(sec->gl_c,2);
//            Ix = fir->m_t * pow(D/2, 2);
            //}
            //else T_fuel[0] = time;
            //if (abs(m_t - (M_Rocket-m_fuel[0])) < 100) T_fuel[0] = time;
//            fir->L  = Lmax;
//            sec->L = Lmax;
//            Ott_1 = fir->anY;
//            H_1 = fir->tY/1000;
//            CILCON = 12.88;
//            dep = count*h;
//            sec->focus = F.Focus(Mah_1, D, M.get_lengo(), M.get_wgo(), M.get_CIL(), CILCON);
//            X_oneC = sec->gl_c - sec->focus;
//            X_twoC = sec->L - sec->gl_c;
        }

        // Участок полета ПН
        else
        {
            peng = 0;
            Peng_control = 0;
//            Imp_t = 0;
//            CF = 0;
              m_t = m_dry;
//            sec->m_t = mpn;
//            fir->Ssumm =  sec->S_dry[0] + sec->S_reC + sec->S_reO;
//            sec->Ssumm = sec->S_dry[0] + sec->S_reC + sec->S_reO;
//            fir->gl_c = fir->Ssumm/fir->m_t;
//            sec->gl_c = sec->Ssumm/sec->m_t;
//            fir->L = Lmax - L1 - L2;
//            sec->L = L1;
//            CILCON = 1.4;
//            X_oneC = 0;
//            X_twoC = 0;
        }


        // std::cout<<"t = "<<count*h<<std::endl;
        // std::cout<<"H = "<<sec->tY/1000<<std::endl;
        // std::cout<<"V = "<<sec->V<<std::endl;
        // std::cout<<"m = "<<m_reC+m_reO<<std::endl;

        // Программа угла атаки
//        alpha alph_1 (fir->V,  kalph [1], kalph [2], time, T_stage [0], 0, k2, k3);
//        alpha alph_2 (sec->V, kalph [1],              0, time, 200, 180, k2, k3);

        // Учет параметров атмосферы




        //HSP = (P.get_density()/2)*pow(V,2);
        HSP_p_1 = HSP_1;
        HSP_1 = (Atm_1.get_density()/2)*pow(V,2);
        Mah_1 = V/Atm_1.get_SV();


//        fir->focus = F.Focus(Mah_1, D, M.get_lengo(), M.get_wgo(), M.get_CIL(), CILCON);
        //std::cout << Focus << std::endl;
        //Focus = M.Focus(Mah_1, D, M.get_lengo(), M.get_wgo());
        //qDebug()<<M.K[10]+d_C[0];

        CX_1=Qus_1.getCX();
        CY_1=Qus_1.getCY();
//        CX_2=Qus_2.getCX();
//        CY_2=Qus_2.getCY();
//        bpr = ((Atm_1.get_density()/2*pow(fir->V,2))*Smid*fir->L*CY_1*fir->alpha)/(fir->Peng_t*(fir->L-fir->gl_c));

        equations B_1 (Atm_1.get_density(), Smid, Atm_1.get_AOG(), m_t, CX_1, CY_1, peng, 0, Wind1);
//        equations B_2 (Atm_2.get_density(), Smid, Atm_2.get_AOG(), sec->m_t, CX_2, CY_2, sec->Peng_t, alph_2.A(), Wind2);

        //dV = B_1.fdV(fir->V, fir->anY);
        dN = B_1.fdN(tY, V, anY);

        Ott = anY-Na;
        pitch_angle = Ott;

        tX += h * (V* cos(anY)+X1)/2;


        X1 = V* cos(anY);



        Wind1 = W1.WSol();


//        if (time<120 &&  HSP_1<HSP_p_1 && e<1)
//        {

//            MHSP_1 = HSP_1;
//            VHSP_1 = fir->V;
//            e+=1;
//        }

//        if (time<120 &&  HSP_2<HSP_p_2 && e<1)
//        {

//            MHSP_2 = HSP_2;
//            VHSP_2 = sec->V;
//            e+=1;
//        }
        //  if  (HSP_2>90000)  {HSP_2=HSP_1;}
        time+=h;
        Na  += dN*h;
        if (tY>0)
        {

            //double me = fir->anY;

            tY += V* sin(anY) *h;

//            K1 = B_1.fdV(fir->V, fir->anY);
//            K2 = B_1.fdV(fir->V+h/2*K1, fir->anY+h/2);
//            K3 = B_1.fdV(fir->V+h/2*K2, fir->anY+h/2);
//            K4 = B_1.fdV(fir->V+h*K3, fir->anY+h);
//            fir->V   += (K1 + K2*2 + K3*2 + K4)/6*h;

//            K1 = B_1.fdY(fir->tY, fir->V, fir->anY);
//            K2 = B_1.fdY(fir->tY+h/2, fir->V+h/2, fir->anY+h/2*K1);
//            K3 = B_1.fdY(fir->tY+h/2, fir->V+h/2, fir->anY+h/2*K2);
//            K4 = B_1.fdY(fir->tY+h, fir->V+h, fir->anY+h*K3);
//            fir->anY += (K1 + K2*2 + K3*2 + K4)/6*h;

            //fir->V += Runge_Kutt(&B_1.fdV, fir->V, fir->anY, h);
            V   += (B_1.fdV(V, anY) + V1)/2*h;
            anY += (B_1.fdY(tY, V, anY)+Y1)/2*h;
            qDebug() << "t : " <<time << ";V : " << V << ";H : " << tY << ";L : " << tX << ";peng : " << peng << ";mass : " << m_t
                     << ";Y : " << anY*57.3 << ";Mah : " << Mah_1;


            H11 = V* sin(anY);
            V1 = B_1.fdV(V, anY);
            Y1 = B_1.fdY(tY, V, anY);


            //std::cout << zXY/1000  << std::endl;
            VX += h*B_1.dVX(velXY, Ott, Na);
            VY += h*B_1.dVY(velXY, Ott, Na);
            VZ += h*B_1.dVZ(velXY, Ott, Na);
            velXY = sqrt(VX*VX+VY*VY+VZ*VZ);
            trjXY = acos(VX/velXY);
            xXY += h*VX * cos(anY) / cos(Ott);
            yXY += h*VY * sin(anY) / sin(Ott);
            zXY += h*VZ;
            norXY = atan(xXY/(6371000+yXY));
            //


            /*

*/

        }

//        if (time >T_fuel[0])
//        //if ((time>k1 && time<k2) || (time>k3 && time<k4))
//        {



//            sec->tY += (sec->V* sin(sec->anY)+H22)/2*h;
//            sec->V  += (B_2.returndV(sec->V, sec->anY)+V2)/2*h; //return
//            sec->anY  += (B_2.returndY(sec->tY, sec->V, sec->anY)+Y2)/2*h;  //return


//            V2 = B_2.returndV(sec->V, sec->anY);
//            Y2 = B_2.returndY(sec->tY, sec->V, sec->anY);
//            H22 = sec->V* sin(sec->anY);

//        }
//        else
//        {
//            sec->tY += (sec->V* sin(sec->anY)+H22)/2*h;
//            sec->V  += (B_2.fdV(sec->V, sec->anY)+V2)/2*h;
//            sec->anY  += (B_2.fdY(sec->tY, sec->V, sec->anY)+Y2)/2*h;

//            V2 = B_2.fdV(sec->V, sec->anY);
//            Y2 = B_2.fdY(sec->tY, sec->V, sec->anY);
//            H22 = sec->V* sin(sec->anY);
//        }


        xn.push_back(time);
//        yu_1.push_back(HSP_1);
//        yu_2.push_back(HSP_2);
////        center_1.push_back(fir->gl_c);
////        center_2.push_back(sec->gl_c);
        v_1.push_back(V);
//        v_2.push_back(sec->V);
//        sinn.push_back(fir->Ssumm);
//        jinn.push_back(fir->Isumm);
//        jinn2.push_back(sec->Isumm);
//        CM.push_back(fir->Ssumm/fir->m_t);
        mass_1.push_back(m_t);
//        mass_2.push_back(sec->m_t);
        Long_1.push_back(tX);
//        Long_2.push_back(sec->tX/1000);
//        w.push_back(Wind2);
        H1.push_back(tY);
//        H2.push_back(sec->tY/1000);
//        angle.push_back(pitch_angle*57.3);
//        b1.push_back(HSP_1*Smid*CX_1);
//        b2.push_back(HSP_2*Smid*CX_2);
//        lin.push_back(Ix);
////        ALI_1.push_back(alph_1.A());
////        ALI_2.push_back(alph_2.A());
//        //ALI.push_back(fir->Peng_t/ (fir->m_t*Atm_1.get_AOG()));
////        res.push_back(sec->Peng_t/(sec->m_t*Atm_2.get_AOG()));
        TET_1.push_back(anY*57.3);
//        TET_2.push_back(sec->anY*57.3);
//        be.push_back(bpr*57.3);
//        pi.push_back(pitch_angle*57.3);
        P1.push_back(peng);
//        P2.push_back(sec->Peng_t);
//        f1.push_back(fir->focus);
//        Lon.push_back(fir->Peng_t/(fir->m_t*Atm_1.get_AOG()));
////        Lonre.push_back(sec->Peng_t/(sec->m_t*Atm_2.get_AOG()));
//        pc2.push_back(sec->Peng_control);
//        cy2.push_back(CY_2);
//        //std::cout << CY_2 << std::endl;
//        dyn1.push_back(X_oneC);
//        dyn2.push_back(X_twoC);
//        lenght_R.push_back(sec->L);
//        //qDebug() << sec->L;

//        //std::cout<<fir->gl_c<<std::endl;
////        amax = alph_1.A();
//        count+=1;
        MaxTime = count*h;
    }
}
