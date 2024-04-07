#include "equations.h"
    equations::equations (double S, double g, double m, double CX, double CY, double alpha, double wind, double time)
    {
        this->S = S;
        this->g = g;
        this->m = m;
        this->CX = CX;
        this->CY= CY;
        this->alpha = alpha;
        this->wind = wind;
        this->time = time;

    }

    // Баллистические уравнения
    double equations::fdV(double vv, double ii)
    {
        F_P = (PENG * cos((M_PI * alpha) / 180));
        F_X = CX * S * po * pow(vv, 2) / 2;
        return  F_P/m -  F_X/m - g * sin(ii);
    }

    double equations::fdV_rk(double vv, double time)
    {
//        double ms = mass_rk(time);
        //qDebug() << ms - m;
        F_P = (peng_rk(time) * cos((M_PI * alpha) / 180));
        F_X = CX * S * po * pow(vv, 2) / 2;
        return  F_P/mass_rk(time) -  F_X/mass_rk(time) - g * sin(Y_rk);
    }

    double equations::dVX(double vv, double ii, double N)
    {
        double J = 8*M_PI/180;
        F_P = PENG * cos( (M_PI * alpha) / 180 + ii);
        F_X = CX * S * po * pow(vv, 2) / 2 * cos(ii) * cos(J);
        F_Y = (CY  * S * (po * pow(vv, 2)) / 2) * sin(ii);
        F_Z = - CY * S * po * pow(vv, 2) / 2 * cos(ii) * sin(J);
        F_G = m*g*sin(N);
        return (F_P - F_X - F_Y - F_G)/m;
    }

    double equations::dVY(double vv, double ii, double N)
    {
        double J = 8*M_PI/180;
        F_P = PENG * sin( (M_PI * alpha) / 180 + ii);
        F_X = -CX * S * po * pow(vv, 2) / 2 * sin(ii) * cos(J);
        F_Y = (CY * S * (po * pow(vv, 2)) / 2) * cos(ii);
        F_Z = CY * S * po * pow(vv, 2) / 2 * sin(ii) * sin(J);
        F_G = m*g*cos(N);
        return (F_P - F_X + F_Y - F_G)/m;
    }

    double equations::dVZ(double vv, double ii, double N)
    {
        double J = 8*M_PI/180;
        F_X = -CX * S * po * pow(vv, 2) / 2 * sin(ii) * cos(J);
        F_Z = (CY * S * (po * pow(vv, 2)) / 2) * cos(J);
        F_W = (CY * S * (po * pow(wind, 2)) / 2);
        F_G = m*sin(N);
        return (F_X+F_Z-F_G-F_W)/m;
    }

    double equations::fdY(double hh, double vv, double ii)
    {
        F_P = (PENG * sin((M_PI * alpha) / 180));
        F_Y = (CY * ((M_PI * alpha) / 180) * S * (po * pow(vv, 2)) / 2);
        return (F_P+ F_Y)/ (m*vv)  - ((g  * cos(ii))) * (1-pow(vv,2)/(g*(R+hh))) /vv;
    }

    double equations::returndV(double vv, double ii)
    {
        F_P = (PENG * cos((M_PI * alpha) / 180));
        F_X = CX * S * po * pow(vv, 2) / 2;
        return  -F_P/m -  F_X/m - g * sin(ii);
    }

    double equations::returndY(double hh, double vv, double ii)
    {
        F_P = (PENG * sin((M_PI * alpha) / 180));
        F_Y = (CY * ((M_PI * alpha) / 180) * S * (po * pow(vv, 2)) / 2);
        return (-F_P+ F_Y)/ (m*vv)  - ((g  * cos(ii))) * (1-pow(vv,2)/(g*(R+hh))) /vv;
    }

    double equations::fdN(double hh, double vv, double ii)
    {
        return (vv /(R+hh)) * cos(ii);
    }

    double equations::fdH(double vv, double ii)
    {
        return vv * sin(ii);
    }

    double equations::peng_rk(double time)
    {
        double png=0;
        static double P_matrix [12] {100 , 921.22, 700, 665.08, 674.6, 681.21, 668.16, 640.74, 600, 538.04, 353.31, 0};
        static double T_matrix [12] {0.01, 0.08, 0.34, 0.44, 0.65, 1.00, 1.21, 1.45, 1.70, 2.00, 2.10, 2.18};
        if (time<=2.18)
        {
            for (int i = 0; i < 12; i++)
            {
                if (time >= T_matrix[i] && time <= T_matrix[i+1])  {png = P_matrix[i] + (P_matrix[i+1]-P_matrix[i])/(T_matrix[i+1]-T_matrix[i])*(time-T_matrix[i]);}
            }
        }
        else {png == 0;}
        return png;
    }

    double equations::mass_rk(double time)
    {
        double res;
        double peng = peng_rk(time);
        static double Imp = 1150;
        //if (time == this->time) {return m;};
        double del = time - this->time;
        if (time<2.18) {res = m-peng/Imp*del;}
        else res = m;
        return res;
//        mtm.push_back(m);
//        ttm.push_back(time);
//        for (int i;i<mtm.length();i++)
//        {
//            if (time >= ttm[i - 1] && time < ttm[i])
//            {
//                return mtm[i];
//            }
//        }

        //return m;
//        double M_rocket = 5.32;
//        double peng;
//        static double Imp = 1150;

//        if (time <= 2.18)
//        {
//            for (int i=0;i<time;i+=0.01)
//            {
//                peng = peng_rk(i);
//                M_rocket -= peng/Imp*i;
//            }
//            return M_rocket;
//        }
//        else
//        {
//            return 4.12;
//        }

    }

