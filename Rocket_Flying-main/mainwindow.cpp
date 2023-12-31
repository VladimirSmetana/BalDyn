#include "mainwindow.h"
#include "ui_mainwindow.h"




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

// Глобальные векторы
QVector<double>lin(0);
QVector<double>sinn(0);
QVector<double> jinn(0), jinn2(0);
QVector<double>CM(0);
QVector<double>ALI_1(0);
QVector<double>ALI_2(0);
QVector<double>res(0);
QVector<double>TET_1(0);
QVector<double>TET_2(0);
QVector<double>center_1(0);
QVector<double>center_2(0);
QVector<double>be(0);
QVector<double>pi(0);
QVector<double>yu_1(0);
QVector<double>yu_2(0);
QVector<double>mass_1(0);
QVector<double>mass_2(0);
QVector<double> xn(0);
QVector<double> v_1(0), v_2(0), v_3(0);
QVector<double> Long_1(0), Long_2(0), H1(0), H2(0), H3(0);
QVector<double> angle(0), b1(0), b2(0);
QVector<double> P1(0), P2(0);
QVector<double> f1(0);
QVector<double> Lon(0), Lonre(0);
QVector<double> w(0), pc2(0);
QVector<double> cy2(0);
QVector<double> dyn1(0), dyn2(0);
//
// Кнопка "Трасса полета"
void MainWindow::on_action_triggered()
{
    // Параметры тяги и угла атаки
    QString p1=ui->lineEdit_10->text();
    QString p2=ui->lineEdit_11->text();
    QString al1=ui->lineEdit_5->text();
    QString al2=ui->lineEdit_4->text();
    Peng[0] = p1.toDouble() * 9.81 * (mpn+mb[0]+mb[1]);
    Peng[1] = p2.toDouble() * 9.81 * (mpn+mb[1]);

    double coef_alpha [3] {0, al1.toDouble(), al2.toDouble()};
    //
    // Рассчитываемые параметры конструкции
        double m_fuel[2];
        double m_dry[2];
        double T_fuel[2];
        double m_furet = 33200/*2200*/, m_reC = m_furet*1/4.5, m_reO = m_furet*3.5/4.5;
        M_Rocket=mpn;
        first->m_t = M_Rocket;
        second->m_t = M_Rocket;
    //
    // Время действия тормозных импульсов

    //
    // Поле локальных переменных
     Smid = M_PI*pow(D,2)/4;
        first->V = 0.1;
     second->V = 0.6;


    count =0;



    //
    // Создание объектов

    mass M;
    //
    // Определение габаритов ракеты
    M.MCI_f(0, h, mpn, D, mb[0], mb[1], s[0], s[1], Peng[0], Peng[1]);
    Lmax = M.get_lenght();
    //double L = Lmax;
    double L1= M.get_lst1();
    double L2= M.get_lst2();
    //
    // Определение основных мцих
    for (int i=0;i<=1;i++)
    {
        m_fuel[i] = mb[i] * (s[i] - 1) / s[i];
        m_O[i] = m_fuel[i]*Ratio/(Ratio+1);
        m_C[i] = m_fuel[i]*1/(Ratio+1);
        m_dry[i] = mb[i]-m_fuel[i];
    }
        m_dry[0]-=m_furet;
        M_Rocket+=m_fuel[0]+m_dry[0]+m_fuel[1]+m_dry[1] + m_furet;

        double zap = 0;
        m_dry [1]+=zap;

        double onefu = m_fuel[0];
        M_stage [0] = M_Rocket;
        M_stage [1] = M_Rocket - mb[0];

        first->S_dry[0] = M.fun_S (M.K[6], M.K[12], m_dry[0]);
        first->S_dry[1] = M.fun_S (M.K[1], M.K[6], m_dry[1]);
        second->S_dry[0] = M.fun_S (M.K[6]-21.5, M.K[12]-21.5, m_dry[0]);
        second->S_dry[1] = M.fun_S (M.K[1]-21.5, M.K[6]-21.5, m_dry[1]);
        S_o[0] = M.fun_S (M.K[8], M.K[9], m_O[0]);
        S_c[0] = M.fun_S (M.K[10], M.K[11], m_C[0]);
        S_o[1] = M.fun_S (M.K[3], M.K[4], m_O[1]);
        S_c[1] = M.fun_S (M.K[5], M.K[6], m_C[1]);
        first->S_reO = M.fun_S (M.K[9], M.K[10], m_reO);
        first->S_reC = M.fun_S (M.K[11], M.K[13], m_reC);
        second->S_reO = M.fun_S (M.K[9 ]-21.5, M.K[10]-21.5, m_reO);
        second->S_reC = M.fun_S (M.K[11]-21.5, M.K[13]-21.5, m_reC);

        first->Ssumm  = M.get_SGO() + first->S_dry[0] + first->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + first->S_reO + first->S_reC;
        Sx = first->Ssumm;
        first->gl_c = first->Ssumm/M_Rocket;
        gl_cmax = first->gl_c;
        //std::cout<<Sx<<std::endl;
        //std::cout<<first->gl_c<<std::endl;

        first->I_dry[0] = M.fun_I (M.K[6], M.K[12], m_dry[0], D);
        first->I_dry[1] = M.fun_I (M.K[1], M.K[6], m_dry[1], D);

        second->I_dry[0] = M.fun_I (M.K[6]-6, M.K[12]-6, m_dry[0], D);

        I_o[0] = M.fun_I (M.K[8], M.K[9], m_O[0], D);
        I_c[0] = M.fun_I (M.K[10], M.K[11], m_C[0], D);
        I_o[1] = M.fun_I (M.K[3], M.K[4], m_O[1], D);
        I_c[1] = M.fun_I (M.K[5], M.K[6], m_C[1], D);
        first->I_reO = M.fun_I (M.K[9], M.K[10], m_reO, D);
        first->I_reC = M.fun_I (M.K[11], M.K[13], m_reC, D);
        second->I_reO = M.fun_I (M.K[9 ]-21.5, M.K[10]-21.5, m_reO, D);
        second->I_reC = M.fun_I (M.K[11]-21.5, M.K[13]-21.5, m_reC, D);
        first->Isumm  = M.get_IGO() + first->I_dry[0] + first->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + first->I_reO + first->I_reC - M_Rocket*pow(gl_cmax,2);
        Iz = first->Isumm;
        Izmax = Iz;
        Ix = M_Rocket * pow(D/2, 2);
        Ixmax = Ix;

        T_fuel[0] = m_fuel[0]/(Peng [0]/Imp[0]);
        T_stage [0] = T_fuel [0] + T_sep [0];
        T_fuel[1] = m_fuel[1]/(Peng [1]/Imp[1]);
        T_stage [1] = T_fuel [1] + T_sep [1];
    //
    // ИД итеративного расчета
        first->m_t = M_Rocket;
        second->m_t = M_Rocket;
        first->anY = M_PI/2;
        second->anY = M_PI/2;
        //double p_ground = 101325;
        second->tY = 1;
    //
    // Итеративный расчет
    H1.clear();
    H2.clear();
    xn.clear();
    count = 0;
    first->tY = 0;
    second->tX = 0;
    int i = 0;
    int value = 0;
    d_O[1] = 0;
    //while (second->tY>=0.5 && second->V>=0.5) second->tY>=0.5
    while (second->tY>0 && second->V>0)
    {
        airforce Qus_1 (Mah_1);
        airforce Qus_2 (Mah_2);

        focus F;

           atmosphere Atm_1 (first->tY);
           atmosphere Atm_2 (second->tY);
           eastwind W1 (first->tY/1000);
           eastwind W2 (second->tY/1000);


           // Участок работы ДУ-1
           if (time<=T_fuel[0])
                {
                 //if (m_t > M_Rocket-onefu )
                 //{
                 first->Peng_t = Peng[0];
                 second->Peng_t = Peng[0];
                 second->Peng_control = second->Peng_t/2;
                 //+ (p_ground - P.get_pressure()) * Smid/2;
                 Imp_t = Imp[0];
                 CF = first->Peng_t/Imp_t;
                 first-> m_t = m_fuel[0]+m_fuel[1]+m_dry[0]+m_dry[1]+ m_reC + m_reO +mpn;
                 second->m_t = m_fuel[0]+m_fuel[1]+m_dry[0]+m_dry[1]+ m_reC + m_reO +mpn;
                 m_O[0] = Ratio*m_fuel[0]/(Ratio+1);
                 m_C[0] = m_fuel[0]/(Ratio+1);
                 m_fuel[0] -= CF*h;
                 d_O[0] += Ratio*CF*h/(1100*Smid)/(Ratio+1);
                 d_C[0] += CF*h/(440*Smid)/(Ratio+1);
                 S_o[0] = M.fun_S (M.K[8]+d_O[0], M.K[9], m_O[0]);
                 S_c[0] = M.fun_S (M.K[10]+d_C[0], M.K[11], m_C[0]);
                 // First в second->e не ошибка, а условность СК
                 first->Ssumm  = M.get_SGO() + first->S_dry[0] + first->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + first->S_reO + first->S_reC;
                 second->Ssumm = M.get_SGO() + first->S_dry[0] + first->S_dry[1] + S_o[0] + S_c[0] + S_o[1] + S_c[1] + first->S_reO + first->S_reC;
                 first->gl_c = first->Ssumm/first->m_t;
                 second->gl_c = second->Ssumm/second->m_t;

                 I_o[0] = M.fun_I (M.K[8]+d_O[0], M.K[9], m_O[0], D);
                 I_c[0] = M.fun_I (M.K[10]+d_C[0], M.K[11], m_C[0], D);
                 first->Isumm  = M.get_IGO() + first->I_dry[0] + first->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + first->I_reC +first->I_reO - first->m_t*pow (first->gl_c,2);

                 second->Isumm = M.get_IGO() + first->I_dry[0] + first->I_dry[1] + I_o[0] + I_c[0] + I_o[1] + I_c[1] + first->I_reC +first->I_reO - second->m_t*pow(second->gl_c,2);
                 Ix = first->m_t * pow(D/2, 2);
                 //}
                 //else T_fuel[0] = time;
                 //if (abs(m_t - (M_Rocket-m_fuel[0])) < 100) T_fuel[0] = time;
                 first->L  = Lmax;
                 second->L = Lmax;
                 Ott_1 = first->anY;
                 H_1 = first->tY/1000;
                 CILCON = 12.88;
                 dep = count*h;
                 second->focus = F.Focus(Mah_1, D, M.get_lengo(), M.get_wgo(), M.get_CIL(), CILCON);
                 X_oneC = second->gl_c - second->focus;
                 X_twoC = second->L - second->gl_c;
                }
           // Участок разделения 1-2
           if (time >T_fuel[0] && time<=T_fuel[0] + T_sep[0])
                {
                 first->Peng_t = 0;
                 second->Peng_t = 0;
                 second->Peng_control = second->Peng_t/2;
                 Imp_t = 0;
                 CF = 0;
                 first->m_t = m_fuel[1]+m_fuel[0]+m_dry[1]+mpn;
                 second->m_t = m_dry[0] + m_reC + m_reO;
                 first->Ssumm  = M.get_SGO() + first->S_dry[1]+ S_o[0] + S_c[0] + S_o[1] + S_c[1];
                 second->Ssumm = second->S_dry[0] + second->S_reC + second->S_reO;
                 first->gl_c = first->Ssumm/first->m_t;
                 second->gl_c = second->Ssumm/second->m_t;
                 first->L = Lmax - L1;
                 second->L = L1;
                 CILCON = 3.42;
                 X_oneC = 0;
                 X_twoC = 0;
                }

           // Участок работы ДУ-2
           if (time>T_fuel[0] + T_sep[0] && time<=T_fuel[0] + T_sep[0]+T_fuel[1])
                {
                 first->Peng_t = Peng[1];
                 second->Peng_t = 0;
                 second->Peng_control = second->Peng_t/2;
                 Imp_t = Imp[1];
                 CF = first->Peng_t/Imp_t;
                 first->m_t = m_fuel[1]+m_fuel[0]+m_dry[1]+mpn;
                 second->m_t = m_dry[0] + m_reC + m_reO;

                 m_O[1] = Ratio*m_fuel[1]/(Ratio+1);
                 m_C[1] = 1*m_fuel[1]/(Ratio+1);

                 m_fuel[1] -= CF*h;
                 d_O[1] += CF*h *Ratio/(1100*Smid)/(Ratio+1);
                 d_C[1] += CF*h /(440*Smid)/(Ratio+1);
                 S_o[1] = M.fun_S (M.K[3]+d_O[1], M.K[4], m_O[1]);
                 S_c[1] = M.fun_S (M.K[5]+d_C[1], M.K[6], m_C[1]);
                 first->Ssumm = M.get_SGO() + first->S_dry[1]+ S_o[0] + S_c[0] + S_o[1] + S_c[1];

                // std::cout << CF*h *Ratio/(1100*Smid)/(Ratio+1) << CF << std::endl;

                 second->Ssumm = second->S_dry[0] + second->S_reC + second->S_reO;
                 first->gl_c = first->Ssumm/first->m_t;
                 second->gl_c = second->Ssumm/second->m_t;
                 first->gl_c = first->gl_c/2;
                 second->gl_c = second->gl_c/2;
                 I_o[1] = M.fun_I (M.K[3]+d_O[1], M.K[4], m_O[1], D);
                 I_c[1] = M.fun_I (M.K[5]+d_C[1], M.K[6], m_C[1], D);
                 first->Isumm = M.get_IGO() +first->I_dry[1]+ I_o[0] + I_c[0] + I_o[1] + I_c[1]- first->m_t*pow(first->gl_c,2);
                 second->Isumm = second->I_dry[0] + second->I_reC + second->I_reO - second->m_t*pow(second->gl_c,2);
                 first->Isumm = first->Isumm;
                 second->Isumm = second->Isumm;
                 Ix = first->m_t * pow(D/2, 2);
                 first->L = Lmax - L1;
                 second->L = L1;

                 Ott_2 = first->anY;
                 CILCON = 3.42;
                 X_oneC = 0;
                 X_twoC = 0;
                }
           // Участок разделения 2-ПН
           if (time>T_fuel[0] + T_sep[0]+T_fuel[1] && time<=T_fuel[0] + T_sep[0]+T_fuel[1] + T_sep[1])
                {
                 first->Peng_t = 0;
                 second->Peng_t = 0;
                 second->Peng_control = second->Peng_t/2;
                 Imp_t = 0;
                 CF = 0;
                 first->m_t = m_dry[1]+mpn;
                 second->m_t = m_dry[0] + m_reC + m_reO;
                 first->Ssumm = M.get_SGO() + first->S_dry[1]+ S_o[0] + S_c[0] + S_o[1] + S_c[1] ;
                 second->Ssumm = second->S_dry[0] + second->S_reC + second->S_reO;
                 first->gl_c = first->Ssumm/first->m_t;
                 second->gl_c = second->Ssumm/second->m_t;
                 first->L = Lmax - L1 - L2;
                 second->L = L1;

                 CILCON = 1.4;
                 X_oneC = 0;
                 X_twoC = 0;
                }
           // Участок полета ПН
           if (time>T_fuel[0] + T_sep[0]+T_fuel[1] + T_sep[1])
                {
                 first->Peng_t = 0;
                 second->Peng_t = 0;
                 second->Peng_control = second->Peng_t/2;
                 Imp_t = 0;
                 CF = 0;
                 first->m_t = mpn;
                 second->m_t = m_dry[0];
                 first->Ssumm = M.get_SGO() + S_o[0] + S_c[0] + S_o[1] + S_c[1];
                 second->Ssumm = second->S_dry[0] + second->S_reC + second->S_reO;
                 first->gl_c = first->Ssumm/first->m_t;
                 first->L = Lmax - L1 - L2;
                 second->L = L1;
                 CILCON = 1.4;
                 X_oneC = 0;
                 X_twoC = 0;
                }
            //Участок возвращения

           if ((time>k1 && time<k2) || (time>k3 && time<k4))
           {
                 if (m_furet>=0)
                 {
                   if (time>k1 && time<k2) (second->Peng_t = kk1*Peng[0]);
                   if (time>k3 && time<k4) (second->Peng_t = kk2*Peng[0]);
                   second->Peng_control = second->Peng_t;
                   Imp_t = Imp[0];
                   CF = second->Peng_t/Imp_t;
                   m_reC -= CF*h * 1/(3.5+1);
                   m_reO -= CF*h * 3.5/(3.5+1);
                   m_furet = m_reC + m_reO;
                   second->m_t = m_dry[0] + m_reC + m_reO;
                   deo += CF*h *Ratio/(1100*Smid)/(Ratio+1);
                   dec += CF*h /(440*Smid)/(Ratio+1);
                   second->S_reO = M.fun_S (M.K[9 ]-21.5 + deo, M.K[10]-21.5, m_reO);
                   second->S_reC = M.fun_S (M.K[11]-21.5 + dec, M.K[13]-21.5, m_reC);
                   second->Ssumm = second->S_dry[0] + second->S_reC + second->S_reO;
                   second->gl_c = second->Ssumm/second->m_t;
                   second->I_reO = M.fun_I (M.K[9 ]-21.5 + deo, M.K[10]-21.5, m_reO, D);
                   second->I_reC = M.fun_I (M.K[11]-21.5 + dec, M.K[13]-21.5, m_reC, D);
                   second->Isumm = second->I_dry[0] + second->I_reC + second->I_reO - second->m_t*pow(second->gl_c,2);
                   second->Isumm = second->Isumm;
                   second->L = L1;
                   second->focus = 0.7*second->L;
                   X_oneC = second->gl_c - second->focus;
                   X_twoC = second->L - second->gl_c;
                 };


           }

          // std::cout<<"t = "<<count*h<<std::endl;
          // std::cout<<"H = "<<second->tY/1000<<std::endl;
          // std::cout<<"V = "<<second->V<<std::endl;
          // std::cout<<"m = "<<m_reC+m_reO<<std::endl;

           // Программа угла атаки
           alpha alph_1 (first->V,  coef_alpha [1], coef_alpha [2], time, T_stage [0], 0, k2, k3);
           alpha alph_2 (second->V, coef_alpha [1],              0, time, 200, 180, k2, k3);

           // Учет параметров атмосферы




           //HSP = (P.get_density()/2)*pow(V,2);
           HSP_p_1 = HSP_1;
           HSP_1 = (Atm_1.get_density()/2)*pow(first->V,2);
           HSP_p_2 = HSP_2;
           HSP_2 = (Atm_2.get_density()/2)*pow(second->V,2);
           Mah_1 = first->V/Atm_1.get_SV();
           Mah_2 = second->V/Atm_2.get_SV();

           first->focus = F.Focus(Mah_1, D, M.get_lengo(), M.get_wgo(), M.get_CIL(), CILCON);
           //std::cout << Focus << std::endl;
           //Focus = M.Focus(Mah_1, D, M.get_lengo(), M.get_wgo());
           //qDebug()<<M.K[10]+d_C[0];

           if (time<T_stage[0]) {CX_1=Qus_1.getCX();  } else {CX_1=0;  }
           if (time<T_stage[0]) {CY_1=Qus_1.getCY();  } else {CY_1=0;  }
           CX_2=Qus_2.getCX();
           CY_2=Qus_2.getCY();
           bpr = ((Atm_1.get_density()/2*pow(first->V,2))*Smid*first->L*CY_1*first->alpha)/(first->Peng_t*(first->L-first->gl_c));

           equations B_1 (Atm_1.get_density(), Smid, Atm_1.get_AOG(), first->m_t, CX_1, CY_1, first->Peng_t, alph_1.A(), Wind1);
           equations B_2 (Atm_2.get_density(), Smid, Atm_2.get_AOG(), second->m_t, CX_2, CY_2, second->Peng_t, alph_2.A(), Wind2);

           //dV = B_1.fdV(first->V, first->anY);
           dN = B_1.fdN(first->tY, first->V, first->anY);

           Ott = first->anY-Na;
           pitch = Ott-first->alpha/57.3;

           first->tX += h * (first->V* cos(first->anY)+X1)/2;
           second->tX += h * (second->V* cos(second->anY)+X2)/2;

           X1 = first->V* cos(first->anY);
           X2 = second->V* cos(second->anY);


            Wind1 = W1.WSol();
            Wind2 = W2.WSol();

            if (time<120 &&  HSP_1<HSP_p_1 && e<1)
            {

                MHSP_1 = HSP_1;
                VHSP_1 = first->V;
                e+=1;
            }

            if (time<120 &&  HSP_2<HSP_p_2 && e<1)
            {

                MHSP_2 = HSP_2;
                VHSP_2 = second->V;
                e+=1;
            }
          //  if  (HSP_2>90000)  {HSP_2=HSP_1;}
            time+=h;
            Na  += dN*h;
            if (first->m_t>mpn)
            {



            first->tY += (first->V* sin(first->anY) + H11)/2*h;
            first->V   += (B_1.fdV(first->V, first->anY) + V1)/2*h;
            first->anY += (B_1.fdY(first->tY, first->V, first->anY)+Y1)/2*h;


            V1 = B_1.fdV(first->V, first->anY);
            Y1 = B_1.fdY(first->tY, first->V, first->anY);
            H11 = first->V* sin(first->anY);

            std::cout << zXY/1000  << std::endl;
            VX += h*B_1.dVX(velXY, Ott, Na);
            VY += h*B_1.dVY(velXY, Ott, Na);
            VZ += h*B_1.dVZ(velXY, Ott, Na);
            velXY = sqrt(VX*VX+VY*VY+VZ*VZ);
            trjXY = acos(VX/velXY);
            xXY += h*VX * cos(first->anY) / cos(Ott);
            yXY += h*VY * sin(first->anY) / sin(Ott);
            zXY += h*VZ;
            norXY = atan(xXY/(6371000+yXY));
            //


/*
 *          Рунге-Кутт4:
 *          double h1 = first->anY - Y1;
            double K1 = B_1.fdV(first->V, first->anY);
            double K2 = B_1.fdV(first->V+h1/2*K1, first->anY+h1/2);
            double K3 = B_1.fdV(first->V+h1/2*K2, first->anY+h1/2);
            double K4 = B_1.fdV(first->V+h1*K3, first->anY+h1);
            first->V += h1/6*(K1+K2*2+K3*2+K4);
*/

            }

            if (time >T_fuel[0])
            //if ((time>k1 && time<k2) || (time>k3 && time<k4))
            {



                second->tY += (second->V* sin(second->anY)+H22)/2*h;
                second->V  += (B_2.returndV(second->V, second->anY)+V2)/2*h; //return
                second->anY  += (B_2.returndY(second->tY, second->V, second->anY)+Y2)/2*h;  //return


                V2 = B_2.returndV(second->V, second->anY);
                Y2 = B_2.returndY(second->tY, second->V, second->anY);
                H22 = second->V* sin(second->anY);

            }
            else
            {
                second->tY += (second->V* sin(second->anY)+H22)/2*h;
                second->V  += (B_2.fdV(second->V, second->anY)+V2)/2*h;
                second->anY  += (B_2.fdY(second->tY, second->V, second->anY)+Y2)/2*h;

                V2 = B_2.fdV(second->V, second->anY);
                Y2 = B_2.fdY(second->tY, second->V, second->anY);
                H22 = second->V* sin(second->anY);
            }

        //qDebug()<<second->tY;
                xn.push_back(time);
                yu_1.push_back(HSP_1);
                yu_2.push_back(HSP_2);
                center_1.push_back(first->gl_c);
                center_2.push_back(second->gl_c);
                v_1.push_back(first->V);
                v_2.push_back(second->V);
                sinn.push_back(first->Ssumm);
                jinn.push_back(first->Isumm);
                jinn2.push_back(second->Isumm);
                CM.push_back(first->Ssumm/first->m_t);
                mass_1.push_back(first->m_t);
                mass_2.push_back(second->m_t);
                Long_1.push_back(first->tX/1000);
                Long_2.push_back(second->tX/1000);
                w.push_back(Wind2);
                H1.push_back(first->tY/1000);
                H2.push_back(second->tY/1000);
                angle.push_back(pitch*57.3);
                b1.push_back(HSP_1*Smid*CX_1);
                b2.push_back(HSP_2*Smid*CX_2);
                lin.push_back(Ix);
                ALI_1.push_back(alph_1.A());
                ALI_2.push_back(alph_2.A());
                //ALI.push_back(first->Peng_t/ (first->m_t*Atm_1.get_AOG()));
                res.push_back(second->Peng_t/(second->m_t*Atm_2.get_AOG()));
                TET_1.push_back(first->anY*57.3);
                TET_2.push_back(second->anY*57.3);
                be.push_back(bpr*57.3);
                pi.push_back(pitch*57.3);
                P1.push_back(first->Peng_t);
                P2.push_back(second->Peng_t);
                f1.push_back(first->focus);
                Lon.push_back(first->Peng_t/(first->m_t*Atm_1.get_AOG()));
                Lonre.push_back(second->Peng_t/(second->m_t*Atm_2.get_AOG()));
                pc2.push_back(second->Peng_control);
                cy2.push_back(CY_2);
                //std::cout << CY_2 << std::endl;
                dyn1.push_back(X_oneC);
                dyn2.push_back(X_twoC);

                //std::cout<<first->gl_c<<std::endl;
        amax = alph_1.A();
        count+=1;
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

void MainWindow::on_action_4_triggered()
{
        close();
}


void MainWindow::on_action_6_triggered()
{
    QVector<double> qu(0), x(0), iner(0);

    for (int i=0;i<=count;i++)

    {
    x.push_back(i*h);
    }
    ui->lineEdit  ->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_7->hide();

    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->label_4->hide();
    ui->label_5->hide();


    ui->label_2->hide();
    ui->label_3->hide();
    ui->label  ->hide();
    ui->label_8->hide();
    ui->label_9->hide();

    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, ALI_1);
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Угол атаки, град");
    ui->widget->xAxis->setRange(0, count*h);
    ui->widget->yAxis->setRange(-5, 30);
    ui->widget->replot();



    ui->label_10->setText("Угол траектории (1), град");
    ui->label_11->setText("Угол траектории (2), град");
}

void MainWindow::on_heightButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn,H1);
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Высота, км");
    ui->widget->xAxis->setRange(0, count*h+50);
    ui->widget->yAxis->setRange(0, 230);
    ui->widget->replot();

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(xn,H2);
    ui->widget->graph(1)->setPen(QPen(Qt::PenStyle::DashLine));
    ui->widget->replot();
}


