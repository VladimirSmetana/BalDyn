#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <qcustomplot.h>
//#include "equations.h"
//#include "atmosphere.h"
//#include "eastwind.h"
//#include "mass.h"

#include "block.h"
#include "alpha.h"
#include "focus.h"
#include "dycoef.h"
#include "pitch.h"
#include <thread>
#include <QtSql>
#include <QDebug>
#include <cmath>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    // Создание объектов
//    std::unique_ptr<block> first = std::make_unique<block>();
//    std::unique_ptr<block> second = std::make_unique<block>();
    std::unique_ptr<pitch> P = std::make_unique<pitch>();
    //block first;
//    block second;
    // Исходные данные РН







    void drawing(QVector<double> Y1,
                 QVector<double> Y2, double y0,  double yk,
                 QVector<double> X1,
                 QVector<double> X2, double x0 , double xk);

    void drawing(QVector<double> Y1, double y0,  double yk,
                 QVector<double> X1, double x0 , double xk);



    double Runge_Kutt(double func(double, double),
                    double XX, double YY,
                    double h);

private slots:


    void on_action_triggered();

    void on_action_5_triggered();

    void on_NX_Button_clicked();

    void on_height_Button_clicked();

    void on_trj_Button_clicked();

    void on_distance_Button_clicked();

    void on_velocity_Button_clicked();

    void on_alpha_Button_clicked();

    void on_T_angle_Button_clicked();

    void on_Q_Button_clicked();

    void on_center_Button_clicked();



    void on_thrust_Button_clicked();

    void on_mass_Button_clicked();

    void on_action_exit_triggered();

    void on_fokus_Button_clicked();

    void on_static_Button_clicked();

    void on_YZmoment_Button_clicked();

    void on_Xmoment_Button_clicked();

private:
    Ui::MainWindow *ui;
    QCustomPlot *wGraphic;
    QCPCurve *verticalLine;
    QCPItemTracer *tracer;

};
#endif // MAINWINDOW_H
