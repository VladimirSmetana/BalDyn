#include <QDebug>
#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H
#include <cmath>

#endif // ATMOSPHERE_H

class atmosphere
    {
    private:
    double H;
    double po;
    double Bett, mstep, pp;
    double tCel, Hmas, vsred, lsred, lamb;
    double B[4];
    double A[5];

    double HT[15]{1     ,  11019,  32000 , 47350 , 71802 , 86152 , 104128, 120000 , 140000, 160000, 200000, 325000, 400000, 600000, 1200000};
    double TT[15]{288.15,  216.65, 228.65, 270.65, 214.65, 186.65, 203.81, 334.417, 559.6,  695.6,  834.4,  941.9,  984.65, 995.9,  1000};
    double TMM[8]{288.15,  216.65, 228.65, 270.65, 214.65, 186.65, 212.0 , 380.60 };
    double dHT[14];

    double Bst [11]{-0.0065, -0.0065, 0.0000 , 0.0010, 0.0028, 0, -0.0028, -0.0020, 0, 0.0030, 0.0110};
    double Hst [11] {1,  11019, 20630, 32000 , 47350 , 51412, 71802 , 86152 , 95411, 104128, 120000};

    double const
        Mc = 28.964420,
        gc = 9.80665,
        ac = 340.294,
        Hpc = 8434.5,
        nc = 25.471 * pow(10, 24),
        pc = 101325.0,
        Tc = 288.15,
        vc = 458.94,
        yc = 12.013,
        nuc = 14.607 * pow(10, -6),
        muc = 17.894 * pow(10, -6),
        lac = 25.343 * pow(10, -3),
        omegac = 6.9193 * pow(10, 9),
        poc = 1.2250,
        Na = 602.257 * pow(10, 24),
        RB = 8314.32, r = 287.05287,
        SOS = 110.4,
        BS = 1.458 * pow(10, -6),
        hi = 1.4,
        b = 0.365 * pow(10, -9),
        R = 6371000,
        Hp = (R * H) / (R + H);


        double Hs;
        double Pap;
        double Mol = Mc, g = gc, T = Tc, Tm = Tc * Mc / Mol, P = pc, n = nc, yyd = yc, a = ac, omega = omegac;
        double t;
        double const PI =  3.1415926535;
        double D = 2.66;
        double S = PI*pow(D,2)/4;

        public:
        atmosphere (double H);

        double get_T();
        double get_n();
        double get_pressure();
        double get_density();
        double get_AOG();
        double get_SV();
    };
