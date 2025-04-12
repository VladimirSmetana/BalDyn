#include "equations.h"
#include "Constants.h"
    equations::equations (double po, double S, double g, double m, double CX, double CY, double PENG, double alpha, double wind)
    :po(po),S(S), g(g), m(m), CX(CX), CY(CY), PENG(PENG), alpha(alpha), wind(wind)
    {}

    // Баллистические уравнения
    double equations::fdV(double vv, double ii)
    {
        F_P = (PENG * cos((M_PI * alpha) / 180));
        F_X = CX * S * po * pow(vv, 2) / 2;
        return  F_P/m -  F_X/m - g * sin(ii);
    }

    double equations::dVX(double vv, double ii, double N)
    {
        double J = 8*M_PI/180;
        F_P = PENG * cos( (M_PI * alpha) / 180 + ii);
        F_X = CX * S * po * pow(vv, 2) / 2 * cos(ii) * cos(J);
        F_Y = (CY  * S * (po * pow(vv, 2)) / 2) * sin(ii);
        F_Z = - CY * S * po * pow(vv, 2) / 2 * cos(ii) * sin(J);
        F_G = m*g*sin(N);
        return (F_P - F_X - F_Y - F_G)/m;
    }

    double equations::dVY(double vv, double ii, double N)
    {
        double J = 8*M_PI/180;
        F_P = PENG * sin( (M_PI * alpha) / 180 + ii);
        F_X = -CX * S * po * pow(vv, 2) / 2 * sin(ii) * cos(J);
        F_Y = (CY * S * (po * pow(vv, 2)) / 2) * cos(ii);
        F_Z = CY * S * po * pow(vv, 2) / 2 * sin(ii) * sin(J);
        F_G = m*g*cos(N);
        return (F_P - F_X + F_Y - F_G)/m;
    }

    double equations::dVZ(double vv, double ii, double N)
    {
        double J = 8*M_PI/180;
        F_X = -CX * S * po * pow(vv, 2) / 2 * sin(ii) * cos(J);
        F_Z = (CY * S * (po * pow(vv, 2)) / 2) * cos(J);
        F_W = (CY * S * (po * pow(wind, 2)) / 2);
        F_G = m*sin(N);
        return (F_X+F_Z-F_G-F_W)/m;
    }

    double equations::fdY(double hh, double vv, double ii)
    {
        F_P = (PENG * sin((M_PI * alpha) / 180));
        F_Y = (CY * ((M_PI * alpha) / 180) * S * (po * pow(vv, 2)) / 2);
        return (F_P+ F_Y)/ (m*vv)  - ((g  * cos(ii))) * (1-pow(vv,2)/(g*(constants::earth_radius+hh))) /vv;
    }

    double equations::returndV(double vv, double ii)
    {
        F_P = (PENG * cos((M_PI * alpha) / 180));
        F_X = CX * S * po * pow(vv, 2) / 2;
        return  -F_P/m -  F_X/m - g * sin(ii);
    }

    double equations::returndY(double hh, double vv, double ii)
    {
        F_P = (PENG * sin((M_PI * alpha) / 180));
        F_Y = (CY * ((M_PI * alpha) / 180) * S * (po * pow(vv, 2)) / 2);
        return (-F_P+ F_Y)/ (m*vv)  - ((g  * cos(ii))) * (1-pow(vv,2)/(g*(constants::earth_radius+hh))) /vv;
    }

    double equations::fdN(double hh, double vv, double ii)
    {
        return (vv /(constants::earth_radius+hh)) * cos(ii);
    }

    double equations::fdH(double vv, double ii)
    {
        return vv * sin(ii);
    }

