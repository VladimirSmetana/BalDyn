#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pitch.h"


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
void MainWindow::drawing(QVector<double> Y1, double y0,  double yk,
QVector<double> X1, double x0 , double xk)
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(X1, Y1);
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->xAxis->setRange(x0, xk);
    ui->widget->yAxis->setRange(y0, yk);
    ui->widget->replot();
}
// -
void MainWindow::drawing(QVector<double> Y1,
                         QVector<double> Y2, double y0,  double yk,
                         QVector<double> X1,
                         QVector<double> X2, double x0 , double xk)
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
    Peng[0] = p1.toDouble() * 9.81 * (mpn+mb[0]+mb[1]);
    Peng[1] = p2.toDouble() * 9.81 * (mpn+mb[1]);

    P->pitch_calculations();
    double coef_alpha [3] {0, al1.toDouble(), al2.toDouble()};

    }
    //db.close();
    QString mk2s = QString::number(first->V);        ui->lineEdit  ->setText(mk2s);
    QString mk1s = QString::number(first->tY/1000);        ui->lineEdit_2->setText(mk1s);
    QString mk3s = QString::number(dep);      ui->lineEdit_3->setText(mk3s);
    QString mk5s = QString::number(second->tX/1000); ui->lineEdit_7->setText(mk5s);
    QString mk6s = QString::number(MHSP_1);    ui->lineEdit_6->setText(mk6s);
    QString mk8s = QString::number(57.3*Ott_1);       ui->lineEdit_8->setText(mk8s);
    QString mk9s = QString::number(57.3*Ott_2);       ui->lineEdit_9->setText(mk9s);
    QString mk12s = QString::number(amax);       ui->lineEdit_12->setText(mk12s);
    QString mk13s = QString::number(57.3*second->anY);       ui->lineEdit_13->setText(mk13s);

    //ui->label_2->setText("Скорость, м/с");
    //ui->label_3->setText("Высота, км");
    //ui->label  ->setText("Время полета, с");
    //ui->label_8->setText("Макс скор напор, кг/мс2");
    //ui->label_9->setText("Дальность, км");

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
    drawing(P->Lon, P->Lonre, 0, 10, P->xn, P->xn, 0, count*h);
}

// График траектории
void MainWindow::on_height_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Высота, км");
    drawing(P->H1, P->H2, 0, 230, P->xn, P->xn, 0, count*h+50);
}

// График высоты
void MainWindow::on_trj_Button_clicked()
{
    ui->widget->xAxis->setLabel("Дальность, км");
    ui->widget->yAxis->setLabel("Высота, км");
    drawing(P->H1, P->H2, 0, 230, P->Long_1, P->Long_2, 0, 1600);
}

// График дальности
void MainWindow::on_distance_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Дальность, км");
    drawing(P->Long_1, P->Long_2, 0, 1600, P->xn, P->xn, 0, count*h);
}

// График скорости
void MainWindow::on_velocity_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Скорость, м/с");
    drawing(P->v_1, P->v_2, 0, first->V+10, P->xn, P->xn, 0, count*h+10);
}

// График угла атаки
void MainWindow::on_alpha_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Угол атаки, град");
    drawing(P->ALI_1, P->ALI_2, -5, 91, P->xn, P->xn, 0, count*h+20);
}

// График угла наклона траектории
void MainWindow::on_T_angle_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Угол наклона траектории, град");
    drawing(P->TET_1, P->TET_2, -90, 90, P->xn, P->xn, 0, count*h+10);
}

// График скоростного напора
void MainWindow::on_Q_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Максимальный скоростной напор, Па");
    drawing(P->yu_1, P->yu_2, 0, *std::max_element(P->yu_2.begin(),P->yu_2.end()), P->xn, P->xn, 0, count*h);
}

// График центра масс
void MainWindow::on_center_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Центр масс РН, м");
    drawing(P->center_1, 0, *std::max_element(P->center_1.begin(),P->center_1.end()), P->xn, 0, count*h);
}

// График тяги
void MainWindow::on_thrust_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Тяга ДУ, кН");
    drawing(P->P1, P->P2, 0, *std::max_element(P->P1.begin(),P->P1.end()), P->xn, P->xn, 0, count*h);
}

// График массы
void MainWindow::on_mass_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Масса, кг");
    drawing(P->mass_1, P->mass_2, 0, *std::max_element(P->mass_1.begin(),P->mass_1.end()), P->xn, P->xn, 0, count*h);
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
    drawing(P->f1, 0, 15, P->xn, 0, count*h);
}

// График стат момента
void MainWindow::on_static_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Стат момент X, кг м");
    drawing(P->sinn, 0, Sx, P->xn, 0, count*h);
}

// График момента инерции Y или Z
void MainWindow::on_YZmoment_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Момент инерции Y/Z,   кг м2");
    drawing(P->jinn, 0, Iz, P->xn, 0, count*h);
}

// График момента инерции Х
void MainWindow::on_Xmoment_Button_clicked()
{
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Момент инерции X, кг м2");
    drawing(P->lin, 0, Ixmax, P->xn, 0, count*h);
}

// Управление ПИД
void MainWindow::on_action_5_triggered()
{
    DC d;
    d.data_writing(P->xn, P->v_2, P->H2, P->w, P->mass_2, P->P2, P->pc2, P->yu_2, P->ALI_2, P->cy2, P->dyn1, P->dyn2, P->jinn2);

    QString k14=ui->lineEdit_14->text(); double P = k14.toDouble();
    QString k15=ui->lineEdit_15->text(); double I = k15.toDouble();
    QString k16=ui->lineEdit_16->text(); double D = k16.toDouble();
    d.get_T().clear();
    d.get_V().clear();
    d.data_calculating(P, I, D);

    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Отклонение по тангажу, м");

    drawing(d.get_V(), -20, 20, d.get_T(), 405, 440);
}
