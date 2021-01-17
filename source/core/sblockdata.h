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

#ifndef SBLOCKDATA_H
#define SBLOCKDATA_H

#include <vector>
#include <QString>
#include "typesofoptimizevar.h"

//typedef std::vector<double> d_vector;

class SBlockData
{
public:
    SBlockData();


    std::vector<TypesOfOptimizeVar *> optimize_vect;

    // ЗАМЕНИТЬ
    // Название блока
    // Block Title
    //
    QString titleblock = "";

    // Коэффициент пропорциональности длины блока
    // Length Ratio Coefficient
    // proportion
    TypesOfOptimizeVar K_L;

    // Коэффициент пропорциональности высоты блока
    // Height Ratio Coefficient
    // proportion
    TypesOfOptimizeVar K_H;

    // Угол наклона носовой стенки блока
    // Fore Wall Inclination Heel
    // degrees
    TypesOfOptimizeVar alpha_F;

    // Угол наклона кормовой стенки блока
    // Aft Wall Inclination Heel
    // degrees
    TypesOfOptimizeVar alpha_A;

    // Ордината размещения блока
    // Block Positioning Ordinate
    // metres
    TypesOfOptimizeVar X;

    // Аппликата размещения блока
    // Block Positioning Applicate
    // metres
    double Z;

    // Обитаемый блок
    // Habitabilical Block
    //
    bool habitability = false;

    // Размещение на блоке фазированной антенной решётки
    // Phased Array Placement
    //
    bool pap = false;

    // Фок-мачта
    // Foremast
    //
    bool foremast = false;

    // Грот-мачта
    // Mainmast
    //
    bool mainmast = false;

    // Дымовая труба
    // Funnel
    //
    bool funnel = false;

    //Размещение на блоке рулевой рубки
    // Wheelhouse Placement
    //
    bool wheelhause = false;

    // Родительский блок по высоте
    // Head Block by Height
    //
    int HB_H = 0;

    // Родительский блок по длине
    // Head Block by Length
    //
    int HB_L = 0;

    // Расстояние до родительского блока по длине
    // Distance To Head Block by Length
    // metres
    double L_HB_L = NOTHING_VALUE;

    // Дочерний блок по высоте
    // Slave Block by Height
    //
    QString sb_h = "";

    // Дочерний блок по длине
    // Slave Block by Length
    //
    QString sb_l = "";

    // Длина нижнего основания блока
    // Block's Lower Base Length
    // metres
    double a = NOTHING_VALUE;

    // Длина верхнего основания блока
    // Block's Upper Base Length
    // metres
    double b = NOTHING_VALUE;

    // Высота блока
    // Block's Height
    // metres
    double h = NOTHING_VALUE;

    // Площадь проекции блока на диаметральную плоскость (ДП)
    // Block's Proection Area to centerline plane (CL)
    // sq.metres
    double S = NOTHING_VALUE;

    // Статический момент по оси абсцисс нижнего основания блока
    // Block's Lower Base Statical Moment
    // sq.metres
    double M_a = NOTHING_VALUE;

    // Статический момент по оси абсцисс верхнего основания блока
    // Block's Upper Base Statical Moment
    // sq.metres
    double M_b = NOTHING_VALUE;

    // Абсцисса центра тяжести (ЦТ) площади проекции блока на ДП
    // Block's Proection Area to CL Gravity Center (CG) Ordinate
    // metres
    double x_g = NOTHING_VALUE;

    // Аппликата ЦТ площади проекции блока на ДП
    // Block's Proection Area to CL CG Ordinate
    // metres
    double z_g = NOTHING_VALUE;

    // Верхняя кормовая точка блока
    // Block's Aft Upper Point
    // metres
    double X_U_A = NOTHING_VALUE;

    // Верхняя носовая точка блока
    // Block's Fore Upper Point
    // metres
    double X_U_F = NOTHING_VALUE;


    bool is_hull = false;
};

typedef  QVector<SBlockData *> BlocksVector;
#endif // SBLOCKDATA_H
