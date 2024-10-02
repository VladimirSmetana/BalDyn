#include <QDebug>
#ifndef AIRFORCE_H
#define AIRFORCE_H
#include <cmath>
#define M_PI 3.14159265358979323846
class airforce
{
private:
    double CX;
    double CY;
public:
    explicit airforce(double Mah);
    double getCX();
    double getCY();
};

#endif // AIRFORCE_H


