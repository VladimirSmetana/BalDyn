#include "FlightInit.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>

#include "Constants.h"
#include <QDebug>

#include "rockets/RocketConfigurator.h"

namespace {
constexpr auto c_components_ratio = 3.5;
constexpr auto c_first_block_length = 42.9;
constexpr auto c_second_block_length = 10.5;
constexpr auto c_second_stage_length = 21.5;
constexpr auto c_extra_mass = 33200; /*2200*/
constexpr auto c_payload_mass = 15000;
constexpr auto c_first_block_mass = 391000;
constexpr auto c_second_block_mass = 107000;
constexpr auto c_first_exhaust_velocity = 3300;
constexpr auto c_second_exhaust_velocity = 3700;
constexpr auto c_maximum_diameter = 4.1;
constexpr auto c_test_mass = 0;
constexpr auto c_first_structural_value = 7;
constexpr auto c_second_structural_value = 10;
}

FlightInit::FlightInit(double (&kalph_)[3], double (&kpeng_)[2]) {
    std::copy(std::begin(kalph_), std::end(kalph_), std::begin(kalph));
    std::copy(std::begin(kpeng_), std::end(kpeng_), std::begin(kpeng));

    m_calculate_initial_values();
    M.MCI_f(mpn, D, mb[0], mb[1], s[0], s[1], peng[0], peng[1]);
    calculate_length();
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
    Rocket rocket = RocketConfigurator(rocketType);

    mpn    = rocket.payload_mass;
    qDebug() << rocket.payload_mass;
    Ratio  = rocket.components_ratio;
    D      = rocket.maximum_diameter;
    zap    = rocket.fuel_landing_mass;

    for (int i=0; i<rocket.block_number; i++) {
        mb[i]  = rocket.block_mass[i];
        Imp[i] = rocket.exhaust_velocity[i];
        s[i]   = rocket.structural_value[i];
        qDebug() << mb[i];
        qDebug() << Imp[i];
        qDebug() << s[i];
        peng[i] = kpeng[i] * constants::acceleration_of_gravity * rocket.stage_mass[i];
    }

    h      = c_step;

    m_furet = rocket.fuel_landing_mass;
    m_reC = m_furet / (Ratio+1);
    m_reO = m_furet * (Ratio) / (Ratio+1);
    M_Rocket = mpn;
    insertion->m_t = M_Rocket;
    landing->m_t = M_Rocket;
    Smid = M_PI * pow(D, 2) / 4;
    insertion->V = 0;
    landing->V = 0;
    count = 0;
}


void FlightInit::initialize_time_parameters() {
    std::cout << "set start flight parameters\n";

    T_fuel[0] = m_fuel[0]/(peng [0]/Imp[0]);
    T_stage [0] = T_fuel [0] + T_sep [0];
    T_fuel[1] = m_fuel[1]/(peng [1]/Imp[1]);
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

void FlightInit::calculate_length() {
    // Определение габаритов ракеты
    Lmax = M.get_length();
    L1 = c_first_block_length;
    L2 = c_second_block_length;
}

void FlightInit::m_calculate_mass_parameters() {
    for (int i = 0; i <= 1; i++) {
        m_fuel[i] = mb[i] * (s[i] - 1) / s[i];
        m_O[i] = m_fuel[i] * Ratio / (Ratio + 1);
        m_C[i] = m_fuel[i] / (Ratio + 1);
        m_dry[i] = mb[i] - m_fuel[i];
    }
    m_dry[0] -= m_furet;
    M_Rocket += m_fuel[0] + m_dry[0] + m_fuel[1] + m_dry[1] + m_furet;
    m_dry[1] += zap;

    M_stage[0] = M_Rocket;
    M_stage[1] = M_Rocket - mb[0];
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
    insertion->I_dry[0] = M.fun_I(M.K[6], M.K[12], m_dry[0], D);
    insertion->I_dry[1] = M.fun_I(M.K[1], M.K[6], m_dry[1], D);
    landing->I_dry[0] = M.fun_I(M.K[6] - c_second_stage_length, M.K[12] - c_second_stage_length, m_dry[0], D);

    I_o[0] = M.fun_I(M.K[8], M.K[9], m_O[0], D);
    I_c[0] = M.fun_I(M.K[10], M.K[11], m_C[0], D);
    I_o[1] = M.fun_I(M.K[3], M.K[4], m_O[1], D);
    I_c[1] = M.fun_I(M.K[5], M.K[6], m_C[1], D);

    insertion->I_reO = M.fun_I(M.K[9], M.K[10], m_reO, D);
    insertion->I_reC = M.fun_I(M.K[11], M.K[13], m_reC, D);
    landing->I_reO = M.fun_I(M.K[9] - c_second_stage_length, M.K[10] - c_second_stage_length, m_reO, D);
    landing->I_reC = M.fun_I(M.K[11] - c_second_stage_length, M.K[13] - c_second_stage_length, m_reC, D);

    insertion->Isumm = M.get_IGO() + insertion->I_dry[0] + insertion->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + insertion->I_reO + insertion->I_reC - M_Rocket * pow(insertion->gl_c, 2);
    Iz = insertion->Isumm;
    Ix = M_Rocket * pow(D / 2, 2);

    Izmax = Iz;
    Ixmax = Ix;
}

