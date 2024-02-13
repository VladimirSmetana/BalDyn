#ifndef PITCH_H
#define PITCH_H

#include "block.h"
#include <cmath>
#include <iostream>
#include <QVector>
#include "mass.h"


class pitch
{
public:
    pitch();

    // Глобальные векторы
    QVector<double>lin;
    QVector<double>sinn;
    QVector<double> jinn, jinn2;
    QVector<double>CM;
    QVector<double>ALI_1;
    QVector<double>ALI_2;
    QVector<double>res;
    QVector<double>TET_1;
    QVector<double>TET_2;
    QVector<double>center_1;
    QVector<double>center_2;
    QVector<double>be;
    QVector<double>pi;
    QVector<double>yu_1;
    QVector<double>yu_2;
    QVector<double>mass_1;
    QVector<double>mass_2;
    QVector<double> xn;
    QVector<double> v_1, v_2, v_3;
    QVector<double> Long_1, Long_2, H1, H2, H3;
    QVector<double> angle, b1, b2;
    QVector<double> P1, P2;
    QVector<double> f1;
    QVector<double> Lon, Lonre;
    QVector<double> w, pc2;
    QVector<double> cy2;
    QVector<double> dyn1, dyn2;

    std::unique_ptr<block> fir = std::make_unique<block>();
    std::unique_ptr<block> sec = std::make_unique<block>();

    void pitch_calculations();

};

#endif // PITCH_H
