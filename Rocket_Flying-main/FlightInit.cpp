#include "FlightInit.h"

#include <algorithm>
#include <iostream>
#include <iterator>

#include "Constants.h"

namespace {
constexpr auto c_components_ratio = 3.5;

constexpr auto c_first_block_length  = 42.9;
constexpr auto c_second_block_length = 10.5;
constexpr auto c_second_stage_length = 21.5;

constexpr auto c_extra_mass = 33200;

constexpr auto c_first_block_mass  = 391000;
constexpr auto c_second_block_mass = 107000;
constexpr auto c_payload_mass      = 15000;

constexpr auto c_maximum_diameter = 4.1;

constexpr auto c_step = 0.1;

constexpr auto c_first_block_mass_ratio  = 7;
constexpr auto c_second_block_mass_ratio = 10;
}

FlightInit::FlightInit(double (&thrustToWeght)[2]) {
    std::copy(std::begin(thrustToWeght), std::end(thrustToWeght), std::begin(m_thrust_to_weight));



    calculate_initial_values();
    M.MCI_f(0, h, mpn, D, mb[0], mb[1], s[0], s[1], peng[0], peng[1]);
    calculate_length();
    calculate_mass_parameters();
    calculate_area_and_inertia();
    initialize_time_parameters();
}

void FlightInit::calculate_initial_values() {

    mb[0] = c_first_block_mass;
    mb[1] = c_second_block_mass;
    mpn   = c_payload_mass;
    D = c_maximum_diameter;
    h = c_step;
    s[0] = c_first_block_mass_ratio;
    s[1] = c_second_block_mass_ratio;
    Ratio = c_components_ratio;

    peng[0] = m_thrust_to_weight[0] * constants::acceleration_of_gravity * (mpn + mb[0] + mb[1]);
    peng[1] = m_thrust_to_weight[1] * constants::acceleration_of_gravity * (mpn + mb[1]);

    m_furet = c_extra_mass;
    m_reC = m_furet / (Ratio + 1);
    m_reO = m_furet * Ratio / (Ratio + 1);
    M_Rocket = mpn;
    fir->m_t = M_Rocket;
    sec->m_t = M_Rocket;
    Smid = M_PI * pow(D, 2) / 4;
    fir->V = 0;
    sec->V = 0;
    count = 0;
}

void FlightInit::calculate_length() {
    // Определение габаритов ракеты
    Lmax = M.get_length();
    L1 = c_first_block_length;
    L2 = c_second_block_length;

    std::cout << "Rocket length: " << Lmax << "\n";
}

void FlightInit::calculate_mass_parameters() {
    for (int i = 0; i <= 1; i++) {
        m_fuel[i] = mb[i] * (s[i] - 1) / s[i];
        m_C[i] = m_fuel[i] / (Ratio + 1);
        m_O[i] = m_fuel[i] * Ratio / (Ratio + 1);
        m_dry[i] = mb[i] - m_fuel[i];
    }

    m_dry[0] -= m_furet;
    M_Rocket += m_fuel[0] + m_dry[0] + m_fuel[1] + m_dry[1] + m_furet;

    m_dry[1] += zap;

    M_stage[0] = M_Rocket;
    M_stage[1] = M_Rocket - mb[0];


}

void FlightInit::calculate_area_and_inertia() {
    fir->S_dry[0] = M.fun_S(M.K[6], M.K[12], m_dry[0]);
    fir->S_dry[1] = M.fun_S(M.K[1], M.K[6], m_dry[1]);
    sec->S_dry[0] = M.fun_S(M.K[6] - c_second_stage_length, M.K[12] - c_second_stage_length, m_dry[0]);
    sec->S_dry[1] = M.fun_S(M.K[1] - c_second_stage_length, M.K[6] - c_second_stage_length, m_dry[1]);

    // Calculate areas for oxygen and carbon
    S_o[0] = M.fun_S(M.K[8], M.K[9], m_O[0]);
    S_c[0] = M.fun_S(M.K[10], M.K[11], m_C[0]);
    S_o[1] = M.fun_S(M.K[3], M.K[4], m_O[1]);
    S_c[1] = M.fun_S(M.K[5], M.K[6], m_C[1]);

    fir->S_reO = M.fun_S(M.K[9], M.K[10], m_reO);
    fir->S_reC = M.fun_S(M.K[11], M.K[13], m_reC);
    sec->S_reO = M.fun_S(M.K[9] - c_second_stage_length, M.K[10] - c_second_stage_length, m_reO);
    sec->S_reC = M.fun_S(M.K[11] - c_second_stage_length, M.K[13] - c_second_stage_length, m_reC);

    fir->Ssumm = M.get_SGO() + fir->S_dry[0] + fir->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + fir->S_reO + fir->S_reC;

    calculate_inertia();
}

void FlightInit::calculate_inertia() {
    fir->I_dry[0] = M.fun_I(M.K[6], M.K[12], m_dry[0], D);
    fir->I_dry[1] = M.fun_I(M.K[1], M.K[6], m_dry[1], D);
    sec->I_dry[0] = M.fun_I(M.K[6] - c_second_stage_length, M.K[12] - c_second_stage_length, m_dry[0], D);

    I_o[0] = M.fun_I(M.K[8], M.K[9], m_O[0], D);
    I_c[0] = M.fun_I(M.K[10], M.K[11], m_C[0], D);
    I_o[1] = M.fun_I(M.K[3], M.K[4], m_O[1], D);
    I_c[1] = M.fun_I(M.K[5], M.K[6], m_C[1], D);

    fir->I_reO = M.fun_I(M.K[9], M.K[10], m_reO, D);
    fir->I_reC = M.fun_I(M.K[11], M.K[13], m_reC, D);
    sec->I_reO = M.fun_I(M.K[9] - c_second_stage_length, M.K[10] - c_second_stage_length, m_reO, D);
    sec->I_reC = M.fun_I(M.K[11] - c_second_stage_length, M.K[13] - c_second_stage_length, m_reC, D);

    fir->Isumm = M.get_IGO() + fir->I_dry[0] + fir->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + fir->I_reO + fir->I_reC - M_Rocket * pow(fir->gl_c, 2);
    Iz = fir->Isumm;
    Ix = M_Rocket * pow(D / 2, 2);
    Izmax = Iz;
    Ixmax = Ix;
}

void FlightInit::initialize_time_parameters() {
    std::cout << "set start flight parameters\n";

    T_fuel[0] = m_fuel[0]/(peng [0]/Imp[0]);
    T_stage [0] = T_fuel [0] + T_sep [0];
    T_fuel[1] = m_fuel[1]/(peng [1]/Imp[1]);
    T_stage [1] = T_fuel [1] + T_sep [1];
    // ИД итеративного расчета
    fir->m_t = M_Rocket;
    sec->m_t = M_Rocket;
    fir->anY = M_PI/2;
    sec->anY = M_PI/2;
    //double p_ground = 101325;
    sec->tY = 1;
    //
    // Итеративный расчет
    H1.clear();
    H2.clear();
    xn.clear();
    count = 0;
    fir->tY = 0;
    sec->tX = 0;
    d_O[1] = 0;
    T[0] = T_fuel[0];
    T[1] = T_fuel[0] + T_sep[0];
    T[2] = T_fuel[0] + T_sep[0]+T_fuel[1];
    T[3] = T_fuel[0] + T_sep[0]+T_fuel[1] + T_sep[1];
}
