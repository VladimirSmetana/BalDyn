#ifndef EQUATIONS_H
#define EQUATIONS_H
#include <cmath>

class equations
{
    private:
    double po;
    double S;
    double g, m, I;
    double CX, CY;
    double PENG, alpha;
    double F_P, F_Y, F_X;
    double const  R = 6371000;

    public: 
    equations (double po, double S, double g, double m, double CX, double CY, double PENG, double alpha);
    // Баллистические уравнения
    double fdV(double vv, double ii);
    double fdY(double hh, double vv, double ii);
    double returndV(double vv, double ii);
    double returndY(double hh, double vv, double ii);
    double fdN(double hh, double vv, double ii);
    double fdH(double vv, double ii);

};

#endif // EQUATIONS_H



