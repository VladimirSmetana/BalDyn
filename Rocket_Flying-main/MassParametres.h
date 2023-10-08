#ifndef MASSPARAMETRES_H
#define MASSPARAMETRES_H

class Parametres
{
private:
    double Ratio = 3.5;
    double po_dry = 300;

    double po_C = 440, po_O = 1150;
    double s[2];

    double mb[2];
    double m_dry[2];
    double m_fuel[2];
    double m_instrument;
    double M_Rocket;

    double Peng[2];

    double w_dry[2];
    double w_headunit;
    double w_instrument;

    double m_C[2];
    double m_O[2];


    double L_C[2], L_O[2];
    double U_C[2], U_O[2];

    double L_spC[2], L_spO[2];
    double L_b[2];

    double L_headunit = 3.5;
    double L_instrument = 0.1;

    double W_Rocket;
    double L_Rocket;

    double CIL, CON, CILCON;

    double S_dry[2], S_o[2], S_c[2], S_instrument, S_headunit, S_Rocket;
    double I_dry[2], I_o[2], I_c[2], I_instrument, I_headunit, I_Rocket;

    double m_center;



public:
    double L_taC[2], L_taO[2];
    double W_taC[2], W_taO[2];
    double w_C[2], w_O[2];
    double L_engine[2];
    double K[14];
};



#endif // MASSPARAMETRES_H
