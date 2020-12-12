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

void SAlgorithm::startChecks()
{
    bool super_bool = true;

    foreach (auto e, blocks)
    {
        super_bool &= check_41(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_42(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_43(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_44(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_45(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_46(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_47(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_48(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_49(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_50(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_51(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_52(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_53(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_54(e);
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_55(e);
    }
}

bool SAlgorithm::check_41(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_42(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_43(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_44(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_45(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_46(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_47(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_48(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_49(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_50(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_51(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_52(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_53(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_54(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
}

bool SAlgorithm::check_55(SBlockData *e)
{
    Q_UNUSED(e)
    return true;
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

    emitUpdateFormulaeSignal();
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
