#ifndef DATAVECTOR_H
#define DATAVECTOR_H

#include <QVector>

struct Dataset {
    QVector<double> altitude_1{};
    QVector<double> jinn{};
    QVector<double>ALI_1{};
    QVector<double>TET_1{};
    QVector<double>center_1{};
    QVector<double>yu_1{};
    QVector<double>mass_1{};
    QVector<double> dyn1{};
    QVector<double> P1{};
    QVector<double> b1{};
    QVector<double> Long_1{};
    QVector<double> v_1{};
    QVector<double> vec_wind1{};

    QVector<double> altitude_2{};
    QVector<double> jinn2{};
    QVector<double>ALI_2{};
    QVector<double>TET_2{};
    QVector<double>center_2{};
    QVector<double>yu_2{};
    QVector<double>mass_2{};
    QVector<double>dyn2{};
    QVector<double> P2{};
    QVector<double> b2{};
    QVector<double> Long_2{};
    QVector<double> v_2{};
    QVector<double> vec_wind2{};

    QVector<double> xn{};

    QVector<double>lin{};
    QVector<double>sinn{};
    QVector<double>CM{};
    QVector<double>be{};
    QVector<double>pi{};
    QVector<double> v_3{};
    QVector<double> angle{};
    QVector<double> f1{};
    QVector<double> Lon{}, Lonre{};
    QVector<double> pc2{};
    QVector<double> cy2{};
    QVector<double> lenght_R{};

};

#endif // DATAVECTOR_H
