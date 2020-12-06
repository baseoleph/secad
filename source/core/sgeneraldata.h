#ifndef SGENERALDATA_H
#define SGENERALDATA_H

#include <iomanip>
#include <vector>
#include <QString>
#include <math.h>
#include "sm_algorithms.h"
#include "sconstants.h"
#include <QDebug>

typedef std::vector<double> d_vector;

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
    double calcSEFMA(const double freeboard, const double sef_mea);
    double calcSEFMO(const double length, const double sef_mro);
    double calcSEFAPA(const double sef_ma, const double sef_apra);

    d_vector calcSEFCoef(const double length, const double draft,
                         const double sef_ma, const double sef_mo, const double sef_apa);
    double calcC0(const double draft, const double t);
    double calcC1(const double q, const double a2, const double a3);
    double calcC2(const double length, const double t, const double q, const double p);
    double calcC3(const double a2, const double length, const double q, const double p);

    // Имя проекта
    QString project_name;

    /* <const> (в процессе работы можно изменить) */

    // Давление ветра, Па
    // Wind Pressure
    // pascals
    double p_w = NOTHING_VALUE;

    // Максимально допустимый угол крена от действия ветра, градусы
    // Wind Heel Angle
    // degrees
    double theta = NOTHING_VALUE;

    /* </const> */

    /* Вводимые переменные */

    // Длина
    // Length
    // metres
    double L = NOTHING_VALUE;

    // Ширина, м
    // Beam
    // metres
    double B = NOTHING_VALUE;

    // Осадка, м
    // Draft
    // metres
    double T = NOTHING_VALUE;

    // Высота борта, м
    // Height
    // metres
    double H = NOTHING_VALUE;

    // Коэффициент общей полноты
    // Block Coefficient
    //
    double delta = NOTHING_VALUE;

    // Коэффициент развитости надстроек
    // Superstructure Development Coefficient
    //
    double k_DS = NOTHING_VALUE;

    // Поперечная метацентрическая высота (МЦВ), м
    // Metacentric Height
    // metres
    double GM = NOTHING_VALUE;

    // Заданное значение максимальной аппликаты огибающей силуэта, м
    // SEF - Silhouette Envelope Function
    // MEA - Maximum Entering Applicate
    // metres
    double t_ = NOTHING_VALUE;

    // Относительная абсцисса максимума огибающей силуэта (доли длины)
    // MRO - SEF Maxumum Relative Ordinate
    // proportion
    double q_ = NOTHING_VALUE;

    // Относительная аппликата огибающей силуэта на кормовом перпендикуляре (доля SEFm)
    // APRA - Aft Perpendicular Relative Applicate
    // proportion
    double p_ = NOTHING_VALUE;

    /* Расчетные переменные */

    // Максимально допустимая длина мертвой зоны
    // Visibility Zone Length
    // metres
    double L_V_max = NOTHING_VALUE;

    // Надводный борт
    // Freeboard
    // metres
    double FB = NOTHING_VALUE;

    // Аппликата максимума огибающей
    // MA - SEF Maximum Applicate
    // metres
    double t = NOTHING_VALUE;

    // Абсцисса максимума огибающей
    // MO - SEF Maximum Ordinate
    // metres
    double q = NOTHING_VALUE;

    // Аппликата огибающей на кормовом перпендикуляре
    // APA - SEF Aft Perpendicular Applicate
    // metres
    double p = NOTHING_VALUE;

    // Золотое сечение по длине
    // Golden Section by Length
    // proportions
    d_vector GS_L;

    // Золотое сечение по высоте
    // Golden Section by Height
    // proportions
    d_vector GS_H;


    // Коэффициенты в фукнции полинома
    // SEF coefficients
    // coefficients
    d_vector cn;
};

#endif // SGENERALDATA_H
