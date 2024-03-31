#ifndef PITCH_H
#define PITCH_H

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




    double Na=0.1, Mah_1, Mah_2,  time = 0;
    int e=0;
    int uj=0;
    int ten=0;
    double V1=0, Y1=0, H11=0, X1=0;
    double V2=0, Y2=0, H22=0, X2=0;
    double xXY = 0, yXY = 0,  VX = 0.3, VY = 0.3, velXY = 0.3, trjXY = M_PI/2, norXY = 0;
    double zXY = 0, VZ  = 0.3;

    double D = 0.102;
    double h = 0.01;

    double M_Rocket;

    int count;
    double Lmax;
    double Iz, Izmax, Sx, Ix, Ixmax;

    //double gl_c;
    double gl_cmax;
    double Wind1;
    double Wind2;
    double CILCON;


    double Smid;

    double M_stage[2];
    double T_stage [2];
    double Ott;
    double CX_1, CY_1;
    double CX_2, CY_2;
    double dN;
    double m_O;
    double d_O;
    double S_o;
    double I_o;
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
    double T_fuel = 2.17;
    double gl_c, foc;

    double anY;
    double tY, tX;
    double Peng_control;
    double Ssumm;
    double Hmax;
    double Vmax;

    void pitch_calculations(double (&kalph)[3], double (&peng)[2]);

};

#endif // PITCH_H
