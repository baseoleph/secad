// Ship Exterior CAD
// Copyright (C) 2020 baseoleph@gmail.com,
//					  nepryaho@gmail.com

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "sgeneraldata.h"

SGeneralData::SGeneralData()
{
    p_w = WIND_PRESSURE;
    theta = WHA;
}

SGeneralData::~SGeneralData()
{

}

void SGeneralData::calcData()
{
   L_V_max = calcVisibilityZone_32();
   FB = calcFreeboard_10();
   t = calc_t_13();
   q = calc_q_14();
   p = calc_p_15();
   cn = calcSEFCoef_27();
   GS_L = calcGoldenSecionByLength_11();
   GS_H = calcGoldenSecionByHeight_12();
}

double SGeneralData::calcVisibilityZone_32()
{
    if (L < 45) return 0;
    else if (L >= 45 and L <= 250) return 2*L;
    else return 500;
}

double SGeneralData::calcFreeboard_10()
{
    return H - T;
}

d_vector SGeneralData::calcGoldenSecionByLength_11()
{
    // there is my trunc
    d_vector gsl = {1, 0.618};
    double gsl_next = gsl[0] - gsl[1];
    double criterion = 0.05;
    while (gsl_next >= criterion)
    {
        gsl.push_back(my_trunc(gsl_next));
        gsl_next = gsl[gsl.size() - 2] - gsl[gsl.size() - 1];
    }
    std::sort(gsl.begin(), gsl.end());
    return gsl;
}

d_vector SGeneralData::calcGoldenSecionByHeight_12()
{
    // there is my trunc
    d_vector gsh = {0.618, 1};
    double gsh_next = gsh[0] + gsh[1];
    double criterion = t/FB;
    while (gsh_next <= criterion)
    {
        gsh.push_back(my_trunc(gsh_next));
        gsh_next = gsh[gsh.size() - 2] + gsh[gsh.size() - 1];
    }
    gsh.push_back(my_trunc(gsh_next));
    return gsh;
}

double SGeneralData::calc_t_13()
{
    return t_ - FB;
}

double SGeneralData::calc_q_14()
{
    return q_ * L;
}

double SGeneralData::calc_p_15()
{
    return t * p_;
}

double SGeneralData::sef_function(double x)
{
    double a0 = cn[0];
    double a1 = cn[1];
    double a2 = cn[2];
    double a3 = cn[3];
    return a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * x + a0;
}

d_vector SGeneralData::calcSEFCoef_27()
{
    d_vector sef_coef(4);
    sef_coef[0] = calcC0();
    sef_coef[2] = calcC2();
    sef_coef[3] = calcC3();
    sef_coef[1] = calcC1();
    return sef_coef;
}

double SGeneralData::calcC0()
{
    return FB;
}

double SGeneralData::calcC1()
{
    double num = 2 * pow(L, 3) * t - 3 * pow(L, 2) * q * t + p * pow(q, 3);
    double den = L * q * (pow(L, 2) - 2 * q * L + pow(q, 2));
    return num/den;
}

double SGeneralData::calcC2()
{
    double num = - (pow(L, 3) * t - 3 * L * pow(q, 2) * t + 2 * p * pow(q, 3));
    double den = L * pow(q, 2) * (pow(L, 2) - 2 * q * L + pow(q, 2));
    return num/den;
}

double SGeneralData::calcC3()
{
    double num = pow(L,2) * t - 2 * L * q * t + p * pow(q, 2);
    double den = L * pow(q, 2) * (pow(L, 2) - 2 * q * L + pow(q, 2));
    return num/den;
}
