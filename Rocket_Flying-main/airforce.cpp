#include "airforce.h"

    airforce::airforce (double Mah)
    {

        if ((Mah > 0) && (Mah <= 0.1)) CY = 0.757;
        if ((Mah > 0.1) && (Mah <= 0.3)) CY = 0.789;
        if ((Mah > 0.3) && (Mah <= 0.5)) CY = 0.810;
        if ((Mah > 0.5) && (Mah <= 0.7)) CY = 0.795;
        if ((Mah > 0.7) && (Mah <= 0.8)) CY = 0.846;
        if ((Mah > 0.8) && (Mah <= 0.9)) CY = 0.977;
        if ((Mah > 0.9) && (Mah <= 1.0)) CY = 1.121;
        if ((Mah > 1.0) && (Mah <= 1.1)) CY = 1.294;
        if ((Mah > 1.1) && (Mah <= 1.3)) CY = 0.843;
        if (Mah  > 1.3) CY = 0.699;


        if ((Mah > 0) && (Mah <= 0.1)) CX = 0.571;
        if ((Mah > 0.1) && (Mah <= 0.3)) CX = 0.510;
        if ((Mah > 0.3) && (Mah <= 0.5)) CX = 0.485;
        if ((Mah > 0.5) && (Mah <= 0.7)) CX = 0.470;
        if ((Mah > 0.7) && (Mah <= 0.8)) CX = 0.497;
        if ((Mah > 0.8) && (Mah <= 0.9)) CX = 0.537;
        if ((Mah > 0.9) && (Mah <= 1.0)) CX = 0.660;
        if ((Mah > 1.0) && (Mah <= 1.1)) CX = 0.821;
        if ((Mah > 1.1) && (Mah <= 1.3)) CX = 0.845;
        if (Mah  > 1.3) CX = 0.762;


//        if ((Mah > 0.3) && (Mah <= 0.5)) CY = 3.18 - 0.660 * (Mah - 1.1);
//        if ((Mah > 1.6) && (Mah <= 3.6)) CY = 2.85 + 0.350 * (Mah - 1.6);
//        if (Mah > 3.6) CY = 12.78/Mah;

//        if (Mah <= 0.8) { CX = 0.29; };
//        if (Mah > 0.8 && Mah < 1.068) { CX = Mah-0.51; };
//        if (Mah >= 1.068) { CX = 0.597/Mah; };
//        if (CX > 1) { CX = 1; };
    }

    double airforce::getCX()
    {
        return CX;
    }

    double airforce::getCY()
    {
        return CY;
    }
