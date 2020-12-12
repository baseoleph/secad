#ifndef SALGORITHM_H
#define SALGORITHM_H

#include <QRandomGenerator>
#include <random>
#include <QDebug>
#include "typesofoptimizevar.h"
#include "sm_algorithms.h"
#include "sblockdata.h"

class SAlgorithm
{
public:
    SAlgorithm(BlocksVector new_blocks);
    void startOpt();

private:
    BlocksVector blocks;
    int M = 0;
    double Y = 0;

    void optimizationStep();
    double generateRandomForY();

    void optimizeVal(TypesOfOptimizeVar *var);
    void contOpt(TypesOfOptimizeVar *var);
    void discOpt(TypesOfOptimizeVar *var);
    void clearTypesOpt();
};

#endif // SALGORITHM_H
