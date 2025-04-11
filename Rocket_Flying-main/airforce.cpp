#include "Airforce.h"

    Airforce::Airforce (double Mah) {
        if ((Mah > 0) && (Mah <= 0.25))   m_CY = 2.8;
        if ((Mah > 0.25) && (Mah <= 1.1)) m_CY = 2.8+0.447 * (Mah-0.25);
        if ((Mah > 1.1) && (Mah <= 1.6))  m_CY = 3.18 - 0.660 * (Mah - 1.1);
        if ((Mah > 1.6) && (Mah <= 3.6))  m_CY = 2.85 + 0.350 * (Mah - 1.6);
        if (Mah > 3.6)                    m_CY = 12.78/Mah;

        if (Mah <= 0.8)                   m_CX = 0.29;
        if (Mah > 0.8 && Mah < 1.068)     m_CX = Mah-0.51;
        if (Mah >= 1.068)                 m_CX = 0.597/Mah;
        if (m_CX > 1)                     m_CX = 1;
    }

    double Airforce::GetCX() {
        return m_CX;
    }

    double Airforce::GetCY() {
        return m_CY;
    }
