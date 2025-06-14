#ifndef FLIGHTTYPE_H
#define FLIGHTTYPE_H

struct FlightType
{
    double L;
    double m_t;
    double V;
    double Peng_t;
    double Peng_control;
    double alpha;
    double focus;
    double tY;
    double tX;
    double anY;
    double Sx;
    double Iyz;
    double Ix;
    double gl_c;
    double I_reO, I_reC;
    double S_reO, S_reC;
    double S_dry[2];
    double I_dry[2];
};

#endif // FLIGHTTYPE_H
