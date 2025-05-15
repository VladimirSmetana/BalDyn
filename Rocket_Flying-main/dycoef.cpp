#include "dycoef.h"
#include <QDebug>
#include <QDataStream>

DC::DC()
{
    file1.setFileName("C:/Users/smeta/OneDrive/Рабочий стол/M/BalDyn/output/freq.txt");
    file1.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file1.resize(0);

    file2.setFileName("C:/Users/smeta/OneDrive/Рабочий стол/M/BalDyn/output/oscil_coef.txt");
    file2.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file2.resize(0);

    file3.setFileName("C:/Users/smeta/OneDrive/Рабочий стол/M/BalDyn/output/motion_coef.txt");
    file3.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file3.resize(0);
}

DC::~DC()
{
     file1.close();
     file2.close();
     file3.close();
}

double DC::PI()
{
    return 3.1415926535;
}

void DC::print(double ct, double t)
{
    std::cout << ct <<" at the moment "<< t << std::endl;
}

    void DC::const_par(double len)
    {
        double a [5];
        double K[3], Y[5];
        double f[5];
        double df[5];

        for (int i=0;i<5;i++)
        {
            form[i].clear();
            dform[i].clear();
            lenght.clear();
            a[i] = lamb [i]/(len);
            K[0] = cosh(lamb [i]) - cos(lamb [i]);
            K[1] = sinh(lamb [i]) - sin(lamb [i]);
            K[2] = - K[1];
            Y[i] = K[0]/K[2];

            for (double x = 0;x<=len;x+=0.1)
            {
                lenght.push_back(x);
                f[i] =  ((sin(a[i]*x)+sinh(a[i]*x))*Y[i]+(cos(a[i]*x)+cosh(a[i]*x)))/2;
                form[i].push_back(f[i]);

                df[i] = a[i]*(Y[i]*(cos(a[i]*x)+cosh(a[i]*x))+(-sin(a[i]*x)+sinh(a[i]*x)))/2;
                dform[i].push_back(df[i]);
            }
        }

//        if(file.open(QIODevice::WriteOnly))
//        {

//        }
//        else
//        {
//            qDebug() << "Error";
//        }


    }

    void DC::ver_par(double time, double mass, double p, double p_con,
                     double q, double cy, double x1, double x2, double vel, double iner, double len, double wind, double center, double focus)
    {

         QTextStream out1(&file1);
         QTextStream out2(&file2);
         QTextStream out3(&file3);

        double D = 4.1;
        double bb = 0.004;
        double E = 70000;
        double I = M_PI*pow(D,4)/64 - M_PI*pow(D-2*bb,4)/64;
        double I4 = mass*pow(len,4);
        double EI0 = E*I * 1000000;


        double S = M_PI*pow(D,2)/4;
        double Mx = mass*0.1/64.4;
        for (int i=0;i<5;i++)
        {
            Ms[i] = 0;
            for (int k=0;k<=form[i].size();k++)
            {
                Ms[i] += Mx*pow(form[i][k],2)*0.1;
            }
            ms_vec[i].push_back(Ms[i]);

            W[i].push_back(sqrt(EI0/I4*pow(lamb[i],4)));


            CW[i].push_back(-form[i].back()*p_con/mass);
            CY[i].push_back(p_con/iner*((x2-len)*dform[i].back()+form[i].back()));

            //out1 << W[i].back()<< '\t';
            //out2 << CW[i].back()<< '\t' << CY[i].back() << '\t';


        }



        // по тангажу
        Cbs .push_back(p_con/mass); // как по рысканию
        Cyws.push_back(-(p+cy/57.3*q*S)/mass); // как по рысканию, но со знаком "-"
        Cwws.push_back((-cy/57.3*q*S*x1)/iner); // как по рысканию, но со знаком "-"
        Cyys.push_back((cy/57.3*q*S)/(mass*vel));  // как по рысканию
        Cwys.push_back((cy/57.3*q*S*x1)/iner/vel); // как по рысканию
        Cwbs.push_back(p_con*x2/iner); // как по рысканию
        Csbs.push_back(p_con/iner);

        // out3 <<  Cbs .back()<< '\t';
        // out3 <<  Cyws.back()<< '\t';
        // out3 <<  Cwws.back()<< '\t';
        // out3 <<  Cyys.back()<< '\t';
        // out3 <<  Cwys.back()<< '\t';
        // out3 <<  Cwbs.back()<< '\t';
        // out3 <<  Csbs.back()<< '\t';

        //file1.putChar('\n');
        //file2.putChar('\n');
        //file3.putChar('\n');.0

        if ((abs(time - 30.0) < 1e-5) || (abs(time - 0.1) < 1e-5) || (abs(time - 50.0) < 1e-5)) {
            qDebug()  << "Масса (" << round(time) << ") = " << mass << " кг";
            qDebug()  << "Тяга (" << round(time) << ") = " << p << " Н";
            qDebug()  << "Управляющая тяга (" << round(time) << ") = " << p_con << " Н";
            qDebug()  << "Длина ракеты (" << round(time) << ") = " << len << " м";
            qDebug()  << "Расстояние от центра масс до приложения центра аэродинамического давления (" << round(time) << ") = " << x1 << " м";
            qDebug()  << "Расстояние от центра масс до приложения силы P (" << round(time) << ") = " << x2 << " м";
            qDebug()  << "Скорость (" << round(time) << ") = " << vel << "м/с";
            qDebug()  << "К-т подъемной силы cya (" << round(time) << ") = " << cy;
            qDebug()  << "Момент инерции Х (" << round(time) << ") = " << iner << "кгм4";
            qDebug()  << "Скоростной напор (" << round(time) << ") = " << q << "кг/мс2";
            qDebug()  << "Скорость ветра (" << round(time) << ") = " << wind << "м/с";
            qDebug()  << "Центр (" << round(time) << ") = " << center << "м/с";
            qDebug()  << "Фокус (" << round(time) << ") = " << focus << "м/с";

            qDebug()  << "Cb (" << round(time) << ") = "<< Cbs .back();
            qDebug()  << "Cyw (" << round(time) << ") = "<< Cyws.back();
            qDebug()  << "Cww (" << round(time) << ") = "<< Cwws.back();
            qDebug()  << "Cyy (" << round(time) << ") = "<< Cyys.back();
            qDebug()  << "Cwy (" << round(time) << ") = "<< Cwys.back();
            qDebug()  << "Cwb (" << round(time) << ") = "<< Cwbs.back();
            qDebug()  << "Csb (" << round(time) << ") = "<< Csbs.back();
            qDebug()  << "------";
        }
        // if (time < 55) {
        //     qDebug()  <<  Cwys.back();
        //     qDebug()  <<  Cwws.back();
        //     qDebug()  <<  Cwbs.back();
        //     qDebug()  <<  Cyys.back();
        //     qDebug()  <<  Cbs.back();
        //     qDebug()  <<  Cyws.back();
        //     qDebug()  <<  wind ;
        // }

    }


    QVector<double> DC::get_V()
    {
        return get_v;
    };

    QVector<double> DC::get_T()
    {
        return get_t;
    };