void MainWindow::on_distanceButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn,Long_1);
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Дальность, км");
    ui->widget->xAxis->setRange(0, count*h);
    ui->widget->yAxis->setRange(0, 1600);
    ui->widget->replot();

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(xn,Long_2);
    ui->widget->graph(1)->setPen(QPen(Qt::PenStyle::DashLine));
    ui->widget->replot();
}


void MainWindow::on_trjButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(Long_1,H1);
    ui->widget->xAxis->setLabel("Дальность, км");
    ui->widget->yAxis->setLabel("Высота, км");
    ui->widget->xAxis->setRange(0, 1600);
    ui->widget->yAxis->setRange(0, 230);
    ui->widget->replot();

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(Long_2,H2);
    ui->widget->graph(1)->setPen(QPen(Qt::PenStyle::DashLine));
    ui->widget->replot();

}

void MainWindow::on_velButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn,v_1);
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Скорость, м/с");
    ui->widget->xAxis->setRange(0, count*h+10);
    ui->widget->yAxis->setRange(0, first->V+10);
    ui->widget->replot();

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(xn,v_2);
    ui->widget->graph(1)->setPen(QPen(Qt::PenStyle::DashLine));
    ui->widget->replot();
}

void MainWindow::on_alphaButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn, ALI_1);
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Угол атаки, град");
    ui->widget->xAxis->setRange(0, count*h+20);
    ui->widget->yAxis->setRange(-5, 91);
    ui->widget->replot();

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(xn, ALI_2);
    ui->widget->graph(1)->setPen(QPen(Qt::PenStyle::DashLine));
    ui->widget->replot();
}

