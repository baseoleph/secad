#include "sgeneraldata.h"

SGeneralData::SGeneralData()
{
    wind_pressure = WIND_PRESSURE;
    wha = WHA;
}

SGeneralData::~SGeneralData()
{

}

void SGeneralData::calcData()
{
   visibility_zone = calcVisibilityZone(length);
   freeboard = calcFreeboard(depths, height);
   gsl = calcGoldenSecionByLength(length);
   gsh = calcGoldenSecionByHeight(length, freeboard);
   sef_ma = calcSEFMA(depths, sef_mea);
   sef_mo = calcSEFMO(length, sef_mro);
   sef_apa = calcSEFAPA(sef_ma, sef_apra);
   sef_coef = calcSEFCoef(length, depths, sef_ma, sef_mo, sef_apa);
}

double SGeneralData::calcVisibilityZone(const double length)
{
    if (length < 45) return 0;
    else if (length >= 45 and length <= 250) return 2*length;
    else return 500;
}

double SGeneralData::calcFreeboard(const double depths, const double height)
{
    return height - depths;
}

d_vector SGeneralData::calcGoldenSecionByLength(const double length)
{
    d_vector gsl = {1, 0.618};
    double gsl_next = gsl[0] - gsl[1];
    double criterion = 0.1/length;
    while (gsl_next >= criterion)
    {
        gsl.push_back(gsl_next);
        gsl_next = gsl[gsl.size() - 2] - gsl[gsl.size() - 1];
    }
    qDebug() << gsl;
    return gsl;
}

d_vector SGeneralData::calcGoldenSecionByHeight(const double length, double freeboard)
{
    d_vector gsh = {0.618, 1};
    double gsh_next = gsh[0] + gsh[1];
    double criterion = freeboard/length;
    while (gsh_next <= criterion)
    {
        gsh.push_back(gsh_next);
        gsh_next = gsh[gsh.size() - 2] + gsh[gsh.size() - 1];
    }

    return gsh;
}

double SGeneralData::calcSEFMA(const double depths, const double sef_mea)
{
    return sef_mea - depths;
}

double SGeneralData::calcSEFMO(const double length, const double sef_mro)
{
    return sef_mro * length;
}

double SGeneralData::calcSEFAPA(const double sef_ma, const double sef_apra)
{
    return sef_ma * sef_apra;
}

d_vector SGeneralData::calcSEFCoef(const double length, const double depths, const double sef_ma, const double sef_mo, const double sef_apa)
{
    double t = sef_ma;
    double q = sef_mo;
    double p = sef_apa;
    d_vector sef_coef(4);
    sef_coef[0] = calcA0(depths, p);
    sef_coef[2] = calcA2(length, t, q, p);
    sef_coef[3] = calcA3(sef_coef[2], length, q, p);
    sef_coef[1] = calcA1(q, sef_coef[2], sef_coef[3]);
    return sef_coef;
}

double SGeneralData::calcA0(const double depths, const double p)
{
    return p + depths;
}

double SGeneralData::calcA1(const double q, const double a2, const double a3)
{
    return -3 * a3 * pow(q, 2) - 2 * a2 * q;
}

double SGeneralData::calcA2(const double length, const double t, const double q, const double p)
{
    double numerator = t * pow(length, 3) - 3 * t * length * pow(q, 2) - 2 * pow(q, 3) * p
                        - p * pow(length, 3) + 3 * p * length * pow(q, 2);
    double denominator = 2 * pow(q, 3) * pow(length, 2) - pow(q, 4) * length - pow(q, 2) * pow(length, 3);
    return numerator/denominator;
}

double SGeneralData::calcA3(const double a2, const double length, const double q, const double p)
{
    double numerator = 2 * a2 * q * length - a2 * pow(length, 2) - p;
    double denominator = pow(length, 3) - 3 * length * pow(q, 2);
    return numerator/denominator;
}
