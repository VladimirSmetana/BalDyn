#include "dycoef.h"
#include <QDebug>
#include <QDataStream>

DC::DC()
{
    file1.setFileName("dow.txt");
    file1.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file1.resize(0);

    file2.setFileName("cin.txt");
    file2.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file2.resize(0);
}

DC::~DC()
{
     file1.close();
     file2.close();
}

double DC::PI()
{
    return 3.1415926535;
}

void DC::print(double ct, double t)
{
    std::cout << ct <<" at the moment "<< t << std::endl;
}

    void DC::const_par(double mass, double len)
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

    void DC::ver_par(double mass, double p, double p_con,
                     double q, double cy, double x1, double x2, double vel, double iner, double len)
    {

         QTextStream out1(&file1);
         QTextStream out2(&file2);

        double D = 4.1;
        double R = D/2;
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

            out1 << W[i].back()<< '\t';
            out2 << CW[i].back()<< '\t' << CY[i].back() << '\t';
        }
        file1.putChar('\n');
        file2.putChar('\n');
        // по тангажу
        Cbs.push_back(p_con/mass); // как по рысканию
        Cyws.push_back(-(p+cy/57.3*q*S)/mass); // как по рысканию, но со знаком "-"
        Cwws.push_back((-cy/57.3*q*S*x1)/iner); // как по рысканию, но со знаком "-"
        Cyys.push_back((cy/57.3*q*S)/(mass*vel));  // как по рысканию
        Cwys.push_back((cy/57.3*q*S*x1)/iner/vel); // как по рысканию
        Cwbs.push_back(p_con*x2/iner); // как по рысканию
        Csbs.push_back(p_con/iner);

    }


    QVector<double> DC::get_V()
    {
        return get_v;
    };

    QVector<double> DC::get_T()
    {
        return get_t;
    };

