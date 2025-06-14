#ifndef FLIGHTINIT_H
#define FLIGHTINIT_H

#include <QVector>
#include "FlightType.h"
#include "mass.h"
#include "rockets/Rocket.h"

class FlightInit {
public:
    FlightInit(double (&kalph_)[3], double (&kpeng_)[2]);
    std::unique_ptr<FlightType> insertion = std::make_unique<FlightType>();
    std::unique_ptr<FlightType> landing = std::make_unique<FlightType>();
    Rocket rocket;
    double Sx;
    double Iz;
    double Ix;
    double Ixmax;
    double Izmax;
    double T_fuel[2];
protected:
    double m_O[2], m_C[2];
    double d_O[2], d_C[2];
    double S_o[2], S_c[2];
    double I_o[2], I_c[2];
    double T_sep[2] {3, 3};

    double peng [2];
    double m_fuel[2];
    double m_dry[2];
    double m_furet, m_reC, m_reO;

    double M_Rocket;
    int count;
    double M_stage[2];

    double mb[2];
    double Imp[2];
    double s[2] {7, 10};
    double zap;
    double h;

    double Smid;
    mass M;

    double T_stage [2];
    double T[4];

private:
    double kalph[3];
    double kpeng[2];

    void m_calculate_initial_values();
    void m_calculate_mass_parameters();
    void calculate_inertia();
    void calculate_area_and_inertia();
    void initialize_time_parameters();

};

#endif // FLIGHTINIT_H
