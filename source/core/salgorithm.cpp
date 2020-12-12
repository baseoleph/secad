#include "salgorithm.h"

SAlgorithm::SAlgorithm()
{

}

void SAlgorithm::init()
{
    M = 1;
    Y = generateRandomForY();

    qDebug() << "Init Opt";
    qDebug() << "M = " << M;
    qDebug() << "Y = " << Y;
    qDebug() << "";
}

double SAlgorithm::generateRandomForY()
{
    std::uniform_real_distribution<> dist(-1, 1);
    return dist(*QRandomGenerator::global());
}

void SAlgorithm::optimizeVal(TypesOfOptimizeVar *var)
{
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
    qDebug() << "min_i = " << 0;
    qDebug() << "max_i = " << var->desc_link.size()-1;
    qDebug() << "pow(Y, M) = " << pow(Y, M);
    qDebug() << "iv_i = " << var->iv_i;

    if (var->iv_i > max_i)
    {
        var->iv_i = max_i;
        qDebug() << "was overflow iv_i = " << var->iv_i;
    }
    else if (var->iv_i < min_i)
    {
        var->iv_i = min_i;
        qDebug() << "was overflow iv_i = " << var->iv_i;
    }
    qDebug() << "--------------------------";
    qDebug() << "";
}
