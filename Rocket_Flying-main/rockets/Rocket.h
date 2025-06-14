#ifndef ROCKET_H
#define ROCKET_H

#include <QVector>

#include "element.h"

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
    double full_length;
    double full_mass;
    QVector<double> block_length;
    QVector<double> exhaust_velocity;
    QVector<double> block_mass;
    QVector<double> o_mass;
    QVector<double> c_mass;
    QVector<double> s_mass;
    QVector<double> fuel_mass;
    QVector<double> stage_mass;
    QVector<double> structural_value;
    QVector<Element> s_elements;
    QVector<Element> o_elements;
    QVector<Element> c_elements;
};

#endif // ROCKET_H