void MainWindow::on_angleButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn, TET_1);
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Угол наклона траектории, град");
    ui->widget->xAxis->setRange(0, count*h+10);
    ui->widget->yAxis->setRange(-90, 90);
    ui->widget->replot();

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(xn, TET_2);
    ui->widget->graph(1)->setPen(QPen(Qt::PenStyle::DashLine));
    ui->widget->replot();
}

void MainWindow::on_vhButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn, yu_1);
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Максимальный скоростной напор, Па");
    ui->widget->xAxis->setRange(0, count*h);
    ui->widget->yAxis->setRange(0, *std::max_element(yu_2.begin(),yu_2.end()));
    ui->widget->replot();

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(xn, yu_2);
    ui->widget->graph(1)->setPen(QPen(Qt::PenStyle::DashLine));
    ui->widget->replot();
}

void MainWindow::on_centerButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn, center_1);
    ui->widget->graph(0)->setPen(QPen(Qt::green));
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Центр масс РН, м");
    ui->widget->xAxis->setRange(0, count*h);
    ui->widget->yAxis->setRange(0, *std::max_element(center_1.begin(),center_1.end()));
    ui->widget->replot();
}

void MainWindow::on_staticButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn, sinn);
    ui->widget->graph(0)->setPen(QPen(Qt::green));
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Стат момент X, кг м");
    ui->widget->xAxis->setRange(0, count*h);
    ui->widget->yAxis->setRange(0, Sx);
    ui->widget->replot();
}

