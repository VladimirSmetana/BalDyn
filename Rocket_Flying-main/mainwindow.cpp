#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FlightSolver.h"
#include <QDebug>
#include <filesystem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Перегруженная функция отрисовки

void MainWindow::drawing(QVector<double>& Y1,
                         const double& y0,
                         const double& yk,
                         QVector<double>& X1,
                         const double& x0 ,
                         const double& xk)
{
    ui->widget->legend->setVisible(true);
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(X1, Y1);
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->xAxis->setRange(x0, xk);
    ui->widget->yAxis->setRange(y0, yk);
    ui->widget->replot();
}

// -
void MainWindow::drawing(QVector<double>& Y1,
                         QVector<double>& Y2,
                         const double& y0,
                         const double& yk,
                         QVector<double>& X1,
                         QVector<double>& X2,
                         const double& x0 ,
                         const double& xk)
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(X1, Y1);
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->xAxis->setRange(x0, xk);
    ui->widget->yAxis->setRange(y0, yk);
    ui->widget->replot();

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(X2, Y2);
    ui->widget->graph(1)->setPen(QPen(Qt::PenStyle::DashLine));
    ui->widget->replot();
}

double  Runge_Kutt(double func(double, double),
                  double XX, double YY,
                  double h)
{
    double K1 = func(XX, YY);
    double K2 = func(XX+h/2*K1, YY+h/2);
    double K3 = func(XX+h/2*K2, YY+h/2);
    double K4 = func(XX+h*K3, YY+h);

    return (K1 + K2*2 + K3*2 + K4)/6*h;
}

// Кнопка "Баллистика"
void MainWindow::on_action_triggered()
{
    // Параметры тяги и угла атаки
    QString p1=ui->lineEdit_10->text();
    QString p2=ui->lineEdit_11->text();
    QString al1=ui->lineEdit_5->text();
    QString al2=ui->lineEdit_4->text();

    double kpeng [2] {p1.toDouble(), p2.toDouble()};
    double coef_alpha [3] {0, al1.toDouble(), al2.toDouble()};
    P = std::make_unique<FlightSolver>(coef_alpha, kpeng);
    P->pitch_calculations();
    m_insertion_data = P->GetInsertionData();
    m_recovery_data  = P->GetRecoveryData();

    std::filesystem::path baldyn = std::filesystem::current_path().parent_path().parent_path().parent_path();
    std::filesystem::path to_insertion_csv = "output/insertion_dataset.csv";
    std::filesystem::path to_recovery_csv  = "output/recovery_dataset.csv";

    m_insertion_data->saveToCSV(baldyn/to_insertion_csv);
    m_recovery_data ->saveToCSV(baldyn/to_recovery_csv);

    QString mk2s = QString::number(P->fir->V);        ui->lineEdit  ->setText(mk2s);
    QString mk1s = QString::number(P->fir->tY/1000);        ui->lineEdit_2->setText(mk1s);
    QString mk3s = QString::number(P->dep);      ui->lineEdit_3->setText(mk3s);
    QString mk5s = QString::number(P->sec->tX/1000); ui->lineEdit_7->setText(mk5s);
    QString mk6s = QString::number(P->MHSP_1);    ui->lineEdit_6->setText(mk6s);
    QString mk8s = QString::number(57.3*P->Ott_1);       ui->lineEdit_8->setText(mk8s);
    QString mk9s = QString::number(57.3*P->Ott_2);       ui->lineEdit_9->setText(mk9s);
    QString mk12s = QString::number(P->amax);       ui->lineEdit_12->setText(mk12s);
    QString mk13s = QString::number(57.3*P->sec->anY);       ui->lineEdit_13->setText(mk13s);

    ui->lineEdit_4->show();
    ui->lineEdit_5->show();
    ui->label_4->show();
    ui->label_5->show();
    ui->action_2->setEnabled(true);
}

// График перегрузки
void MainWindow::on_NX_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Продольная перегрузка");
    drawing(m_insertion_data->g_force,
            m_recovery_data->g_force,
            0,
            10,
            m_insertion_data->time,
            m_recovery_data->time,
            0,
            P->MaxTime);
}

// График траектории
void MainWindow::on_height_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Высота, км");
    drawing(m_insertion_data->altitude,
            m_recovery_data->altitude,
            0,
            230,
            m_insertion_data->time,
            m_recovery_data->time,
            0,
            P->MaxTime+50);
}

