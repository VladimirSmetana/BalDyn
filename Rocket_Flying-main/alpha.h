#ifndef ALPHA_H
#define ALPHA_H
#include <cmath>

class alpha
{
private:
    double Vel, k1, k2, time, septime, def, tv1, tv2, ans, z, che;
public:
    alpha (double Vel, double k1, double k2, double time, double septime, int def, int tv1, int tv2);
    double A ();
};

#endif // ALPHA_H
