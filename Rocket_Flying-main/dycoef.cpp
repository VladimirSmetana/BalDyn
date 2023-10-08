#include "dycoef.h"

double DC::PI()
{
    return 3.1415926535;
};

void DC::print(double ct, double t)
{
    std::cout << ct <<" at the moment "<< t << std::endl;
}

void DC::data_writing(QVector<double> xn, QVector<double> v_2, QVector<double> H2,
                  QVector<double> w, QVector<double> mass_2, QVector<double> P2,
                  QVector<double> pc2, QVector<double> yu_2, QVector<double> ALI_2,
                  QVector<double> cy2, QVector<double> dyn1, QVector<double> dyn2,
                  QVector<double> jinn2)

{

            double PI = 3.1415926535;
            double const D = 4.1;
            double const L = 64.4;
            double S = PI*pow(D,2)/4;
            int kkk = 0;
            double ms;

            Cbs.clear();
            Cyws.clear();
            Cwws.clear();
            Cyys.clear();
            Cwys.clear();
            Cwbs.clear();
            Csbs.clear();
            dypresss.clear();
            masss.clear();
            Wind.clear();
            times.clear();
            vels.clear();
            W[0].clear();
            W[1].clear();
            W[2].clear();
            W[3].clear();
            W[4].clear();
            CW[0].clear();
            CW[1].clear();
            CW[2].clear();
            CW[3].clear();
            CW[4].clear();
            CY[0].clear();
            CY[1].clear();
            CY[2].clear();
            CY[3].clear();
            CY[4].clear();

        for(int i=0;i<xn.size();i++)
        {

            Cbs.push_back(pc2[i]/mass_2[i]);
            Cyws.push_back(-(P2[i]+cy2[i]/57.3*yu_2[i]*S)/mass_2[i]);
            Cwws.push_back((-cy2[i]/57.3*yu_2[i]*S*dyn1[i])/jinn2[i]);
            Cyys.push_back((cy2[i]/57.3*yu_2[i]*S)/(mass_2[i]*v_2[i]));
            Cwys.push_back((-cy2[i]/57.3*yu_2[i]*S*dyn1[i])/jinn2[i]/v_2[i]);

            Cwbs.push_back(pc2[i]*dyn2[i]/jinn2[i]);

            Csbs.push_back(pc2[i]/jinn2[i]);

            dypresss.push_back(yu_2[i]);
            masss.push_back(mass_2[i]);
            Wind.push_back(w[i]);
            times.push_back(xn[i]);
            vels.push_back(v_2[i]);


            ms = masss[1293];
            W[0].push_back(10.84*ms/masss[i]);
            W[1].push_back(29.87*ms/masss[i]);
            W[2].push_back(58.57*ms/masss[i]);
            W[3].push_back(96.8*ms/masss[i]);
            W[4].push_back(144.61*ms/masss[i]);


            CW[0].push_back(Csbs[i]);
            CW[1].push_back(-Csbs[i]);
            CW[2].push_back(Csbs[i]);
            CW[3].push_back(-Csbs[i]);
            CW[4].push_back(Csbs[i]);


            CY[0].push_back(-0.108*Cbs[i]);
            CY[1].push_back(0.183*Cbs[i]);
            CY[2].push_back(-0.256*Cbs[i]);
            CY[3].push_back(0.326*Cbs[i]);
            CY[4].push_back(-0.403*Cbs[i]);

            //std::cout << (Cyws[i]) << std::endl;//*yu_2[i]*S*dyn1[i]);///jinn2[i]/v_2[i] << std::endl;

//            if (kkk==100 || kkk==0)
//            {
//            std::cout << W[0][i] << std::endl;
//                kkk=0;
//            }
//                        kkk+=1;
        }


    }
    void DC::data_calculating(double P, double I, double D)
    {
        double PI = 3.1415926535;

        double Summ_Cws, Summ_Cvs;
        double KK, KS[5], KdS[5], KddS[5], Summ_KS[5];

        double h = 0.1;

        double goal = 0;
        PID pid(P, I, D, h, goal);

        double bmax = 7 / 57.3;

        double s[5];
        double ds[5];
        double dds[5];


        double
            wu = 0,
            dw = 0,
            ddw = 0,
            y = 0,
            v = 0,
            dv = 0,
            u = 0,
            du = 0,
            ddu = 0,
            uc = 0,
           // Summ_Cws=0,
           // Summ_Cvs=0,
            Summ_S=0;
            //Q = 0;


        for (int i = 0; i < 5; i++)
        {
            s[i] = 0;
            ds[i] = 0;
            dds[i] = 0;
        }



        double Qs = 0; //= -4.2*pow(10, -9);
        double Qw = 0; //= 3.4*pow(10, -11);
        double Qv = 0; //= 3.64*pow(10, -8);

        for (int i=4050;i<4373;i++)
        {
            uc = pid.signal(wu);
            if (uc >= bmax) uc = bmax;
            if (uc <=-bmax) uc =-bmax;

            Qs = 0; //dypresss[i]*(-3.89*pow(10, -11));
            Qw = 0; //dypresss[i]*(-2.67*pow(10, -13));
            Qv = 0; // = dypresss[i]*(4.97*pow(10, -8));

                Summ_Cws = CW[0][i]*s[0] + CW[1][i]*s[1] + CW[2][i]*s[2] + CW[3][i]*s[3] + CW[4][i]*s[4];
                Summ_Cvs = CY[0][i]*s[0] + CY[1][i]*s[1] + CY[2][i]*s[2] + CY[3][i]*s[3] + CY[4][i]*s[4];

                double AU = Qs * (wu - (v - Wind[i]) / vels[i]);

                KS[0] = 0;   KS[1] = 0;   KS[2] = 0;         KS  [3] = 0;      KS[4]  = 0;
                KdS[0] = 0;  KdS[1] = 0;  KdS[2] = 0;        KdS [3] = 0;      KdS[4] = 0;
                KddS[0] = 0; KddS[1] = 0; KddS[2] = 0;       KddS[3] =0;       KddS[4]= 0;

                for (int j = 0; j < 5; j++)
                {
                        Summ_KS[j] = KS[j] * s[j] + KdS[j] * ds[j];
                        Summ_S += s[j];
                }

                dv =  - Cyws[i] * wu - Cyys[i] * v  + Cbs[i] * uc  + Cyws[i] * Wind[i];
                ddw =  - Cwws[i] * wu - Cwbs[i] * uc  - Cwys[i] * v + Cwys[i] * Wind[i];


                //dv =  - Cyws[i] * wu - Cyys[i] * v  + Cbs[i] * uc  - Summ_Cvs + Cyws[i] * Wind[i];
                //ddw =  - Cwws[i] * wu - Cwbs[i] * uc -Summ_Cws - Cwys[i] * v + Cwys[i] * Wind[i];

                dds[0] = -h * sqrt(W[0][i]) / PI * ds[0] - W[0][i] * s[0] + Csbs[i] * uc - Summ_KS[0];
                dds[1] = -h * sqrt(W[1][i]) / PI * ds[1] - W[1][i] * s[1] - Csbs[i] * uc - Summ_KS[1];
                dds[2] = -h * sqrt(W[2][i]) / PI * ds[2] - W[2][i] * s[2] + Csbs[i] * uc - Summ_KS[2];
                dds[3] = -h * sqrt(W[3][i]) / PI * ds[3] - W[3][i] * s[3] - Csbs[i] * uc - Summ_KS[3];
                dds[4] = -h * sqrt(W[4][i]) / PI * ds[4] - W[4][i] * s[4] + Csbs[i] * uc - Summ_KS[4];
                dv     -= Qv * s[0];
                ddw    -= Qw * s[0];
                dds[0] -= AU;





                v += h * dv;
                y += h * v;
                dw += h * ddw;
                wu += h * dw;
                du += h * ddu;
                u += h * du;

                get_t.push_back(times[i]);
                DC::print(v/1000,times[i]);
                get_v.push_back(v/1000);



                //get_v.push_back(uc*57.3);wu*57.3
                //std::cout << times[i]<<"_____"<< cy_2[i] <<std::endl;



                for (int j = 0; j <5; j++)
                {
                        ds[j] += h * dds[j] * pow(1+KddS[j],-1);
                        s[j] += h * ds[j] * pow(1 + KdS[j], -1);
                        s[j] = s[j] * pow(1 + KS[j], -1);
                }

                //if (abs(wu)*57.3>=5 || abs(v) >= 10 ) {break;}
        }

        return;
    }

    QVector<double> DC::get_V()
    {
        return get_v;
    };

    QVector<double> DC::get_T()
    {
        return get_t;
    };

