#include <QDebug>
#ifndef AIRFORCE_H
#define AIRFORCE_H

class Airforce {
public:
    explicit Airforce(double Mah);
    double GetCX();
    double GetCY();
private:
    double m_CX;
    double m_CY;
};

#endif // AIRFORCE_H


