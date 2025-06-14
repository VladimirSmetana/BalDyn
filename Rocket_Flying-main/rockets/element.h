#ifndef ELEMENT_H
#define ELEMENT_H

class Element {
public:
    Element(double& start_point,
            double& end_point,
            double& mass,
            double& diameter);

    double GetMass();
    double GetIz  ();
    double GetIx  ();
    double GetSx  ();

    void ChangeMass(double&  delta_mass);
    void ChangeLevel(double& delta_level);

private:

    double fun_Iz(double& start_point,
                  double& end_point,
                  double& mass,
                  double& diameter);

    double fun_Ix(double& mass,
                  double& diameter);

    double fun_Sx(double& start_point,
                  double& end_point,
                  double& mass);

    double m_start_point;
    double m_end_point;
    double m_mass;
    double m_diameter;
    double m_iz;
    double m_ix;
    double m_sx;
};

#endif // ELEMENT_H
