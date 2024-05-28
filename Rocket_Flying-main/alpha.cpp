#include "alpha.h"

alpha::alpha (double Vel, double k1, double k2, double time, double septime, int def, int tv1, int tv2)

    :Vel(Vel), k1(k1), k2(k2), time(time), septime(septime), def(def), tv1(tv2)
{}

double alpha::A()
{
    if (Vel>50 && Vel<270 && time <= septime)
    {
        z=M_PI*(Vel-50);
        che=(Vel-50)+0.25*(270-Vel);
        ans = k1*pow(sin(z/che),2);
    }
    else
        if (time >= septime)
        {

            if (def == 0) ans = k2 * (time - septime);
            if (def == 180) {
                if (time - septime<60)
                {
                    z=M_PI*(time - septime);
                    che=(time - septime)+0.25*(septime+60-time);
                    ans = 90*pow(sin(z/che),2);
                    //ans = 3 * (time - septime);
                }
                if (time>tv1 && time<tv2)
                {
                    z=M_PI*(time - tv1);
                    che=(time - tv1)+0.25*(tv1+(tv2-tv1)-time);
                    ans = 0.25*pow(sin(z/che),2); }

            } ;

        }
        else
            ans = 0;

    return ans;
}
