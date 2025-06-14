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
    M.MCI_f(rocket.payload_mass,
            rocket.maximum_diameter,
            rocket.block_mass[0],
            rocket.block_mass[1],
            rocket.structural_value[0],
            rocket.structural_value[1],
            peng[0],
            peng[1]);
    m_calculate_mass_parameters();
    initialize_time_parameters();
    calculate_area_and_inertia();
}

void FlightInit::m_calculate_initial_values() {
    qDebug() << "\n" << "-- INITIAL DATA --" << "\n";
    qDebug() << "1st attack coefficient:" << kalph[1];
    qDebug() << "2d attack coefficient :"  << kalph[2];
    qDebug() << "1st thrust-to-weight coefficient:" << kpeng[0];
    qDebug() << "2d thrust-to-weight coefficient :"  << kpeng[1];

    RocketType rocketType = RocketType::master;
    rocket = RocketConfigurator(rocketType);

    for (int i=0; i<rocket.block_number; i++) {
        peng[i] = kpeng[i] * constants::acceleration_of_gravity * rocket.stage_mass[i];
    }

    h  = c_step;

    rocket.fuel_landing_mass = rocket.fuel_landing_mass;
    m_reC = rocket.fuel_landing_mass / (rocket.components_ratio+1);
    m_reO = rocket.fuel_landing_mass * (rocket.components_ratio) / (rocket.components_ratio+1);
    M_Rocket = rocket.payload_mass;
    insertion->m_t = M_Rocket;
    landing->m_t = M_Rocket;
    Smid = M_PI * pow(rocket.maximum_diameter, 2) / 4;
    insertion->V = 0;
    landing->V = 0;
    count = 0;
}


void FlightInit::initialize_time_parameters() {
    std::cout << "set start flight parameters\n";

    T_fuel[0] = m_fuel[0]/(peng [0]/rocket.exhaust_velocity[0]);
    T_stage [0] = T_fuel [0] + T_sep [0];
    T_fuel[1] = m_fuel[1]/(peng [1]/rocket.exhaust_velocity[1]);
    T_stage [1] = T_fuel [1] + T_sep [1];
    // ИД итеративного расчета
    insertion->m_t = M_Rocket;
    landing->m_t = M_Rocket;
    insertion->anY = M_PI/2;
    landing->anY = M_PI/2;
    landing->tY = 1;
    // Итеративный расчет
    count = 0;
    insertion->tY = 0;
    landing->tX = 0;
    d_O[1] = 0;
    T[0] = T_fuel[0];
    T[1] = T_fuel[0] + T_sep[0];
    T[2] = T_fuel[0] + T_sep[0]+T_fuel[1];
    T[3] = T_fuel[0] + T_sep[0]+T_fuel[1] + T_sep[1];
}

void FlightInit::m_calculate_mass_parameters() {
    for (int i = 0; i <= 1; i++) {
        m_fuel[i] = rocket.block_mass[i] * (rocket.structural_value[i] - 1) / rocket.structural_value[i];
        m_O[i] = m_fuel[i] * rocket.components_ratio / (rocket.components_ratio + 1);
        m_C[i] = m_fuel[i] / (rocket.components_ratio + 1);
        m_dry[i] = rocket.block_mass[i] - m_fuel[i];
    }
    m_dry[0] -= rocket.fuel_landing_mass;
    M_Rocket += m_fuel[0] + m_dry[0] + m_fuel[1] + m_dry[1] + rocket.fuel_landing_mass;
    m_dry[1] += rocket.fuel_landing_mass;

    M_stage[0] = M_Rocket;
    M_stage[1] = M_Rocket - rocket.block_mass[0];
}

void FlightInit::calculate_area_and_inertia() {
    insertion->S_dry[0] = M.fun_S(M.K[6], M.K[12], m_dry[0]);
    insertion->S_dry[1] = M.fun_S(M.K[1], M.K[6], m_dry[1]);
    landing->S_dry[0] = M.fun_S(M.K[6] - c_second_stage_length, M.K[12] - c_second_stage_length, m_dry[0]);
    landing->S_dry[1] = M.fun_S(M.K[1] - c_second_stage_length, M.K[6] - c_second_stage_length, m_dry[1]);

    // Calculate areas for oxygen and carbon
    S_o[0] = M.fun_S(M.K[8], M.K[9], m_O[0]);
    S_c[0] = M.fun_S(M.K[10], M.K[11], m_C[0]);
    S_o[1] = M.fun_S(M.K[3], M.K[4], m_O[1]);
    S_c[1] = M.fun_S(M.K[5], M.K[6], m_C[1]);

    insertion->S_reO = M.fun_S(M.K[9], M.K[10], m_reO);
    insertion->S_reC = M.fun_S(M.K[11], M.K[13], m_reC);
    landing->S_reO = M.fun_S(M.K[9] - c_second_stage_length, M.K[10] - c_second_stage_length, m_reO);
    landing->S_reC = M.fun_S(M.K[11] - c_second_stage_length, M.K[13] - c_second_stage_length, m_reC);

    insertion->Ssumm = M.get_SGO() + insertion->S_dry[0] + insertion->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + insertion->S_reO + insertion->S_reC;


    Sx = insertion->Ssumm;
    calculate_inertia();
    qDebug() << "\n" << "-- INERCIA --" << "\n";
    qDebug() << "Sx: " << Sx;
    qDebug() << "Ix: " << Ix;
    qDebug() << "Iz: " << Iz;
}

void FlightInit::calculate_inertia() {
    insertion->I_dry[0] = M.fun_I(M.K[6], M.K[12], m_dry[0], rocket.maximum_diameter);
    insertion->I_dry[1] = M.fun_I(M.K[1], M.K[6], m_dry[1], rocket.maximum_diameter);
    landing->I_dry[0] = M.fun_I(M.K[6] - c_second_stage_length, M.K[12] - c_second_stage_length, m_dry[0], rocket.maximum_diameter);

    I_o[0] = M.fun_I(M.K[8], M.K[9], m_O[0], rocket.maximum_diameter);
    I_c[0] = M.fun_I(M.K[10], M.K[11], m_C[0], rocket.maximum_diameter);
    I_o[1] = M.fun_I(M.K[3], M.K[4], m_O[1], rocket.maximum_diameter);
    I_c[1] = M.fun_I(M.K[5], M.K[6], m_C[1], rocket.maximum_diameter);

    insertion->I_reO = M.fun_I(M.K[9], M.K[10], m_reO, rocket.maximum_diameter);
    insertion->I_reC = M.fun_I(M.K[11], M.K[13], m_reC, rocket.maximum_diameter);
    landing->I_reO = M.fun_I(M.K[9] - c_second_stage_length, M.K[10] - c_second_stage_length, m_reO, rocket.maximum_diameter);
    landing->I_reC = M.fun_I(M.K[11] - c_second_stage_length, M.K[13] - c_second_stage_length, m_reC, rocket.maximum_diameter);

    insertion->Isumm = M.get_IGO() + insertion->I_dry[0] + insertion->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + insertion->I_reO + insertion->I_reC - M_Rocket * pow(insertion->gl_c, 2);
    Iz = insertion->Isumm;
    Ix = M_Rocket * pow(rocket.maximum_diameter / 2, 2);

    Izmax = Iz;
    Ixmax = Ix;
}

