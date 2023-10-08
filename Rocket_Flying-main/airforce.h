#include <QDebug>
#ifndef AIRFORCE_H
#define AIRFORCE_H
#include <cmath>

class airforce
{
private:
    double CX;
    double CY;
public:
    airforce(double Mah);
    double getCX();
    double getCY();
};

#endif // AIRFORCE_H


