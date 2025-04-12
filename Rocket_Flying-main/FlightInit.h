#ifndef FLIGHTINIT_H
#define FLIGHTINIT_H

#include <QVector>

#include "mass.h"
#include "block.h"

class FlightInit
{
public:
    FlightInit(double (&thrustToWeght)[2]);

private:
    void calculate_initial_values();
    void calculate_length();
    void calculate_mass_parameters();
    void calculate_inertia();
    void calculate_area_and_inertia();
    void initialize_time_parameters();

public:
    double m_thrust_to_weight[3];
    mass M;
    double mb[2];
    double D;
    double mpn;
    double h;
    double s[2];
    double peng[2];

    double m_fuel[2];
    double m_dry[2];
    double m_furet, m_reC, m_reO;
    double L1,L2;
    double M_Rocket;

    std::unique_ptr<block> fir = std::make_unique<block>();
    std::unique_ptr<block> sec = std::make_unique<block>();

    double Smid;
    double M_stage[2];
    double T_stage [2];
    double Iz, Izmax, Sx, Ix, Ixmax;

    QVector<double> H1;
    QVector<double> H2;
    QVector<double> xn;

    double T_fuel[2];

    double m_O[2], m_C[2];
    double d_O[2], d_C[2];
    double S_o[2], S_c[2];
    double I_o[2], I_c[2];

    double T[4];

    double Lmax;
    double zap = 0;
    int count;

    double Imp[2] {3300, 3700};
    double T_sep[2] {3, 3};
    double Ratio;
};

#endif // FLIGHTINIT_H
