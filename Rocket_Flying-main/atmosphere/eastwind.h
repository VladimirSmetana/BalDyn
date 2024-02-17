#ifndef EASTWIND_H
#define EASTWIND_H
#include <cmath>

#endif // EASTWIND_H



class eastwind
{
private:
double H;
    double W;
    double HW[17]={0.1 , 6, 12 , 18 , 24 , 30 , 36, 42 , 48, 54, 60, 66, 72, 78, 84, 90, 94};
    double WW[17]={1.9 , 8, 15 , 18 , 24 , 12 , 10, 8  ,  6,  5,  4,  3,  3,  2,  2,  1,  0.1};
public:
eastwind (double H);
    double WSol ();
};


