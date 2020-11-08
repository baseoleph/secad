#ifndef SGENERALDATA_H
#define SGENERALDATA_H

#include <iomanip>
#include <vector>

typedef std::vector<double> d_vector;

class SGeneralData
{
public:
    SGeneralData();    
    ~SGeneralData();

    /* <const> (в процессе работы можно изменить) */

    // Давление ветра, Па
    // Wind Pressure
    // pascals
    double wind_pressure = 1200;

    // Максимально допустимый угол крена от действия ветра, градусы
    // Wind Heel Angle
    // degrees
    double wha = 15;

    /* </const> */

    // Длина
    // Length
    // meters
    double length;

    // Ширина, м
    // Beam
    // meters
    double deam;

    // Осадка, м
    // Depths
    // meters
    double depths;

    // Высота борта, м
    // Height
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

    // Заданное значение максимальной аппликаты огибающей силуэта, м
    // SEF - Silhouette Envelope Function
    // MEA - Maximum Entering Applicate
    // meters
    double sef_mea;

    // Относительная абсцисса максимума огибающей силуэта (доли длины)
    // MRO - SEF Maxumum Relative Ordinate
    // proportion
    double sef_mro;

    // Относительная аппликата огибающей силуэта на кормовом перпендикуляре (доля SEFm)
    // APRA - Aft Perpendicular Relative Applicate
    // proportion
    double sef_apra;

    // Максимально допустимая длина мертвой зоны
    // Visibility Zone Length
    // meters
    double visibility_zone;

    // Надводный борт
    // Freeboard
    // meters
    double freeboard;

    double sef_ma;
    double sef_mo;
    double sef_apa;

    // Золотое сечение по длине
    // Golden Section by Leight
    // proportions
    d_vector gsl;

    // Золотое сечение по высоте
    // Golden Section by Height
    // proportions
    d_vector gsh;


    // Коэффициенты в фукнции полинома
    // SEF coefficients
    // coefficients
    d_vector sef_coef;
};

#endif // SGENERALDATA_H
