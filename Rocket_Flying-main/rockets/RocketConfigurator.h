#ifndef ROCKETS_H
#define ROCKETS_H

#include "Rocket.h"

enum class RocketType {
    master,
    cz_2c
};

namespace {
    static Rocket RocketConfigurator(RocketType type) {
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
            rocket.block_number       = 3;
            rocket.payload_mass       = 18000;
            rocket.block_mass         = {391000, 107000};
            rocket.components_ratio   = 4.0;
            rocket.maximum_diameter   = 4.5;
            rocket.head_length        = 12;
            rocket.block_length       = {11.5, 22.5};
            rocket.exhaust_velocity   = {3400, 3750};
            rocket.structural_value   = {8, 12};
            break;
       }

        return rocket;
    }
};

#endif // ROCKETS_H
