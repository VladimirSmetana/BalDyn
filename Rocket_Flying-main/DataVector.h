#ifndef DATAVECTOR_H
#define DATAVECTOR_H

#include <QVector>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>

namespace fs = std::filesystem;

struct Dataset {
    QVector<double> time{};
    QVector<double> altitude{};
    QVector<double> x_moment{};
    QVector<double> attack_angle{};
    QVector<double> trajectory_angle{};
    QVector<double> center_of_mass{};
    QVector<double> dynamic_pressure{};
    QVector<double> mass{};
    QVector<double> stability_margin{};
    QVector<double> thrust{};
    QVector<double> longitude{};
    QVector<double> velocity{};
    QVector<double> wind_velocity{};
    QVector<double> g_force{};
    QVector<double> yz_moment{};
    QVector<double> static_moment{};
    QVector<double> engine_angle{};
    QVector<double> pitch_angle{};
    QVector<double> focus{};
    QVector<double> control_thrust{};
    QVector<double> drug_coefficient{};
    QVector<double> rocket_length{};
    QVector<double> lift_force{};

    bool saveToCSV(const fs::path& filename) const;
};

#endif // DATAVECTOR_H
