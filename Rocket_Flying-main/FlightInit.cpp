#include "FlightInit.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>

#include "Constants.h"

namespace {
constexpr auto components_ratio = 4.5;
constexpr auto first_block_length = 42.9;
constexpr auto second_block_length = 10.5;
constexpr auto second_stage_length = 21.5;
constexpr auto extra_mass = 33200; /*2200*/
}

FlightInit::FlightInit(double (&kalph_)[3], double (&kpeng_)[2]) {
    std::copy(std::begin(kalph_), std::end(kalph_), std::begin(kalph));
    std::copy(std::begin(kpeng_), std::end(kpeng_), std::begin(kpeng));

    m_calculate_initial_values();
    //calculate_length();
}

void FlightInit::m_calculate_initial_values() {
    std::cout << "" << kalph[0] << "\n";
    std::cout << "" << kalph[1] << "\n";
    std::cout << "" << kalph[2] << "\n";
    std::cout << "" << kpeng[0] << "\n";
    std::cout << "" << kpeng[1] << "\n";
    peng[0] = kpeng[0] * constants::acceleration_of_gravity * (mpn + mb[0] + mb[1]);
    peng[1] = kpeng[1] * constants::acceleration_of_gravity * (mpn + mb[1]);
    m_furet = extra_mass;
    m_reC = m_furet / components_ratio;
    m_reO = m_furet * (components_ratio - 1) / components_ratio;
    M_Rocket = mpn;
    fir->m_t = M_Rocket;
    sec->m_t = M_Rocket;
    Smid = M_PI * pow(D, 2) / 4;
    fir->V = 0;
    sec->V = 0;
    count = 0;
}


