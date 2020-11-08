#ifndef SGENERALDATA_H
#define SGENERALDATA_H

class SGeneralData
{
public:
    SGeneralData();    
    ~SGeneralData();

    // Длина
    // Leight
    // meters
    double leight;

    // Ширина, м
    // Beam
    // meters
    double deam;

    // Осадка, м
    // Depths
    // meters
    double depths;

    // Высота борта, м
    // Freeboard
    // meters
    double height;

    // Коэффициент общей полноты
    // Block Coefficient
    //
    double cb;

    // Коэффициент развитости надстроек
    // Superstructure Development Coefficient
    //
    double csd;

    // Поперечная метацентрическая высота (МЦВ), м
    // Metacentric Height
    // meters
    double gm;

    // Давление ветра, Па
    // Wind Pressure
    // pascals
    double wind_pressure = 1200;

    // Максимально допустимый угол крена от действия ветра, градусы
    // Wind Heel Angle
    // degrees
    double wha = 15;

    // Заданное значение максимальной аппликаты огибающей силуэта, м
    // SEFm - Silhouette Envelope Function max
    // meters
    double sef_max;

    // Относительная абсцисса максимума огибающей силуэта (доли длины)
    // ROSEFm - SEFm relative ordinate
    // proportion
    double rosef_max;

    // Относительная аппликата огибающей силуэта на кормовом перпендикуляре (доля SEFm)
    // APRA - Aft Perpendicular Relative Applicate
    // proportion
    double apra;

};

#endif // SGENERALDATA_H
