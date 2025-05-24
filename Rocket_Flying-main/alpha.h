#ifndef ALPHA_H
#define ALPHA_H


class alpha
{
private:
    double k1, k2, septime, IsRichOrbit;
public:
    alpha (double k1, double k2, double septime, bool IsRichOrbit);

    double calculate_alpha (double velocity,  double time);
};

#endif // ALPHA_H
