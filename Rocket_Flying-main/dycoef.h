#ifndef DYCOEF_H
#define DYCOEF_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <cmath>
#include <QtSql>
#include "iostream"
#include <QFile>


class DC
{

private:
    double len;
public:
    DC();
    ~DC();
    double PI();
    double const lamb [5] {4.73, 7.853, 10.996, 14.137, 17.279};
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

    QVector<double> ms_vec[5];

    QVector<double> form[5];
    QVector<double> dform[5];
    QVector<double> lenght;

    double Ms[5];

    void print(double ct, double t);
    void data_writing(QVector<double> xn, QVector<double> v_2, QVector<double> H2,
                      QVector<double> w, QVector<double> mass_2, QVector<double> P2,
                      QVector<double> pc2, QVector<double> yu_2, QVector<double> ALI_2,
                      QVector<double> cy2, QVector<double> dyn1, QVector<double> dyn2,
                      QVector<double> jinn2);

    void data_calculating(double P, double I, double D);
    void const_par(double len);
    void ver_par(double time, double mass, double p, double p_con,
                        double q, double cy, double x1, double x2, double vel, double iner, double len, double wind, double center, double focus);
        QFile file1;
        QFile file2;
        QFile file3;
};



#endif // DYCOEF_H
