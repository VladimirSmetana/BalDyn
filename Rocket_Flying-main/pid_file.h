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
        double Err = input - Goal;
        double P = Err * Kp;
        Summ_Err += Err * h;
        double I = Summ_Err * Ki;
        double D = (Err - prev_Err) / h * Kd;
        prev_Err = Err;

        return P + I + D;
    }
    ~PID() {};
};

#endif // PID_FILE_H
