#include "atmosphere.h"

    atmosphere::atmosphere (double H)
    {
        for (int i = 1; i < 15; i++)
        {
            if (H >= HT[i - 1] && H < HT[i]) { T = (TT[i-1])+(H-HT[i-1])*(TT[i]-TT[i-1])/ (HT[i] - HT[i - 1]); };
        }

        for (int i = 1; i < 8; i++)
        {
            if (H >= HT[i - 1] && H < HT[i]) { Tm = (TMM[i - 1]) + (H - HT[i - 1]) * (TMM[i] - TMM[i - 1]) / (HT[i] - HT[i - 1]); };
        }


        if (H<94000)
        {


            /// Введение атмосферы

            /// Коэффициенты полинома молярной массы
            B[0] = 46.9083;  B[1] = -29.71210 * pow(10, -5); B[2] = 12.08693 * pow(10, -10); B[3] = -1.85675 * pow(10, -15);

            /// Молярная масса
            Mol = Mc;


            Bett = (7466 * pow(H, 3) - 1262795028 * pow(H, 2) + 61597340039789 * H - 833732588564247562) * pow(10, -20);
            /// Давление
            if (abs(Bett) < 0.0000001) { pp = log(101325); Hs = H - 0.1; P = exp(pp - (0.434294 * gc / (r * T)) * (H- 0)); }  //P = exp(pp - (0.434294 * gc / (r * T)) * (H - Hs)); }
            if (abs(Bett) >= 0.0000001) { pp = log(101325); Hs = H-0.1; P = exp(pp - (gc * log((Tm + Bett *  (H - 0))  / Tm)) / (Bett * r)); }
            Pap = 101325 * exp(-gc*H*Mc/(RB*T));
            /// Плотность
            po = (P * Mol) / (RB * T);
            /// Концентрация частиц воздуха
            n = 7.243611 * pow(10, 22) * P / T;



            tCel = T - 273.15;
            yyd = po * g;
            Hmas = (RB / Mol) * (T / g);
            a = 20.046796 * sqrt(T);
            vsred = 145.50685 * T / Mol;
            lsred = 2.332376 * pow(10, -5) * T / P;
            omega = 6.238629 * pow(10, 6) * P / sqrt(T * Mol);
            lamb = (2.648151 * pow(10, -3) * pow(T, 3 / 2)) / (T + 245.4 * pow(10, -(12 / T)));
        }
        g = gc * pow(R / (R + H), 2);
    }


    double atmosphere::get_T()
    {
        return T;
    }

    double atmosphere::get_n()
    {
        return n;
    }
    double atmosphere::get_pressure()
    {
        return P;
    }
    double atmosphere::get_density()
    {
        return po;
    }

    double atmosphere::get_AOG()
    {
        return g;
    }

    double atmosphere::get_SV()
    {
        return a;
    }
