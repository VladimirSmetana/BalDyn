#include "focus.h"


double focus::Focus (double Mah, double D, double Lgo, double wgo, double CIL, double CILCON)
    {
        KM = (pow(abs(1 - pow(Mah, 2)), 0.5)) / CIL;
        if (CILCON > 0.0 && CILCON <= 0.5) { if (Mah < 1) { dXF = -0.03 * pow(KM, 2) - 0.04 * KM + 0.09; } if (Mah >= 1) { dXF = -0.03 * pow(KM, 2) + 0.06 * KM + 0.09; }; }
        if (CILCON > 0.5 && CILCON <= 1.0) { if (Mah < 1) { dXF = -0.03 * pow(KM, 2) - 0.04 * KM + 0.09; } if (Mah >= 1) { dXF = -0.03 * pow(KM, 2) + 0.16 * KM + 0.10; }; }
        if (CILCON > 1.0 && CILCON <= 2.0) { if (Mah < 1) { dXF = -0.03 * pow(KM, 2) - 0.04 * KM + 0.09; } if (Mah >= 1) { dXF = -0.05 * pow(KM, 2) + 0.34 * KM + 0.05; }; }
        if (CILCON > 2.0 && CILCON <= 3.0) { if (Mah < 1) { dXF = -0.03 * pow(KM, 2) - 0.04 * KM + 0.09; } if (Mah >= 1) { dXF = -0.07 * pow(KM, 2) + 0.42 * KM + 0.01; }; }
        if (CILCON > 3.0)                  { if (Mah < 1) { dXF = -0.03 * pow(KM, 2) - 0.04 * KM + 0.09; } if (Mah >= 1) { dXF = -0.08 * pow(KM, 2) + 0.51 * KM - 0.02; }; }
        XF = Lgo - wgo / ((M_PI * pow(D, 2)) / 4) + Lgo * dXF;
        return XF;
    }
