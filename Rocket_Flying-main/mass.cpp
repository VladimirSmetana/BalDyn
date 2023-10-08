#include "mass.h"


double mass::fun_S(double X_l, double X_b, double mass)
    {
        return 0.5 * mass * (X_l+X_b);
    }
double mass::fun_I(double X_l, double X_b, double mass, double D)
    {
        return 0.25 * mass * ( pow(X_l+X_b, 2) + 0.333 * pow(X_b - X_l, 2)+pow((D/2),2) );
    }

    void  mass::MCI_f (double time,double h,double payload, double D,double m_block1, double m_block2,double s1, double s2,double P1, double P2)
    {
        mb[0] = m_block1; mb[1] = m_block2;
        M_Rocket = mb[0] + mb[1] + payload;
        s[0] = s1; s[1] = s2;
        Peng[0] = P1; Peng[1] = P2;

        w_headunit = 80;

        m_instrument = 0.0008*M_Rocket;
        w_instrument = m_instrument/150;
        W_Rocket = w_headunit+w_instrument;
        L_headunit = 11;
        L_instrument = 0.1;
        L_Rocket += L_headunit + L_instrument;

        for (int i=0;i<=1;i++)
        {
            m_fuel[i] = mb[i] * (s[i] - 1) / s[i];
            m_dry[i] = mb[i]-m_fuel[i];
            w_dry[i]=m_dry[i]/po_dry;
            m_C[i]=m_fuel[i]*1/(1+Ratio);
            m_O[i]=m_fuel[i]*Ratio/(1+Ratio);
            w_C[i] = m_C[i]/po_C;
            w_O[i] = m_O[i]/po_O;

            //L_C[i] = w_C[i]*4/(M_PI*pow(D,2));
            //L_O[i] = w_O[i]*4/(M_PI*pow(D,2));
            L_taC[i] = 1.1*L_C[i];
            L_taO[i] = 1.1*L_O[i];
            //L_spC[i] = L_taC[i] - L_C[i];
            //L_spO[i] = L_taO[i] - L_O[i];


            L_b[i] = L_taC[i]+L_taO[i]+L_engine[i];

            W_taC[i] = 1.25*w_C[i];
            W_taO[i] = 1.25*w_O[i];
            W_Rocket +=  W_taC[i] + W_taO[i];
        }
        W_Rocket = W_Rocket/(1-0.15);


        //L_engine[0] = 3.2;
        //L_engine[1] = 5.4;



        //U_C[0] = time -

        // Геометрические исходные данные

        L_spO[1] = 0.6;
        L_O[1] = 4.8;
        L_spC[1] = 0.6;
        L_C[1] = 4.1+0.6;
        L_engine[1] =3.2-0.6;
        L_spO[0] = 1;
        L_O[0] = 17.3;
        L_spC[0] = 2.7;
        L_C[0] = 13.2;
        L_engine[0] = 4.9;
        // Координаты граничных точек РН
        K[0] = 0;
        K[1] = K[0] + L_headunit;
        K[2] = K[1] + L_instrument;
        K[3] = K[2] + L_spO[1];
        K[4] = K[3] + L_O[1];
        K[5] = K[4] + L_spC[1];
        K[6] = K[5] + L_C[1];
        K[7] = K[6] + L_engine[1];
        K[8] = K[7] + L_spO[0];
        K[9] = K[8] + L_O[0];
        K[10]= K[9] + L_spC[0];
        K[11]= K[10]+ L_C[0];
        K[13]= K[11]+ 1.3;
        K[12]= K[11]+ L_engine[0];



        L_Rocket =K[12];


        CIL = (L_Rocket - L_headunit) / D; CON = (L_headunit) / D; CILCON = CIL / CON;
        // Определение моментов инерции
        S_dry[0] = fun_S (K[6], K[12], m_dry[0]);
        S_o[0] = fun_S (K[8], K[9], m_O[0]);
        S_c[0] = fun_S (K[10], K[11], m_C[0]);
        S_dry[1] = fun_S (K[1], K[6], m_dry[1]);
        S_o[1] = fun_S (K[3], K[4], m_O[1]);
        S_c[1] = fun_S (K[5], K[6], m_C[1]);
        S_headunit = fun_S (K[0], K[1], 16500);
        //S_Rocket = S_instrument + S_Rocket;

        I_dry[0] = fun_I (K[6], K[12], m_dry[0], D);
        I_o[0] = fun_I (K[10], K[11], m_O[0], D);
        I_c[0] = fun_I (K[8], K[9], m_C[0], D);
        I_dry[1] = fun_I (K[1], K[6], m_dry[1], D);
        I_o[1] = fun_I (K[5], K[6], m_O[1], D);
        I_c[1] = fun_I (K[3], K[4], m_C[1], D);
        I_headunit = fun_I (K[0], K[1], 16500, D);


        m_center = S_Rocket/M_Rocket;



        return;
    }

    double mass::get_CM()
    {
        return m_center;
    }
    double mass::get_I()
    {
        return I_Rocket;
    }
    double mass::get_S()
    {
        return S_Rocket;
    }
    double mass::get_lenght()
    {
        return L_Rocket;
    }
    double mass::get_lst1()
    {
        return L_b[0];
    }
    double mass::get_lst2()
    {
        return L_b[1];
    }
    double mass::get_SGO()
    {
        return S_headunit;
    }
    double mass::get_IGO()
    {
        return I_headunit;
    }

    double mass::get_wgo()
    {
        return w_headunit;
    }

    double mass::get_lengo()
    {
        return L_headunit;
    }

    double mass::get_CIL()
    {
        return CIL;
    }




