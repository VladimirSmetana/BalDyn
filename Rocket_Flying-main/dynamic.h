
#ifndef DYNAMIC_H
#define DYNAMIC_H




ifstream Aero;
ifstream Dow;
ifstream Cin;
ifstream CEqual;
ifstream Alpha;

Aero.open("C:\\Users\\Владимир Сметана\\Desktop\\УЧЕБНЫЙ АРХИВ\\12 S\\PID-reg\\Start data\\reAero.txt");
Dow.open("C:\\Users\\Владимир Сметана\\Desktop\\УЧЕБНЫЙ АРХИВ\\12 S\\PID-reg\\Start data\\reDow.txt");
Cin.open("C:\\Users\\Владимир Сметана\\Desktop\\УЧЕБНЫЙ АРХИВ\\12 S\\PID-reg\\Start data\\reCin.txt");
CEqual.open("C:\\Users\\Владимир Сметана\\Desktop\\УЧЕБНЫЙ АРХИВ\\12 S\\PID-reg\\Start data\\reCEqual.txt");
Alpha.open("C:\\Users\\Владимир Сметана\\Desktop\\УЧЕБНЫЙ АРХИВ\\12 S\\PID-reg\\Start data\\Alpha.txt");

float kp, ki, kd, goal, h=0.5;
float Time ;
int N = Convert::ToInt64(domainUpDown2->Text) * 2;
int Mod = Convert::ToDouble(domainUpDown1->Text);
float KK, KS[5], KdS[5], KddS[5], Summ_KS[5];

float *Cvv = new float [N];
//int size = sizeof(Cvv)*N;
float* Cww = new float [N];
float* Cvw = new float [N];
float* Cwv = new float [N];
float* Cvb = new float [N];
float* Cwb = new float [N];
float* Wind = new float[N];
float** dow; dow = new float* [N];
float** Cws; Cws = new float* [N];
float** Cvs; Cvs = new float* [N];
for (int j = 0; j < 5; j++)
{
    dow[j] = new float[N];
    Cws[j] = new float[N];
    Cvs[j] = new float[N];
}
float* Csb = new float[N];
float* Qv = new float[N];
float* Qs = new float[N];
float* Qw = new float[N];
float* Vel = new float[N];
float* Alp = new float[N];
float* newAlp = new float[N];

float s[5];
float ds[5];
float dds[5];


for (int i = 0; i < 5; i++)
{
    s[i] = 0;
    ds[i] = 0;
    dds[i] = 0;
}

float double_W[5];

float bmax, bmin;
float
    w = 0,
    dw = 0,
    ddw = 0,
    v = 0,
    dv = 0,
    u = 0,
    y = 0,
    du = 0,
    ddu = 0,
    uc = 0,
    Summ_Cws=0,
    Summ_Cvs=0,
    Summ_S=0;

float A0;
float AU;
float A1;
float N0;
float N1;
chart1->Series[0]->Points->Clear();
chart2->Series[0]->Points->Clear();
chart2->Series[1]->Points->Clear();
chart3->Series[0]->Points->Clear();
chart4->Series[0]->Points->Clear();
chart5->Series[0]->Points->Clear();
//chart6->Series[0]->Points->Clear();
listBox1->Items->Clear();

kp = Convert::ToDouble(textBox1->Text);
ki = Convert::ToDouble(textBox2->Text);
kd = Convert::ToDouble(textBox3->Text);

goal = 0;

PID pid(kp, ki, kd, 0.5, goal);
bmax = 5 / 57.3;

//EngineController controller(0.1);

