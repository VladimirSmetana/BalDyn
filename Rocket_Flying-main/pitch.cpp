#include "pitch.h"

pitch::pitch()
{

}

void pitch::pitch_calculations()
//    (double time,
//     double T_stage, //T_stage[0]
//     double (&vel)[2],
//     double (&k)[4],
//     double (&kalph)[3],
//     double (&H)[2], //fir/sec->tY // Не забудь поставить изменение величины через &
//     double (&anY)[2], //fir/sec->anY
//     double (&Mah)[2], // Mah_1, Mah_2
//     double Smid,
//     double (&mass)[2],
//     double (&peng)[2],
//     double Ott, // Не забудь поставить изменение величины через &
//     double h,
//     double mpn)
{
    // Программа угла атаки
    // ________________________________________________________________________
    atmosphere Atm_1 (H[0]);
    atmosphere Atm_2 (H[1]);
    eastwind W1 (H[0]/1000);
    eastwind W2 (H[1]/1000);
    airforce Qus_1 (Mah[0]);
    airforce Qus_2 (Mah[1]);


    alpha_class alph_1 (vel[0],  kalph [1], kalph [2], time,    T_stage, 0,   k[1], k[2]);
    alpha_class alph_2 (vel[1],  kalph [1], 0,         time,    200,     180, k[1], k[2]);

    // Учет параметров атмосферы

    //HSP = (P.get_density()/2)*pow(V,2);
    HSP_p_1 = HSP_1;
    HSP_1 = (Atm_1.get_density()/2)*pow(vel[0],2);
    HSP_p_2 = HSP_2;
    HSP_2 = (Atm_2.get_density()/2)*pow(vel[1],2);
    Mah[0] = vel[0]/Atm_1.get_SV();
    Mah[1] = vel[1]/Atm_2.get_SV();


    //std::cout << Focus << std::endl;
    //Focus = M.Focus(Mah_1, D, M.get_lengo(), M.get_wgo());
    //qDebug()<<M.K[10]+d_C[0];

    if (time<T_stage) {CX_1=Qus_1.getCX();  } else {CX_1=0;  }
    if (time<T_stage) {CY_1=Qus_1.getCY();  } else {CY_1=0;  }
    CX_2=Qus_2.getCX();
    CY_2=Qus_2.getCY();
    //bpr = ((Atm_1.get_density()/2*pow(vel[0],2))*Smid*fir->L*CY_1*fir->alpha)/(peng[0]*(fir->L-fir->gl_c));

    equations B_1 (Atm_1.get_density(), Smid, Atm_1.get_AOG(), mass[0], CX_1, CY_1, peng[0], alph_1.A(), Wind1);
    equations B_2 (Atm_2.get_density(), Smid, Atm_2.get_AOG(), mass[1], CX_2, CY_2, peng[1], alph_2.A(), Wind2);
    alpha[0] = alph_1.A();
    alpha[1] = alph_2.A();
    AOG[0] = Atm_1.get_AOG();
    AOG[1] = Atm_2.get_AOG();

    //dV = B_1.fdV(vel[0], Y[0]);
    dN = B_1.fdN(H[0], vel[0], anY[0]);

    Ott = anY[0]-Na;
    pitch_angle = Ott-alph_1.A()/57.3;

    Len[0] += h * (vel[0]* cos(anY[0])+X1)/2;
    Len[1] += h * (vel[1]* cos(anY[1])+X2)/2;

    X1 = vel[0]* cos(anY[0]);
    X2 = vel[1]* cos(anY[1]);


    Wind1 = W1.WSol();
    Wind2 = W2.WSol();

    if (time<120 &&  HSP_1<HSP_p_1 && e<1)
    {

        MHSP_1 = HSP_1;
        VHSP_1 = vel[0];
        e+=1;
    }

    if (time<120 &&  HSP_2<HSP_p_2 && e<1)
    {

        MHSP_2 = HSP_2;
        VHSP_2 = vel[1];
        e+=1;
    }
    //  if  (HSP_2>90000)  {HSP_2=HSP_1;}
    time+=h;
    Na  += dN*h;
    if (mass[0]>mpn)
    {

        //double me = Y[0];

        H[0] += vel[0]* sin(anY[0]) *h;

//        K1 = B_1.fdV(vel[0], Y[0]);
//        K2 = B_1.fdV(vel[0]+h/2*K1, Y[0]+h/2);
//        K3 = B_1.fdV(vel[0]+h/2*k[1], Y[0]+h/2);
//        K4 = B_1.fdV(vel[0]+h*k[2], Y[0]+h);
//        vel[0]   += (K1 + k[1]*2 + k[2]*2 + K4)/6*h;

//        K1 = B_1.fdY(fir->tY, vel[0], Y[0]);
//        K2 = B_1.fdY(fir->tY+h/2, vel[0]+h/2, Y[0]+h/2*K1);
//        K3 = B_1.fdY(fir->tY+h/2, vel[0]+h/2, Y[0]+h/2*k[1]);
//        K4 = B_1.fdY(fir->tY+h, vel[0]+h, Y[0]+h*k[2]);
//        Y[0] += (K1 + k[1]*2 + k[2]*2 + K4)/6*h;

        //vel[0] += Runge_Kutt(&B_1.fdV, vel[0], Y[0], h);
        H[0] += (B_1.fdY(H[0], vel[0], anY[0])+Y1)/2*h;


        H11 = vel[0]* sin(anY[0]);
        V1 = B_1.fdV(vel[0], anY[0]);
        Y1 = B_1.fdY(H[0], vel[0], anY[0]);


        std::cout << zXY/1000  << std::endl;
        VX += h*B_1.dVX(velXY, Ott, Na);
        VY += h*B_1.dVY(velXY, Ott, Na);
        VZ += h*B_1.dVZ(velXY, Ott, Na);
        velXY = sqrt(VX*VX+VY*VY+VZ*VZ);
        trjXY = acos(VX/velXY);
        xXY += h*VX * cos(anY[0]) / cos(Ott);
        yXY += h*VY * sin(anY[0]) / sin(Ott);
        zXY += h*VZ;
        norXY = atan(xXY/(6371000+yXY));
        //


        /*

*/

    }

    if (time >T_fuel)
    //if ((time>k1 && time<k[1]) || (time>k[2] && time<k4))
    {
        H[1] += (vel[1]* sin(anY[1])+H22)/2*h;
        vel[1]  += (B_2.returndV(vel[1], H[1])+V2)/2*h; //return
        anY[1]  += (B_2.returndY(H[1], vel[1], anY[1])+Y2)/2*h;  //return


        V2 = B_2.returndV(vel[1], anY[1]);
        Y2 = B_2.returndY(H[1], vel[1], anY[1]);
        H22 = vel[1]* sin(anY[1]);

    }
    else
    {
        H[1] += (vel[1]* sin(anY[1])+H22)/2*h;
        vel[1]  += (B_2.fdV(vel[1], anY[1])+V2)/2*h;
        anY[1]  += (B_2.fdY(H[1], vel[1], anY[1])+Y2)/2*h;

        V2 = B_2.fdV(vel[1], anY[1]);
        Y2 = B_2.fdY(H[1], vel[1], anY[1]);
        H22 = vel[1]* sin(anY[1]);
    }


    // ________________________________________________________________________

}
