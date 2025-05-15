#include "RocketConfigurator.h"

Rocket RocketConfigurator(RocketType type) {
    Rocket rocket;

    switch (type) {
    case RocketType::master:
        rocket.block_number       = 2;
        rocket.payload_mass       = 15000;
        rocket.block_mass         = {391000, 107000};
        rocket.components_ratio   = 3.5;
        rocket.maximum_diameter   = 4.1;
        rocket.head_length        = 11;
        rocket.block_length       = {10.5, 21.5};
        rocket.exhaust_velocity   = {3300, 3700};
        rocket.structural_value   = {7, 10};


        break;

    case RocketType::cz_2c:
        rocket.block_number       = 2;
        rocket.payload_mass       = 3850;
        rocket.block_mass         = {171300, 58000};
        rocket.components_ratio   = 4.0;
        rocket.maximum_diameter   = 4.5;
        rocket.head_length        = 12;
        rocket.block_length       = {11.5, 22.5};
        rocket.exhaust_velocity   = {2556.5, 2922.37};
        rocket.structural_value   = {20, 25};
        break;

    default:
        rocket.block_number       = 0;
    }


    if (rocket.block_number!=0) {
        for (int i = 0; i<rocket.block_number; i++) {
            double stage_mass = rocket.payload_mass;
            for (int j = i; j<rocket.block_number; j++) {
                stage_mass+=rocket.block_mass[j];
            }
            rocket.stage_mass.push_back(stage_mass);
        }
    }

    return rocket;
}
