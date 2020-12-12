#include "salgorithm.h"

SAlgorithm::SAlgorithm()
{

}

void SAlgorithm::init()
{
    M = 1;
    Y = generateRandomForY();
}

double SAlgorithm::generateRandomForY()
{
    std::uniform_real_distribution<> dist(-1, 1);
    return dist(*QRandomGenerator::global());
}

void SAlgorithm::optimizeVal(TypesOfOptimizeVar *var)
{
    if (var->type == CONS)
    {
        consOpt(var);
    }
    else if (var->type == CONT)
    {
        contOpt(var);
    }
}

void SAlgorithm::contOpt(TypesOfOptimizeVar *var)
{
    var->iv = var->av + (var->cont_max - var->cont_min) * pow(Y, M);
    if (var->iv > var->cont_max)
    {
        var->iv = var->cont_max;
    }
    else if (var->iv < var->cont_min)
    {
        var->iv = var->cont_min;
    }
}

void SAlgorithm::consOpt(TypesOfOptimizeVar *var)
{

}