// График высоты
void MainWindow::on_trj_Button_clicked()
{
    ui->widget->xAxis->setLabel("Дальность, км");
    ui->widget->yAxis->setLabel("Высота, км");
    drawing(m_insertion_data->altitude,
            m_recovery_data ->altitude,
            0,
            230,
            m_insertion_data->longitude,
            m_recovery_data ->longitude,
            0,
            1600);
}

// График дальности
void MainWindow::on_distance_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Дальность, км");
    drawing(m_insertion_data->longitude,
            m_recovery_data ->longitude,
            0, 1600,
            m_insertion_data->time,
            m_recovery_data ->time,
            0,
            P->MaxTime);
}

// График скорости
void MainWindow::on_velocity_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Скорость, м/с");
    drawing(m_insertion_data->velocity,
            m_recovery_data ->velocity,
            0,
            P->fir->V+10,
            m_insertion_data->time,
            m_recovery_data ->time,
            0,
            P->MaxTime+10);
}

// График угла атаки
void MainWindow::on_alpha_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Угол атаки, град");
    drawing(m_insertion_data->attack_angle,
            m_recovery_data ->attack_angle,
            -5,
            91,
            m_insertion_data->time,
            m_recovery_data ->time,
            0,
            P->MaxTime+20);
}

// График угла наклона траектории
void MainWindow::on_T_angle_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Угол наклона траектории, град");
    drawing(m_insertion_data->trajectory_angle,
            m_recovery_data ->trajectory_angle,
            -90,
            90,
            m_insertion_data->time,
            m_recovery_data ->time,
            0,
            P->MaxTime+10);
}

// График скоростного напора
void MainWindow::on_Q_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Скоростной напор, Па");
    drawing(m_insertion_data->dynamic_pressure,
            m_recovery_data ->dynamic_pressure,
            0,
            *std::max_element(m_recovery_data ->dynamic_pressure.begin(),m_recovery_data ->dynamic_pressure.end()),
            m_insertion_data->time,
            m_recovery_data ->time,
            0,
            P->MaxTime);
}

// График центра масс
void MainWindow::on_center_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Центр масс РН, м");
    drawing(m_insertion_data->center_of_mass,
            0,
            *std::max_element(m_insertion_data->center_of_mass.begin(),m_insertion_data->center_of_mass.end()),
            m_insertion_data->time,
            0,
            P->MaxTime);
}

// График тяги
void MainWindow::on_thrust_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Тяга ДУ, кН");
    drawing(m_insertion_data->thrust,
            m_recovery_data ->thrust,
            0,
            *std::max_element(m_insertion_data->thrust.begin(),m_insertion_data->thrust.end()),
            m_insertion_data->time,
            m_recovery_data ->time,
            0,
            P->MaxTime);
}

// График массы
void MainWindow::on_mass_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Масса, кг");
    drawing(m_insertion_data->mass,
            m_recovery_data ->mass,
            0,
            *std::max_element(m_insertion_data->mass.begin(),m_insertion_data->mass.end()),
            m_insertion_data->time,
            m_recovery_data ->time,
            0,
            P->MaxTime);
}

// Файл->Выход
void MainWindow::on_action_exit_triggered()
{
    close();
}

// График фокуса
void MainWindow::on_fokus_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Фокус, м");
    drawing(m_insertion_data->focus,
            0,
            15,
            m_insertion_data->time,
            0,
            P->MaxTime);
}

// График стат момента
void MainWindow::on_static_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Стат момент X, кг м");
    drawing(m_insertion_data->static_moment,
            0,
            P->Sx,
            m_insertion_data->time,
            0,
            P->MaxTime);
}

// График момента инерции Y или Z
void MainWindow::on_YZmoment_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Момент инерции Y/Z,   кг м2");
    drawing(m_insertion_data->yz_moment,
            0,
            P->Iz,
            m_insertion_data->time,
            0,
            P->MaxTime);
}

// График момента инерции Х
void MainWindow::on_Xmoment_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Момент инерции X, кг м2");
    drawing(m_insertion_data->x_moment,
            0,
            P->Ixmax,
            m_insertion_data->time,
            0,
            P->MaxTime);
}

