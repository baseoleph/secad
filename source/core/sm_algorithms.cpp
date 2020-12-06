#include "sm_algorithms.h"

double my_trunc(double d)
{
    return  std::trunc(d * PRECISION) / PRECISION;
}
