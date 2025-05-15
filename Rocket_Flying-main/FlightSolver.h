#ifndef FLIGHTSOLVER_H
#define FLIGHTSOLVER_H

#include "FlightInit.h"
#include <cmath>

#include <QVector>

#include "aerodynamics/Airforce.h"

#include "atmosphere/atmosphere.h"
#include "eastwind.h"
#include "alpha.h"
#include <QFile>
#include "DataVector.h"

class FlightSolver : public FlightInit {

private:
    double Na=0.1, Mah_1, Mah_2,  time = 0;
    int e=0;
    int uj=0;
    int ten=0;
    double V1=0, Y1=0, H11=0, X1=0;
    double V2=0, Y2=0, H22=0, X2=0;
    double xXY = 0, yXY = 0,  VX = 0.3, VY = 0.3, velXY = 0.3, trjXY = M_PI/2, norXY = 0;
    double zXY = 0, VZ  = 0.3;

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

    double Ott;
    double CX_1, CY_1;
    double CX_2, CY_2;
    double dN;

    double Imp_t, CF;
    double pitch_angle;
    double bpr;
    double HSP_1, HSP_p_1, VHSP_1;
    double HSP_2, HSP_p_2;
    double H_1;
    double deo, dec;
    double X_oneC;
    double X_twoC;

    std::shared_ptr<Dataset> m_insertion_data = std::make_shared<Dataset>();
    std::shared_ptr<Dataset> m_recovery_data = std::make_shared<Dataset>();

    public:


    FlightSolver(double (&kalph_)[3],
                 double (&kpeng_)[2]);
    ~FlightSolver();

    double kalph[3];
    double kpeng[2];

    double dep;
    double Ott_1, Ott_2 ;
    double MHSP_1, MHSP_2, VHSP_2;
    double MaxTime;

    double amax;

    double mass_function(double time);
    double thrust_function(double time);
    void pitch_calculations();

    std::shared_ptr<Dataset> GetInsertionData();
    std::shared_ptr<Dataset> GetRecoveryData();

    QFile file1;

};

#endif // FLIGHTSOLVER_H
