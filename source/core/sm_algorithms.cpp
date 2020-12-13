#include "sm_algorithms.h"

double my_trunc(double d)
{
    return  std::trunc(d * PRECISION) / PRECISION;
}

double my_ctg(double val_in_degrees)
{
    double val_in_rad = qDegreesToRadians(val_in_degrees);
    double ctg_val = qCos(val_in_rad)/qSin(val_in_rad);
    return ctg_val;
}