// Динамика
void MainWindow::on_action_5_triggered()
{
    int coun = 0;
    d->const_par(P->Lmax);


    for (int i=0;i<m_recovery_data ->time.size(); i++)
    {
        if (m_recovery_data ->time[i] < P->T_fuel[0])
        {
            d->ver_par(m_recovery_data ->time[i],
                       m_recovery_data ->mass[i],
                       m_recovery_data ->thrust[i],
                       m_recovery_data ->control_thrust[i],
                       m_recovery_data ->dynamic_pressure[i],
                       m_recovery_data ->drug_coefficient[i],
                       m_insertion_data ->stability_margin[i],
                       m_recovery_data ->stability_margin[i],
                       m_recovery_data ->velocity[i],
                       m_recovery_data ->yz_moment[i],
                       m_recovery_data ->rocket_length[i],
                       m_recovery_data ->wind_velocity[i],
                       m_insertion_data ->center_of_mass[i],
                       m_insertion_data ->focus[i]);
        }
        // else
        // {
        //     if (coun==0 && m_recovery_data ->rocket_length[i]< m_recovery_data ->rocket_length[i-1])
        //     {
        //         d->const_par(
        //             m_recovery_data ->rocket_length[i]); coun++;
        //     }
        //     d->ver_par(m_recovery_data ->mass[i],
        //                m_recovery_data ->thrust[i],
        //                m_recovery_data ->control_thrust[i],
        //                m_recovery_data ->dynamic_pressure[i],
        //                m_recovery_data ->drug_coefficient[i],
        //                m_insertion_data ->stability_margin[i],
        //                m_recovery_data ->stability_margin[i],
        //                m_recovery_data ->velocity[i],
        //                m_recovery_data ->yz_moment[i],
        //                m_recovery_data ->rocket_length[i]);
        // }

    }
}

void MainWindow::on_height_Button_2_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Частота, 1/c");
    QColor color [5] {Qt::red ,Qt::green, Qt::yellow, Qt::blue, Qt::black};
    drawing(d->W[0], 0, 90, m_insertion_data->time, 0, P->MaxTime);
    ui->widget->graph(0)->setName(QString("%1 Тон").arg(1));
    for (int i=1;i<5;i++)
    {
        ui->widget->addGraph();
        ui->widget->graph(i)->setData(m_insertion_data->time, d->W[i]);
        ui->widget->graph(i)->setPen(QPen(color[i]));
        ui->widget->graph(i)->setName(QString("%1 Тон").arg(i+1));
        ui->widget->replot();
    }

}


void MainWindow::on_height_Button_3_clicked()
{
    ui->widget->xAxis->setLabel("Длина, м");
    ui->widget->yAxis->setLabel("Коэффициент формы, -");
    QColor color [5] {Qt::red ,Qt::green, Qt::yellow, Qt::blue, Qt::black};
    drawing(d->form[0], -1, 1, d->lenght, 0, 64.4);

    ui->widget->graph(0)->setName(QString("%1 Тон").arg(1));
    for (int i=1;i<5;i++)
    {
        ui->widget->addGraph();
        ui->widget->graph(i)->setData(d->lenght, d->form[i]);
        ui->widget->graph(i)->setPen(QPen(color[i]));
        ui->widget->graph(i)->setName(QString("%1 Тон").arg(i+1));
        ui->widget->replot();
    }

}


void MainWindow::on_height_Button_4_clicked()
{
    ui->widget->xAxis->setLabel("Длина, м");
    ui->widget->yAxis->setLabel("Коэффициент формы, -");
    QColor color [5] {Qt::red ,Qt::green, Qt::yellow, Qt::blue, Qt::black};
    drawing(d->dform[0], -1, 1, d->lenght, 0, 64.4);
    ui->widget->graph(0)->setName(QString("%1 Тон").arg(1));
    for (int i=1;i<5;i++)
    {
        ui->widget->addGraph();
        ui->widget->graph(i)->setData(d->lenght, d->dform[i]);
        ui->widget->graph(i)->setPen(QPen(color[i]));
        ui->widget->graph(i)->setName(QString("%1 Тон").arg(i+1));
        ui->widget->replot();
    }


}


void MainWindow::on_pushButton_clicked()
{
    ui->widget->xAxis->setLabel("Высота, км");
    ui->widget->yAxis->setLabel("Ветер, м/с");
    drawing(m_recovery_data ->wind_velocity,
            0,
            *std::max_element(m_recovery_data ->wind_velocity.begin(),
                              m_recovery_data ->wind_velocity.end()),
                              m_recovery_data ->altitude,
                              0,
                              95);
}

