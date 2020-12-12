#ifndef SALGORITHM_H
#define SALGORITHM_H

#include <QRandomGenerator>
#include <random>
#include <QDebug>
#include "typesofoptimizevar.h"
#include "sm_algorithms.h"
#include "sblockdata.h"

//typedef  std::vector<SBlockData *> BlocksVector;

class SAlgorithm
{
public:
    SAlgorithm();
    void init(BlocksVector p_blocks);
    void optimizeVal(TypesOfOptimizeVar *var);

private:
    BlocksVector blocks;
    int M = 0;
    double Y = 0;

    double generateRandomForY();
    void contOpt(TypesOfOptimizeVar *var);
    void discOpt(TypesOfOptimizeVar *var);
};

#endif // SALGORITHM_H
