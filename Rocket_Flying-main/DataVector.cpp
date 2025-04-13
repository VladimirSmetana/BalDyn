#include "DataVector.h"
#include "qtypes.h"

bool Dataset::saveToCSV(const fs::path& filename) const {
    QFile file(QString::fromStdString(filename.string()));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for writing:" << QString::fromStdString(filename.string());
        return false;
    }

    QTextStream out(&file);

    // Записываем заголовок
    out << "Time,Altitude,X_Moment,Attack_Angle,Trajectory_Angle,Center_of_Mass,"
        << "Dynamic_Pressure,Mass,Stability_Margin,Thrust,Longitude,Velocity,"
        << "Wind_Velocity,G_Force,YZ_Moment,Static_Moment,Engine_Angle,"
        << "Pitch_Angle,Focus,Control_Thrust,Drug_Coefficient,Rocket_Length,Lift_Force\n";

    // Проверяем размер векторов и записываем данные
    qsizetype numRows = time.size();
    if (numRows == 0) {
        qWarning() << "Time vector is empty. No data to save.";
        return false;
    }

    for (qsizetype i = 0; i < numRows; ++i) {
        out << time[i] << ',';

        if (altitude.size() == numRows) out << altitude[i] << ',';
        else out << "N/A,"; // или любое другое значение по умолчанию

        if (x_moment.size() == numRows) out << x_moment[i] << ',';
        else out << "N/A,";

        if (attack_angle.size() == numRows) out << attack_angle[i] << ',';
        else out << "N/A,";

        if (trajectory_angle.size() == numRows) out << trajectory_angle[i] << ',';
        else out << "N/A,";

        if (center_of_mass.size() == numRows) out << center_of_mass[i] << ',';
        else out << "N/A,";

        if (dynamic_pressure.size() == numRows) out << dynamic_pressure[i] << ',';
        else out << "N/A,";

        if (mass.size() == numRows) out << mass[i] << ',';
        else out << "N/A,";

        if (stability_margin.size() == numRows) out << stability_margin[i] << ',';
        else out << "N/A,";

        if (thrust.size() == numRows) out << thrust[i] << ',';
        else out << "N/A,";

        if (longitude.size() == numRows) out << longitude[i] << ',';
        else out << "N/A,";

        if (velocity.size() == numRows) out << velocity[i] << ',';
        else out << "N/A,";

        if (wind_velocity.size() == numRows) out << wind_velocity[i] << ',';
        else out << "N/A,";

        if (g_force.size() == numRows) out << g_force[i] << ',';
        else out << "N/A,";

        if (yz_moment.size() == numRows) out << yz_moment[i] << ',';
        else out << "N/A,";
        if (static_moment.size() == numRows) out << static_moment[i] << ',';
        else out << "N/A,";

        if (engine_angle.size() == numRows) out << engine_angle[i] << ',';
        else out << "N/A,";

        if (pitch_angle.size() == numRows) out << pitch_angle[i] << ',';
        else out << "N/A,";

        if (focus.size() == numRows) out << focus[i] << ',';
        else out << "N/A,";

        if (control_thrust.size() == numRows) out << control_thrust[i] << ',';
        else out << "N/A,";

        if (drug_coefficient.size() == numRows) out << drug_coefficient[i] << ',';
        else out << "N/A,";

        if (rocket_length.size() == numRows) out << rocket_length[i] << ',';
        else out << "N/A,";

        if (lift_force.size() == numRows) out << lift_force[i];
        else out << "N/A";
        out << '\n';
    }

    file.close();
    return true;
}
