#ifndef FLIGHTINIT_H
#define FLIGHTINIT_H

class FlightInit
{
public:
    FlightInit(double (&kalph_)[3], double (&kpeng_)[2]);
private:
    double kalph[3];
    double kpeng[2];
};

#endif // FLIGHTINIT_H
