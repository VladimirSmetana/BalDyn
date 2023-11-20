#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <qcustomplot.h>
#include "equations.h"
#include "atmosphere.h"
#include "airforce.h"
#include "mass.h"
#include "eastwind.h"
#include "block.h"
#include "alpha.h"
#include "focus.h"
#include "dycoef.h"
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
    std::unique_ptr<block> first = std::make_unique<block>();
    std::unique_ptr<block> second = std::make_unique<block>();
    //block first;
//    block second;
    // Исходные данные РН
    double mpn=15000;
    double mb[2] {391000, 107000};
    double s[2] {7, 10};
    double D = 4.1;
    double Imp[2] {3300, 3700};
    double T_sep[2] {3, 3};
    double Ratio = 3.5;
    double h = 0.1;

    double M_Rocket;
    double Peng [2];
    int count;
    double Lmax;
    double Iz, Izmax, Sx, Ix, Ixmax;
    //double gl_c;
    double gl_cmax;
    double Wind1;
    double Wind2;
    double CILCON;

    double k1 = 360;
    double k2 = 383;
    double k3 = 405;
    double k4 = 440;
    double kk1 = 0.2;
    double kk2 = 0.22;

    double Smid;
    double M_stage[2];
    double T_stage [2];
    double Ott;
    double CX_1, CY_1;
    double CX_2, CY_2;
    double dN;
    double m_O[2], m_C[2];
    double d_O[2], d_C[2];
    double S_o[2], S_c[2];
    double I_o[2], I_c[2];
    double Imp_t, CF;
    double pitch;
    double bpr;
    double HSP_1, HSP_p_1, VHSP_1;
    double HSP_2, HSP_p_2;
    double MHSP_1;
    double MHSP_2, VHSP_2;
    double Ott_1, Ott_2 ;
    double H_1;
    double dep;
    double deo, dec;
    double amax;
    double X_oneC;
    double X_twoC;


    double Na=0.1, Mah_1, Mah_2,  time = 0;
    int e=0;
    int uj=0;
    int ten=0;
    double V1=0, Y1=0, H11=0, X1=0;
    double V2=0, Y2=0, H22=0, X2=0;
    double xXY = 0, yXY = 0,  VX = 0.3, VY = 0.3, velXY = 0.3, trjXY = M_PI/2, norXY = 0;
    double zXY = 0, VZ  = 0.3;

private slots:


    void on_action_triggered();

    void on_action_4_triggered();

    void on_action_6_triggered();

    void on_heightButton_clicked();

    void on_distanceButton_clicked();

    void on_trjButton_clicked();

    void on_velButton_clicked();

    void on_alphaButton_clicked();

    void on_angleButton_clicked();

    void on_vhButton_clicked();

    void on_centerButton_clicked();

    void on_staticButton_clicked();

    void on_YZmomentButton_clicked();

    void on_XmomentButton_clicked();

    void on_massButton_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_14_clicked();

    void on_fokusButton_clicked();

    void on_action_5_triggered();

    void on_action_7_triggered();

private:
    Ui::MainWindow *ui;
    QCustomPlot *wGraphic;
    QCPCurve *verticalLine;
    QCPItemTracer *tracer;
};
#endif // MAINWINDOW_H
