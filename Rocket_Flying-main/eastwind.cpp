#include "eastwind.h"

    eastwind::eastwind (double H)
    {
        this->H = H;
    }
    double eastwind::WSol()
    {
        for (int i = 0; i < 17; i++)
        {
//            if (H >= 0.1 && H < 6)  W = 1.9;
//            if (H >= 6 && H < 12)  W = 8;
//            if (H >= 12 && H < 18)  W = 15;
//            if (H >= 18 && H < 24)  W = 18;
//            if (H >= 24 && H < 30)  W = 24;
//            if (H >= 30 && H < 36)  W = 12;
//            if (H >= 36 && H < 42)  W = 10;
//            if (H >= 42 && H < 48)  W = 8;
//            if (H >= 48 && H < 54)  W = 6;
//            if (H >= 54 && H < 60)  W = 5;
//            if (H >= 60 && H < 66)  W = 4;
//            if (H >= 66 && H < 72)  W = 3;
//            if (H >= 72 && H < 84)  W = 2;
//            if (H >= 84 && H < 94)  W = 1;
            if (H>=94) {W=0;}
            if (H >= HW[i] && H <= HW[i+1])  {W = WW[i] + (WW[i+1]-WW[i])/(HW[i+1]-HW[i])*(H-HW[i]);}
        }
        return W;
    }


