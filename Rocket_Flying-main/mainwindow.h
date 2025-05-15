#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <qcustomplot.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>


#include "FlightType.h"
#include "alpha.h"
#include "focus.h"
#include "dycoef.h"
#include "FlightSolver.h"
#include <thread>
#include <QtSql>
#include <QDebug>
#include <cmath>
#include <iostream>
#include "DataVector.h"

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
    std::unique_ptr<FlightSolver> P;
    std::unique_ptr<DC> d = std::make_unique<DC>();

    void drawing(QVector<double>& Y1,
                 QVector<double>& Y2,
                 const double& y0,
                 const double& yk,
                 QVector<double>& X1,
                 QVector<double>& X2,
                 const double& x0 ,
                 const double& xk);

    void drawing(QVector<double>& Y1,
                 const double& y0,
                 const double& yk,
                 QVector<double>& X1,
                 const double& x0 ,
                 const double& xk);

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

    void on_height_Button_2_clicked();

    void on_height_Button_3_clicked();

    void on_height_Button_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QCustomPlot *wGraphic;
    QCPCurve *verticalLine;
    QCPItemTracer *tracer;
    std::shared_ptr<Dataset> m_insertion_data;
    std::shared_ptr<Dataset> m_recovery_data;
};
#endif // MAINWINDOW_H
