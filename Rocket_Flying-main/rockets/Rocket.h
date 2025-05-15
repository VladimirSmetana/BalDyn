#ifndef ROCKET_H
#define ROCKET_H

#include <QVector>

namespace {
constexpr auto c_step = 0.1;
}

struct Rocket {
    int    block_number;
    double payload_mass;
    double components_ratio;
    double maximum_diameter;
    double fuel_landing_mass;
    double head_length;
    QVector<double> block_length;
    QVector<double> exhaust_velocity;
    QVector<double> block_mass;
    QVector<double> stage_mass;
    QVector<double> structural_value;
};

#endif // ROCKET_H
