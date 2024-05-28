#ifndef FOCUS_H
#define FOCUS_H
#include <cmath>
#define M_PI 3.14159265358979323846
class focus
{
private:
    double dXF;
    double KM;
    double XF;
public:
    double Focus (double Mah, double D, double Lgo, double wgo, double CIL, double CILCON);
};

#endif // FOCUS_H