void MainWindow::on_YZmomentButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn, jinn);
    ui->widget->graph(0)->setPen(QPen(Qt::green));
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Момент инерции Y/Z,   кг м2");
    ui->widget->xAxis->setRange(0, count*h);
    ui->widget->yAxis->setRange(0, Iz);
    ui->widget->replot();
}

void MainWindow::on_XmomentButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn, lin);
    ui->widget->graph(0)->setPen(QPen(Qt::green));
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Момент инерции X, кг м2");
    ui->widget->xAxis->setRange(0, count*h);
    ui->widget->yAxis->setRange(0, Ixmax);
    ui->widget->replot();
}

void MainWindow::on_massButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn, mass_1);
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Масса, кг");
    ui->widget->xAxis->setRange(0, count*h);
    ui->widget->yAxis->setRange(0, *std::max_element(mass_1.begin(),mass_1.end()));
    ui->widget->replot();

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(xn, mass_2);
    ui->widget->graph(1)->setPen(QPen(Qt::PenStyle::DashLine));
    ui->widget->replot();
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn, P1);
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Тяга ДУ, кН");
    ui->widget->xAxis->setRange(0, count*h);
    ui->widget->yAxis->setRange(0, *std::max_element(P1.begin(),P1.end()));
    ui->widget->replot();

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(xn, P2);
    ui->widget->graph(1)->setPen(QPen(Qt::PenStyle::DashLine));
    ui->widget->replot();
}


