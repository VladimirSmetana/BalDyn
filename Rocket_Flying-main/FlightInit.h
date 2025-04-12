#ifndef FLIGHTINIT_H
#define FLIGHTINIT_H

#include <QVector>
#include "block.h"

class FlightInit
{
public:
    FlightInit(double (&kalph_)[3], double (&kpeng_)[2]);

    double m_O[2], m_C[2];
    double d_O[2], d_C[2];
    double S_o[2], S_c[2];
    double I_o[2], I_c[2];
    double T_sep[2] {3, 3};
    double Ratio = 3.5;
    double h = 0.1;
    double peng [2];
    double m_fuel[2];
    double m_dry[2];
    double m_furet, m_reC, m_reO;
    double L1,L2;
    double mpn=15000;
    double mb[2] {391000, 107000};
    double s[2] {7, 10};
    double D = 4.1;
    double zap = 0;
    double M_Rocket;
    int count;
    std::unique_ptr<block> fir = std::make_unique<block>();
    std::unique_ptr<block> sec = std::make_unique<block>();

    double Smid;
private:
    double kalph[3];
    double kpeng[2];

    void m_calculate_initial_values();
    //void calculate_length();
};

#endif // FLIGHTINIT_H
