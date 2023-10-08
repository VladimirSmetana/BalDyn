#ifndef BLOCK_H
#define BLOCK_H

class block
{
public:
    double L;
    double m_t;
    double V;
    double Peng_t;
    double Peng_control;
    double alpha;
    double focus;
    double tY;
    double tX;
    double anY;
    double Ssumm;
    double Isumm;
    double gl_c;
    double I_reO, I_reC;
    double S_reO, S_reC;
    double S_dry[2];
    double I_dry[2];
};

#endif // BLOCK_H
