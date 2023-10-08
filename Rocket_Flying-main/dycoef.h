#ifndef DYCOEF_H
#define DYCOEF_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <cmath>
#include <QtSql>
#include "pid_file.h"
#include "iostream"

class DC
{
public:

    double PI();
    QVector<double> times;
    QVector<double> Cbs;
    QVector<double> Cyws;
    QVector<double> Cwws;
    QVector<double> Cyys;
    QVector<double> Cwys;
    QVector<double> Cwbs;
    QVector<double> Csbs;
    QVector<double> masss;
    QVector<double> W[5];
    QVector<double> CW[5];
    QVector<double> CY[5];
    QVector<double> Wind;
    QVector<double> vels;
    QVector<double> dypresss;
    QVector<double> get_t; QVector<double> get_T();
    QVector<double> get_v; QVector<double> get_V();
    QVector<double> get_w; QVector<double> get_W();
    QVector<double> get_s; QVector<double> get_S();

    void print(double ct, double t);
    void data_writing(QVector<double> xn, QVector<double> v_2, QVector<double> H2,
                      QVector<double> w, QVector<double> mass_2, QVector<double> P2,
                      QVector<double> pc2, QVector<double> yu_2, QVector<double> ALI_2,
                      QVector<double> cy2, QVector<double> dyn1, QVector<double> dyn2,
                      QVector<double> jinn2);

    void data_calculating(double P, double I, double D);
};



#endif // DYCOEF_H
