#include "alpha.h"
#include <cmath>
#include <QDebug>

alpha::alpha (double k1, double k2, double septime, bool IsRichOrbit)
    : k1(k1), k2(k2), septime(septime), IsRichOrbit(IsRichOrbit) {}

double alpha::calculate_alpha(double velocity, double time) {
    double ans = 0;
    double che = 0;
    double z   = 0;

    if ((velocity > 50 && velocity < 270 && time <= septime)) {
        z = M_PI * (velocity - 50);
        che = (velocity - 50) + 0.25 * (270 - velocity);
        ans = k1 * pow(sin(z / che), 2);
    } else if (time >= septime) {
        if (!IsRichOrbit) {
            ans = k2 * (time - septime);
        } else {
            if (time - septime < 60) {
                z = M_PI * (time - septime);
                che = (time - septime) + 0.25 * (septime + 60 - time);
                ans = 90 * pow(sin(z / che), 2);
            }
        }
    }
    return ans;
}

