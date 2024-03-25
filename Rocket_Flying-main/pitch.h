#ifndef PITCH_H
#define PITCH_H

#include "block.h"
#include <cmath>
#include <iostream>
#include <QVector>
#include "mass.h"
#include "airforce.h"
#include "focus.h"
#include "equations.h"
#include "atmosphere.h"
#include "eastwind.h"
#include "alpha.h"

class pitch
{
public:
    pitch();

    // Глобальные векторы
    QVector<double>lin;
    QVector<double>sinn;
    QVector<double> jinn, jinn2;
    QVector<double>CM;
    QVector<double>ALI_1;
    QVector<double>ALI_2;
    QVector<double>res;
    QVector<double>TET_1;
    QVector<double>TET_2;
    QVector<double>center_1;
    QVector<double>center_2;
    QVector<double>be;
    QVector<double>pi;
    QVector<double>yu_1;
    QVector<double>yu_2;
    QVector<double>mass_1;
    QVector<double>mass_2;
    QVector<double> xn;
    QVector<double> v_1, v_2, v_3;
    QVector<double> Long_1, Long_2, H1, H2, H3;
    QVector<double> angle, b1, b2;
    QVector<double> P1, P2;
    QVector<double> f1;
    QVector<double> Lon, Lonre;
    QVector<double> w, pc2;
    QVector<double> cy2;
    QVector<double> dyn1, dyn2;
    QVector<double> lenght_R;


    std::unique_ptr<block> fir = std::make_unique<block>();
    std::unique_ptr<block> sec = std::make_unique<block>();


    double Na=0.1, Mah_1, Mah_2,  time = 0;
    int e=0;
    int uj=0;
    int ten=0;
    double V1=0, Y1=0, H11=0, X1=0;
    double V2=0, Y2=0, H22=0, X2=0;
    double xXY = 0, yXY = 0,  VX = 0.3, VY = 0.3, velXY = 0.3, trjXY = M_PI/2, norXY = 0;
    double zXY = 0, VZ  = 0.3;

    double mpn=15000;
    double mb[2] {391000, 107000};
    double s[2] {7, 10};
    double D = 4.1;
    double Imp[2] {3300, 3700};
    double T_sep[2] {3, 3};
    double Ratio = 3.5;
    double h = 0.1;

    double M_Rocket;

    int count;
    double Lmax;
    double Iz, Izmax, Sx, Ix, Ixmax;
    //double gl_c;
    double gl_cmax;
    double Wind1;
    double Wind2;
    double CILCON;

    double k1 = 360;
    double k2 = 383;
    double k3 = 405;
    double k4 = 440;
    double kk1 = 0.2;
    double kk2 = 0.22;

    double Smid;

    double M_stage[2];
    double T_stage [2];
    double Ott;
    double CX_1, CY_1;
    double CX_2, CY_2;
    double dN;
    double m_O[2], m_C[2];
    double d_O[2], d_C[2];
    double S_o[2], S_c[2];
    double I_o[2], I_c[2];
    double Imp_t, CF;
    double pitch_angle;
    double bpr;
    double HSP_1, HSP_p_1, VHSP_1;
    double HSP_2, HSP_p_2;
    double MHSP_1;
    double MHSP_2, VHSP_2;
    double Ott_1, Ott_2 ;
    double H_1;
    double dep;
    double deo, dec;
    double amax;
    double X_oneC;
    double X_twoC;
    double MaxTime;
    double T_fuel[2];

    void pitch_calculations(double (&kalph)[3], double (&peng)[2]);

};

#endif // PITCH_H
