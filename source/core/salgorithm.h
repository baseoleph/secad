#ifndef SALGORITHM_H
#define SALGORITHM_H

#include <QRandomGenerator>
#include <random>
#include <QDebug>
#include "typesofoptimizevar.h"

class SAlgorithm
{
public:
    SAlgorithm();
    void init();
    void optimizeVal(TypesOfOptimizeVar *var);

private:
    int M = 0;
    double Y = 0;

    double generateRandomForY();
    void contOpt(TypesOfOptimizeVar *var);
    void consOpt(TypesOfOptimizeVar *var);
};

#endif // SALGORITHM_H
