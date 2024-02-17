#ifndef PITCH_H
#define PITCH_H
#include "alpha.h"
#include "atmosphere/atmosphere.h"
#include "focus.h"
#include "atmosphere/airforce.h"
#include <iostream>
#include "equations.h"
#include "atmosphere/eastwind.h"

class pitch
{
public:
    pitch();

    double HSP_1, HSP_p_1, VHSP_1;
    double HSP_2, HSP_p_2;
    double MHSP_1;
    double MHSP_2, VHSP_2;

    double Na=0.1, Mah_1, Mah_2,  time = 0;
    int e=0;
    int uj=0;
    int ten=0;
    double V1=0, Y1=0, H11=0, X1=0;
    double V2=0, Y2=0, H22=0, X2=0;
    double xXY = 0, yXY = 0,  VX = 0.3, VY = 0.3, velXY = 0.3, trjXY = M_PI/2, norXY = 0;
    double zXY = 0, VZ  = 0.3;

    double CX_1, CY_1;
    double CX_2, CY_2;
    double Wind1;
    double Wind2;
    double dN;
    double pitch_angle;
    double Len[2];


    void pitch_calculations
        (double time,
         double T_stage, //T_stage[0]
         double (&vel)[2],
         double (&k)[4],
         double (&kalph)[3],
         double (&H)[2], //fir/sec->tY
         double (&anY)[2], //fir/sec->anY
         double (&Mah)[2], // Mah_1, Mah_2
         double Smid,
         double (&mass)[2],
         double (&peng)[2],
         double Ott, // Не забудь поставить изменение величины через &
         double h,
         double mpn);
};

#endif // PITCH_H
