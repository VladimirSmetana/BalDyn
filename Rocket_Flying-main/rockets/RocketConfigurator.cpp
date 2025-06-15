#include "RocketConfigurator.h"

Rocket RocketConfigurator(RocketType type) {

    Rocket rocket;

    double L_headunit;
    double L_instrument;
    double extra_payload;
    QVector<double> L_spO;
    QVector<double> L_spC;
    QVector<double> L_O;
    QVector<double> L_C;
    QVector<double> L_engine;
    QVector<double> K;

    switch (type) {
    case RocketType::master:
        rocket.block_number       = 2;
        rocket.payload_mass       = 15000;
        rocket.block_mass         = {391000, 107000};
        rocket.components_ratio   = 3.5;
        rocket.maximum_diameter   = 4.1;
        rocket.head_length        = 11;
        rocket.block_length       = {42.0, 10.5};
        rocket.exhaust_velocity   = {3300, 3700};
        rocket.structural_value   = {7, 10};

        L_spO   .assign(rocket.block_number, 0);
        L_spC   .assign(rocket.block_number, 0);
        L_O     .assign(rocket.block_number, 0);
        L_C     .assign(rocket.block_number, 0);
        L_engine.assign(rocket.block_number, 0);
        K       .assign(12, 0);

        L_headunit = 11;
        L_instrument = 0.1;
        L_spO[1] = 0.6;
        L_O[1] = 4.8;
        L_spC[1] = 0.6;
        L_C[1] = 4.1+0.6;
        L_engine[1] =3.2-0.6;
        L_spO[0] = 1;
        L_O[0] = 17.3;
        L_spC[0] = 2.7;
        L_C[0] = 13.2;
        L_engine[0] = 4.9;

        K[0] = 0;
        K[1] = K[0] + L_headunit;
        K[2] = K[1] + L_instrument;
        K[3] = K[2] + L_spO[1];
        K[4] = K[3] + L_O[1];
        K[5] = K[4] + L_spC[1];
        K[6] = K[5] + L_C[1];
        K[7] = K[6] + L_engine[1];
        K[8] = K[7] + L_spO[0];
        K[9] = K[8] + L_O[0];
        K[10]= K[9] + L_spC[0];
        K[11]= K[10]+ L_C[0];
        K[13]= K[11]+ 1.3;
        K[12]= K[11]+ L_engine[0];

        rocket.full_length = rocket.head_length;
        if (rocket.block_number!=0) {
            for (int i = 0; i<rocket.block_number; i++) {
                double stage_mass = rocket.payload_mass;
                for (int j = i; j<rocket.block_number; j++) {
                    stage_mass+=rocket.block_mass[j];
                }
                rocket.full_length += rocket.block_length[i];
                rocket.stage_mass.push_back(stage_mass);
                rocket.fuel_mass.push_back(rocket.block_mass[i] * (rocket.structural_value[i] - 1) / rocket.structural_value[i]);
                rocket.o_mass.push_back(rocket.fuel_mass[i] * rocket.components_ratio / (rocket.components_ratio + 1));
                rocket.c_mass.push_back(rocket.fuel_mass[i] / (rocket.components_ratio + 1));
                rocket.s_mass.push_back(rocket.block_mass[i] - rocket.fuel_mass[i]);

            }
        }

        rocket.re_c_mass.push_back(rocket.fuel_landing_mass / (rocket.components_ratio+1));
        rocket.re_o_mass.push_back(rocket.fuel_landing_mass * (rocket.components_ratio) / (rocket.components_ratio+1));

        extra_payload = 1.1*rocket.payload_mass;
        rocket.head_unit.emplace_back(K[0], K[1],  extra_payload, rocket.maximum_diameter);

        rocket.re_o_element.emplace_back(K[9], K[10],  rocket.re_o_mass[0], rocket.maximum_diameter);
        rocket.re_c_element.emplace_back(K[11],K[13],  rocket.re_c_mass[0], rocket.maximum_diameter);

        rocket.o_elements.emplace_back(K[8], K[9],  rocket.o_mass[0], rocket.maximum_diameter);
        rocket.o_elements.emplace_back(K[3], K[4],  rocket.o_mass[1], rocket.maximum_diameter);
        rocket.c_elements.emplace_back(K[10],K[11], rocket.c_mass[0], rocket.maximum_diameter);
        rocket.c_elements.emplace_back(K[5], K[6],  rocket.c_mass[1], rocket.maximum_diameter);
        rocket.s_elements.emplace_back(K[6], K[12], rocket.s_mass[0], rocket.maximum_diameter);
        rocket.s_elements.emplace_back(K[1], K[6],  rocket.s_mass[1], rocket.maximum_diameter);


        break;

    case RocketType::cz_2c:
        rocket.block_number       = 2;
        rocket.payload_mass       = 3850;
        rocket.block_mass         = {171300, 58000};
        rocket.components_ratio   = 3.0;
        rocket.maximum_diameter   = 3.35;
        rocket.head_length        = 10.243;
        rocket.block_length       = {25.72, 7.757};
        rocket.exhaust_velocity   = {2556.5, 2922.37};
        rocket.structural_value   = {20, 25};

        if (rocket.block_number!=0) {
            for (int i = 0; i<rocket.block_number; i++) {
                double stage_mass = rocket.payload_mass;
                for (int j = i; j<rocket.block_number; j++) {
                    stage_mass+=rocket.block_mass[j];
                }
                rocket.stage_mass.push_back(stage_mass);
            }
        }
        break;

    default:
        rocket.block_number       = 0;
    }

    return rocket;
}
