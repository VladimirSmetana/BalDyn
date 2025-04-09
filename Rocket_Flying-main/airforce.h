#include <QDebug>
#ifndef AIRFORCE_H
#define AIRFORCE_H

class Airforce {
private:
    double m_CX;
    double m_CY;
public:
    explicit Airforce(double Mah);
    double GetCX();
    double GetCY();
};

#endif // AIRFORCE_H


