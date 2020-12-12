#include "salgorithm.h"

SAlgorithm::SAlgorithm(BlocksVector new_blocks)
{
    blocks = new_blocks;
    clearTypesOpt();

    qDebug() << "Init Opt";
    qDebug() << "";
}

void SAlgorithm::startOpt()
{
    M = 0;
    optimizationStep();
}


void SAlgorithm::optimizationStep()
{
    ++M;
    foreach (auto e, blocks)
    {
        qDebug() << "!!!!!!!!!!!!!!!!!";
        qDebug() << "Block " << e->titleblock;
        qDebug() << "K_L";
        optimizeVal(&e->K_L);
        qDebug() << "K_H";
        optimizeVal(&e->K_H);
        qDebug() << "alpha_A";
        optimizeVal(&e->alpha_A);
        qDebug() << "alpha_F";
        optimizeVal(&e->alpha_F);
    }
}

double SAlgorithm::generateRandomForY()
{
    std::uniform_real_distribution<> dist(-1, 1);
    return dist(*QRandomGenerator::global());
}

void SAlgorithm::optimizeVal(TypesOfOptimizeVar *var)
{
    Y = generateRandomForY();
    if (var->type == DISC)
    {
        qDebug() << "--------------------------";
        qDebug() << "DISC, av = " << var->av;
        qDebug() << "av_i = " << var->av_i;
        discOpt(var);
    }
    else if (var->type == CONT)
    {
        qDebug() << "--------------------------";
        qDebug() << "CONT, av = " << var->av;
        contOpt(var);
    }
    else
    {
        qDebug() << "--------------------------";
        qDebug() << "CONS, av = " << var->av;
        qDebug() << "--------------------------";
        qDebug() << "";
    }
}

void SAlgorithm::contOpt(TypesOfOptimizeVar *var)
{
    var->iv = var->av + (var->cont_max - var->cont_min) * pow(Y, M);
    qDebug() << "min = " << var->cont_min;
    qDebug() << "max = " << var->cont_max;
    qDebug() << "pow(Y, M) = " << pow(Y, M);
    qDebug() << "iv = " << var->iv;

    if (var->iv > var->cont_max)
    {
        var->iv = var->cont_max;
        qDebug() << "was overflow iv = " << var->iv;
    }
    else if (var->iv < var->cont_min)
    {
        var->iv = var->cont_min;
        qDebug() << "was overflow iv = " << var->iv;
    }
    qDebug() << "--------------------------";
    qDebug() << "";
}

void SAlgorithm::discOpt(TypesOfOptimizeVar *var)
{
    int max_i = var->desc_link.size() - 1;
    int min_i = 0;
    var->iv_i = var->av_i + max_i * pow(Y, M);
    var->iv = var->desc_link[var->iv_i];
    qDebug() << "min_i = " << 0;
    qDebug() << "max_i = " << var->desc_link.size()-1;
    qDebug() << "pow(Y, M) = " << pow(Y, M);
    qDebug() << "iv = " << var->iv;
    qDebug() << "iv_i = " << var->iv_i;

    if (var->iv_i > max_i)
    {
        var->iv_i = max_i;
        var->iv = var->desc_link[var->iv_i];
        qDebug() << "was overflow iv_i = " << var->iv_i;
        qDebug() << "iv = " << var->iv;
    }
    else if (var->iv_i < min_i)
    {
        var->iv_i = min_i;
        var->iv = var->desc_link[var->iv_i];
        qDebug() << "was overflow iv_i = " << var->iv_i;
        qDebug() << "iv = " << var->iv;
    }
    qDebug() << "--------------------------";
    qDebug() << "";
}

void SAlgorithm::clearTypesOpt()
{
    foreach (auto e, blocks)
    {
        e->K_H.setRandomAvValue();
        e->K_L.setRandomAvValue();
        e->alpha_F.setRandomAvValue();
        e->alpha_A.setRandomAvValue();
        e->X.setRandomAvValue();
    }
}