for (int i = 0; i < N; i++)
{
    // Чтение файла с данными аэродинамики
    Aero >> Wind[i];
    Aero >> Qv[i];
    Aero >> Qs[i];
    Aero >> Qw[i];
    Aero >> Vel[i];
    // Чтение файла с частотами
    Dow >> dow[0][i];
    Dow >> dow[1][i];
    Dow >> dow[2][i];
    Dow >> dow[3][i];
    Dow >> dow[4][i];
    // Чтения файла с колебательными коэффициентами
    Cin >> Cws[0][i];
    Cin >> Cvs[0][i];
    Cin >> Cws[1][i];
    Cin >> Cvs[1][i];
    Cin >> Cws[2][i];
    Cin >> Cvs[2][i];
    Cin >> Cws[3][i];
    Cin >> Cvs[3][i];
    Cin >> Cws[4][i];
    Cin >> Cvs[4][i];
    // Чтение файлов с коэффициентами движения
    CEqual >> Cvb[i];
    CEqual >> Cvw[i];
    CEqual >> Cww[i];
    CEqual >> Cvv[i];
    CEqual >> Cwv[i];
    CEqual >> Cwb[i];
    CEqual >> Csb[i];
    // Чтение файла с углами атаки
    Alpha >> Alp[i];
    //Alp[i] = 0;
    newAlp[i] = w-(v-Wind[i])/ Vel[i];

    uc = pid.signal(w);
    if (uc >= bmax) uc = bmax;
    if (uc <=-bmax) uc =-bmax;

    Summ_Cws = Cws[0][i]*s[0] + Cws[1][i]*s[1] + Cws[2][i]*s[2] + Cws[3][i]*s[3] + Cws[4][i]*s[4];
    Summ_Cvs = Cvs[0][i]*s[0] + Cvs[1][i]*s[1] + Cvs[2][i]*s[2] + Cvs[3][i]*s[3] + Cvs[4][i]*s[4];
    AU = Qs[i] * (w - (v - Wind[i]) / Vel[i]);

    for (int j = 0; j < 5; j++)
    {
        double_W[j] = dow[j][i];
    }

    KS[0] = 0;   KS[1] = 0;   KS[2] = 0;         KS  [3] = 0;      KS[4]  = 0;
    KdS[0] = 0;  KdS[1] = 0;  KdS[2] = 0;        KdS [3] = 0;      KdS[4] = 0;
    KddS[0] = 0; KddS[1] = 0; KddS[2] = 1.5;      KddS[3] =5.5;    KddS[4]= 13;

    for (int j = 0; j < 5; j++)
    {
        Summ_KS[j] = KS[j] * s[j] + KdS[j] * ds[j];
        Summ_S += s[j];
    }

    dv = Cvv[i] * Wind[i] - Cvw[i] * w + Cvb[i] * uc - Summ_Cvs; //
    ddw = Cwv[i] * Wind[i] - Cww[i] * w - Cwv[i] * v - Cwb[i] * uc -Summ_Cws; //

    if (checkBox1->CheckState == CheckState::Checked)
    {
        dds[0] = -0.5 * sqrt(double_W[0]) / 3.14 * ds[0] - double_W[0] * s[0] + Csb[i] * uc - Summ_KS[0];
        dds[1] = -0.5 * sqrt(double_W[1]) / 3.14 * ds[1] - double_W[1] * s[1] - Csb[i] * uc - Summ_KS[1];
        dds[2] = -0.5 * sqrt(double_W[2]) / 3.14 * ds[2] - double_W[2] * s[2] + Csb[i] * uc - Summ_KS[2];
        dds[3] = -0.5 * sqrt(double_W[3]) / 3.14 * ds[3] - double_W[3] * s[3] - Csb[i] * uc - Summ_KS[3];
        dds[4] = -0.5 * sqrt(double_W[4]) / 3.14 * ds[4] - double_W[4] * s[4] + Csb[i] * uc - Summ_KS[4];
        dv     -= Qv[i] * s[0];
        ddw    -= Qw[i] * s[0];
        dds[0] -= AU;
    }

    //Интегрирование
    v += h * dv;
    dw += h * ddw;
    w += h * dw;
    du += h * ddu;
    u += h * du;
    y += h * v;

    for (int j = 0; j < Mod; j++)
    {
        ds[j] += h * dds[j] * pow(1+KddS[j],-1);
        s[j] += h * ds[j] * pow(1 + KdS[j], -1);
        s[j] = s[j] * pow(1 + KS[j], -1);
    }
    chart5->Series[0]->Points->AddXY(Time, Summ_S*1000);
    chart6->Series[0]->Points->AddXY(Time, newAlp[i]*57.3);
    //Summ_S * 1000

    // FrontEnd

    //listBox1->Items->Add(Time+"  "+ newAlp[i] * 57.3);
    textBox4->Text += Convert::ToString(newAlp[i] * 57.3)+" "+ Convert::ToString(Time) + "\n";

    Time += 0.5;
    chart1->Series[0]->Points->AddXY(Time, w*57.3);

    chart2->Series[0]->Points->AddXY(Time, Vel[i]+v);
    chart2->Series[1]->Points->AddXY(Time, Vel[i]);
    chart3->Series[0]->Points->AddXY(Time, y);
    //chart3->Series[0]->Points->AddXY(Time, uc*57.3);
    //chart4->Series[0]->Points->AddXY(Time, Wind[i]);

    if (abs(w * 57.3) > 5) { break; }
}
// 	number = System::Convert::ToString(Time);
//  textBox5->Text = number;
// Удаление массивов
delete [] Cvb;
delete [] Cvw;
delete [] Cvv;
delete [] Cww;
delete [] Cwv;
delete [] Cwb;
delete [] Csb;
delete [] Wind;
for (int i = 0; i < 5; i++)
{
    delete[] dow[i];
    delete[] Cws[i];
    delete[] Cvs[i];
}
delete [] Qv;
delete [] Qs;
delete [] Qw;
delete [] Vel;
delete [] Alp;

// Удаление потоков
Aero.close();
Dow.close();
Cin.close();
CEqual.close();
Alpha.close();
}








#endif // DYNAMIC_H
