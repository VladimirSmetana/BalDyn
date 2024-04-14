#ifndef EQUATIONS_H
#define EQUATIONS_H
#include <cmath>
#include <QVector>
#include <QDebug>
class equations
{
    private:

    double S;
    double g, m, I;
    double CX, CY;

    double F_P, F_Z, F_Y, F_X, F_G, F_W;
    double wind;
    double const  R = 6371000;

    public:
    equations (double S, double g, double m, double CX, double CY, double alpha, double wind, double time);
    double po;
    double PENG, alpha;
    // Баллистические уравнения
    double fdV(double vv, double ii);
    double fdV_rk(double vv, double time);
    double fdY(double hh, double vv, double ii);
    double fdY_rk(double yy, double time);
    double returndV(double vv, double ii);
    double returndY(double hh, double vv, double ii);
    double fdN(double hh, double vv, double ii);
    double fdH(double vv, double ii);

    double dVX(double vv, double ii, double N);
    double dVY(double vv, double ii, double N);
    double dVZ(double vv, double ii, double N);

    double peng_rk(double time);


    double mass_rk(double time);

    double Y_rk;
    double H_rk;
    double V_rk;
    double time;

    QVector<double> mtm;
    QVector<double> ttm;

    double RK(double V, double t, double h, double (*fc)(double, double));
};

#endif // EQUATIONS_H



