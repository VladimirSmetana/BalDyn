#include "FlightInit.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>

#include "Constants.h"
#include <QDebug>

#include "rockets/RocketConfigurator.h"

namespace {
constexpr auto c_second_stage_length = 21.5;
}

FlightInit::FlightInit(double (&kalph_)[3], double (&kpeng_)[2]) {
    std::copy(std::begin(kalph_), std::end(kalph_), std::begin(kalph));
    std::copy(std::begin(kpeng_), std::end(kpeng_), std::begin(kpeng));

    m_calculate_initial_values();
    M.MCI_f(rocket->payload_mass,
            rocket->maximum_diameter,
            rocket->block_mass[0],
            rocket->block_mass[1],
            rocket->structural_value[0],
            rocket->structural_value[1],
            peng[0],
            peng[1]);
    m_calculate_mass_parameters();
    initialize_time_parameters();
    calculate_area_and_inertia();
    calculate_landing_values();
}

void FlightInit::m_calculate_initial_values() {
    qDebug() << "\n" << "-- INITIAL DATA --" << "\n";
    qDebug() << "1st attack coefficient:" << kalph[1];
    qDebug() << "2d attack coefficient :"  << kalph[2];
    qDebug() << "1st thrust-to-weight coefficient:" << kpeng[0];
    qDebug() << "2d thrust-to-weight coefficient :"  << kpeng[1];

    RocketType rocketType = RocketType::master;
    rocket = std::make_unique<Rocket>(RocketConfigurator(rocketType));

    for (int i=0; i<rocket->block_number; i++) {
        peng[i] = kpeng[i] * constants::acceleration_of_gravity * rocket->stage_mass[i];
    }

    h  = c_step;

    m_reC = rocket->fuel_landing_mass / (rocket->components_ratio+1);
    m_reO = rocket->fuel_landing_mass * (rocket->components_ratio) / (rocket->components_ratio+1);
    M_Rocket = rocket->payload_mass;
    insertion->m_t = M_Rocket;
    Smid = M_PI * pow(rocket->maximum_diameter, 2) / 4;
    insertion->V = 0;

    count = 0;
}

void FlightInit::m_calculate_mass_parameters() {
    // something weird
    rocket->s_mass[0] -= rocket->fuel_landing_mass;
    M_Rocket += rocket->fuel_mass[0] + rocket->s_mass[0] + rocket->fuel_mass[1] + rocket->s_mass[1] + rocket->fuel_landing_mass;
    rocket->s_mass[1] += rocket->fuel_landing_mass;
}


void FlightInit::initialize_time_parameters() {
    std::cout << "set start flight parameters\n";

    T_fuel[0] = rocket->fuel_mass[0]/(peng [0]/rocket->exhaust_velocity[0]);
    T_stage [0] = T_fuel [0] + T_sep [0];
    T_fuel[1] = rocket->fuel_mass[1]/(peng [1]/rocket->exhaust_velocity[1]);
    T_stage [1] = T_fuel [1] + T_sep [1];
    // ИД итеративного расчета
    insertion->m_t = M_Rocket;

    insertion->anY = M_PI/2;

    // Итеративный расчет
    count = 0;
    insertion->tY = 0;

    d_O[1] = 0;
    T[0] = T_fuel[0];
    T[1] = T_fuel[0] + T_sep[0];
    T[2] = T_fuel[0] + T_sep[0]+T_fuel[1];
    T[3] = T_fuel[0] + T_sep[0]+T_fuel[1] + T_sep[1];
}

void FlightInit::calculate_area_and_inertia() {
    insertion->S_dry[0] = rocket->s_elements[0].GetSx();
    insertion->S_dry[1] = rocket->s_elements[1].GetSx();


    // Calculate areas for oxygen and carbon
    S_o[0] = rocket->o_elements[0].GetSx();
    S_c[0] = rocket->c_elements[0].GetSx();
    S_o[1] = rocket->o_elements[0].GetSx();
    S_c[1] = rocket->c_elements[0].GetSx();

    insertion->S_reO = rocket->re_o_element[0].GetSx();
    insertion->S_reC = rocket->re_c_element[0].GetSx();



    insertion->Sx = rocket->head_unit[0].GetSx() + insertion->S_dry[0] + insertion->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1]
                    + insertion->S_reO + insertion->S_reC;

    Sx = insertion->Sx;
    calculate_inertia();
    qDebug() << "\n" << "-- INERCIA --" << "\n";
    qDebug() << "Sx: " << Sx;
    qDebug() << "Ix: " << Ix;
    qDebug() << "Iz: " << Iz;
}

void FlightInit::calculate_inertia() {
    insertion->I_dry[0] = rocket->s_elements[0].GetIz();
    insertion->I_dry[1] = rocket->s_elements[1].GetIz();

    I_o[0] = rocket->o_elements[0].GetIz();
    I_c[0] = rocket->c_elements[0].GetIz();
    I_o[1] = rocket->o_elements[1].GetIz();
    I_c[1] = rocket->c_elements[1].GetIz();

    insertion->I_reO = rocket->re_o_element[0].GetIz();
    insertion->I_reC = rocket->re_c_element[0].GetIz();

    insertion->Iyz =  rocket->head_unit[0].GetIz() + insertion->I_dry[0] + insertion->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + insertion->I_reO + insertion->I_reC - M_Rocket * pow(insertion->gl_c, 2);
    Iz = insertion->Iyz;
    Ix = M_Rocket * pow(rocket->maximum_diameter / 2, 2);

    Izmax = Iz;
    Ixmax = Ix;
}

void FlightInit::calculate_landing_values() {
    landing->m_t = insertion->m_t;
    landing->V = insertion->V;
    landing->m_t = insertion->m_t;
    landing->anY = insertion->anY;
    landing->tY = 1;
    landing->S_reO = insertion->S_reO;
    landing->S_reC = insertion->S_reC;
    landing->tX = 0;
    landing->S_dry[0]   = insertion->S_dry[0];
    landing->S_dry[1]   = insertion->S_dry[1];
    landing->I_dry[0] = insertion->I_dry[0];
    landing->I_reO = insertion->I_reO;
    landing->I_reC = insertion->I_reC;
}
