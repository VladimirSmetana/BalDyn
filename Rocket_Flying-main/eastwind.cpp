#include "eastwind.h"

eastwind::eastwind (double H):H(H){}

    double eastwind::WSol()
    {
        for (int i = 0; i < 17; i++)
        {
            if (H>=94) {W=0;}
            if (H >= HW[i] && H < HW[i+1])  {W = WW[i] + (WW[i+1]-WW[i])/(HW[i+1]-HW[i])*(H-HW[i]);}
        }
        return W;
    }


