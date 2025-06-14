#include "element.h"

#include <cmath>

Element::Element(double start_point,
                 double end_point,
                 double mass,
                 double diameter)

: m_start_point (start_point)
, m_end_point   (end_point)
, m_mass        (mass)
, m_diameter    (diameter) {

    m_iz = fun_Iz(m_start_point, m_end_point, m_mass, m_diameter);
    m_ix = fun_Ix(m_mass, m_diameter);
    m_sx = fun_Sx(m_start_point, m_end_point, m_mass);
}

void Element::ChangeMass(double delta_mass) {
    m_mass -= delta_mass;
    m_iz = fun_Iz(m_start_point, m_end_point, m_mass, m_diameter);
    m_ix = fun_Ix(m_mass, m_diameter);
    m_sx = fun_Sx(m_start_point, m_end_point, m_mass);
}

void Element::ChangeLevel(double delta_level) {
    m_iz = fun_Iz(m_start_point + delta_level, m_end_point, m_mass, m_diameter);
    m_sx = fun_Sx(m_start_point + delta_level, m_end_point, m_mass);
}

double Element::fun_Iz(double start_point,
                       double end_point,
                       double mass,
                       double diameter) {
    return 0.25 * mass * ( pow(start_point+end_point, 2)
           + 0.333 * pow(start_point - end_point, 2)+pow((diameter/2),2) );
}

double Element::fun_Ix(double mass,
                       double diameter) {
    return mass * pow(diameter/2, 2);
}

double Element::fun_Sx(double start_point,
                       double end_point,
                       double mass) {
    return 0.5 * mass * (start_point + end_point);
}

double Element::GetMass() {
    return m_mass;
}
double Element::GetIz  () {
    return m_iz;
}
double Element::GetIx  () {
    return m_ix;
}
double Element::GetSx  () {
    return m_sx;
}
