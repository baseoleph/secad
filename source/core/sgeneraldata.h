#ifndef SGENERALDATA_H
#define SGENERALDATA_H

#define WIND_PRESSURE 1200
#define WHA 15

#include <iomanip>
#include <vector>
#include <string>
#include <math.h>

#include <QDebug>

typedef std::vector<double> d_vector;
typedef std::string string;

class SGeneralData
{
public:
    SGeneralData();    
    ~SGeneralData();

    void calcData();
    double calcVisibilityZone(const double length);
    double calcFreeboard(const double draft, const double height);
    d_vector calcGoldenSecionByLength(const double length);
    d_vector calcGoldenSecionByHeight(const double sef_ma);
    double calcSEFMA(const double draft, const double sef_mea);
    double calcSEFMO(const double length, const double sef_mro);
    double calcSEFAPA(const double sef_ma, const double sef_apra);

    d_vector calcSEFCoef(const double length, const double draft,
                         const double sef_ma, const double sef_mo, const double sef_apa);
    double calcC0(const double draft, const double t);
    double calcC1(const double q, const double a2, const double a3);
    double calcC2(const double length, const double t, const double q, const double p);
    double calcC3(const double a2, const double length, const double q, const double p);

    // Имя проекта
    string project_name;

    /* <const> (в процессе работы можно изменить) */

    // Давление ветра, Па
    // Wind Pressure
    // pascals
    double wind_pressure;

    // Максимально допустимый угол крена от действия ветра, градусы
    // Wind Heel Angle
    // degrees
    double wha;

    /* </const> */

    /* Вводимые переменные */

    // Длина
    // Length
    // meters
    double length;

    // Ширина, м
    // Beam
    // meters
    double beam;

    // Осадка, м
    // Draft
    // meters
    double draft;

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

    /* Расчетные переменные */

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
    // Golden Section by Length
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
