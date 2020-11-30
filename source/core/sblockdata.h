#ifndef SBLOCKDATA_H
#define SBLOCKDATA_H

#include <vector>
#include <QString>
#include "sconstants.h"

typedef std::vector<double> d_vector;

enum {
CONS,
CONT,
DISC
};

struct types_of_optimize_var{
    int type = CONS;
    double cons = NOTHING_VALUE;
    double av = NOTHING_VALUE;
    double iv = NOTHING_VALUE;
    double cont_min = NOTHING_VALUE;
    double cont_max = NOTHING_VALUE;
    bool is_golden_section = false;

    d_vector *desc_link;
    d_vector desc_not_gs;
};

class SBlockData
{
public:
    SBlockData();

    std::vector<types_of_optimize_var *> optimize_vect;

    // ЗАМЕНИТЬ
    // Название блока
    // Block Title
    //
    QString titleblock = "";

    // Коэффициент пропорциональности длины блока
    // Length Ratio Coefficient
    // proportion
    types_of_optimize_var lrc;

    // Коэффициент пропорциональности высоты блока
    // Height Ratio Coefficient
    // proportion
    types_of_optimize_var hrc;

    // Угол наклона носовой стенки блока
    // Fore Wall Inclination Heel
    // degrees
    types_of_optimize_var fwih;

    // Угол наклона кормовой стенки блока
    // Aft Wall Inclination Heel
    // degrees
    types_of_optimize_var awih;

    // Ордината размещения блока
    // Block Positioning Ordinate
    // metres
    types_of_optimize_var x;

    // Аппликата размещения блока
    // Block Positioning Applicate
    // metres
    types_of_optimize_var z;

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
    int hb_h = NOTHING_VALUE;

    // Родительский блок по длине
    // Head Block by Length
    //
    int hb_l = NOTHING_VALUE;

    // Расстояние до родительского блока по длине
    // Distance To Head Block by Length
    // metres
    double l_hb_l = NOTHING_VALUE;

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
    double bb_l = NOTHING_VALUE;

    // Длина верхнего основания блока
    // Block's Upper Base Length
    // metres
    double bb_u = NOTHING_VALUE;

    // Высота блока
    // Block's Height
    // metres
    double h = NOTHING_VALUE;

    // Площадь проекции блока на диаметральную плоскость (ДП)
    // Block's Proection Area to centerline plane (CL)
    // sq.metres
    double s = NOTHING_VALUE;

    // Статический момент по оси абсцисс нижнего основания блока
    // Block's Lower Base Statical Moment
    // sq.metres
    double m_a = NOTHING_VALUE;

    // Статический момент по оси абсцисс верхнего основания блока
    // Block's Upper Base Statical Moment
    // sq.metres
    double m_b = NOTHING_VALUE;

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
    double uxa = NOTHING_VALUE;

    // Верхняя носовая точка блока
    // Block's Fore Upper Point
    // metres
    double uxf = NOTHING_VALUE;


    bool is_hull = false;
};

#endif // SBLOCKDATA_H
