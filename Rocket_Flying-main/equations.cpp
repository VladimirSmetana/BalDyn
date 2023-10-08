#include "equations.h"
    equations::equations (double po, double S, double g, double m, double CX, double CY, double PENG, double alpha)
    {
        this->po = po;
        this->S = S;
        this->g = g;
        this->m = m;
        this->CX = CX;
        this->CY= CY;
        this->PENG = PENG;
        this->alpha = alpha;
    }

    // Баллистические уравнения
    double equations::fdV(double vv, double ii)
    {
        F_P = (PENG * cos((M_PI * alpha) / 180));
        F_X = CX * S * po * pow(vv, 2) / 2;
        return  F_P/m -  F_X/m - g * sin(ii);
    }

    double equations::fdY(double hh, double vv, double ii)
    {
        F_P = (PENG * sin((M_PI * alpha) / 180));
        F_Y = (CY * ((M_PI * alpha) / 180) * S * (po * pow(vv, 2)) / 2);
        return (F_P+ F_Y)/ (m*vv)  - ((g  * cos(ii))) * (1-pow(vv,2)/(g*(R+hh))) /vv;
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
        return (-F_P+ F_Y)/ (m*vv)  - ((g  * cos(ii))) * (1-pow(vv,2)/(g*(R+hh))) /vv;
    }

    double equations::fdN(double hh, double vv, double ii)
    {
        return (vv /(R+hh)) * cos(ii);
    }

    double equations::fdH(double vv, double ii)
    {
        return vv * sin(ii);
    }

