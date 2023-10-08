#ifndef PID_FILE_H
#define PID_FILE_H

class PID
{
private:
    float Kp, Ki, Kd;
    float Error;
    float h;
    float Goal;
    float Err;
    float prev_Err;
    float Summ_Err;
public:

    PID(float P, float I, float  D, float  hp, float  goal)
    {
        Kp = P; Ki = I, Kd = D;
        h = hp;
        Goal = goal;
        //Err = 0;
        prev_Err = 0;
        Summ_Err = 0;

    }
    float signal(float input)
    {
        float dErr;
        float P, I, D;

        Err = input - Goal;
        Summ_Err += Err * h;
        dErr = (Err - prev_Err) / h;
        prev_Err = Err;

        P = Err * Kp;
        I = Summ_Err * Ki;
        D = dErr * Kd;

        return P + I + D;
    }
    ~PID() {};
};

#endif // PID_FILE_H