void MainWindow::on_pushButton_14_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn, Lon);
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Продольная перегрузка");
    ui->widget->xAxis->setRange(0, count*h);
    ui->widget->yAxis->setRange(0, 10);
    ui->widget->replot();

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(xn, Lonre);
    ui->widget->graph(1)->setPen(QPen(Qt::PenStyle::DashLine));
    ui->widget->replot();
}


void MainWindow::on_fokusButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xn, f1);
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Фокус, м");
    ui->widget->xAxis->setRange(0, count*h);
    ui->widget->yAxis->setRange(0, 5);
    ui->widget->replot();
}


void MainWindow::on_action_5_triggered()
{
    DC d;
    d.data_writing(xn, v_2, H2, w, mass_2, P2, pc2, yu_2, ALI_2, cy2, dyn1, dyn2, jinn2);

    QString k14=ui->lineEdit_14->text(); double P = k14.toDouble();
    QString k15=ui->lineEdit_15->text(); double I = k15.toDouble();
    QString k16=ui->lineEdit_16->text(); double D = k16.toDouble();
    d.get_T().clear();
    d.get_V().clear();
    d.data_calculating(P, I, D);

    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(d.get_T(), d.get_V());
    ui->widget->graph(0)->setPen(QPen(Qt::green));
    ui->widget->xAxis->setLabel("Время, с");
    ui->widget->yAxis->setLabel("Отклонение по тангажу, м");
    ui->widget->xAxis->setRange(405, 440);
    ui->widget->yAxis->setRange(-20, 20);
    ui->widget->replot();
}


void MainWindow::on_action_7_triggered()
{

}

