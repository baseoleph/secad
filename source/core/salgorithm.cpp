#include "salgorithm.h"

SAlgorithm::SAlgorithm(BlocksVector new_blocks, SGeneralData *new_general)
{
    general = new_general;
    blocks = new_blocks;
    clearTypesOpt();
    qDebug(logInfo()) << "Init Opt";
    qDebug(logInfo()) << "";
}

void SAlgorithm::startOpt()
{
    M = 0;
    optimizationStep();
}

bool SAlgorithm::startChecks()
{
    bool super_bool = true;

    qDebug(logInfo()) << "-----------------";
    qDebug(logInfo()) << "Start Check";
    qDebug(logInfo()) << "-----------------";
    foreach (auto e, blocks)
    {
        SBlockData *e_host = nullptr;
        if (e->HB_H != 0)
        {
            e_host = blocks[e->HB_H - 1];
            super_bool &= check_37(e, e_host);
            super_bool &= check_38(e, e_host);
        }
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_41(e);
    }

    super_bool &= check_43();

    super_bool &= check_44();

    foreach (auto e, blocks)
    {
        if (e->HB_L == 0 && e->HB_H == 1)
        {
            super_bool &= check_45(e);
            break;
        }
    }

    SBlockData *e_last;
    foreach (auto e, blocks)
    {
        if (e->HB_H == 1)
        {
            if (e->HB_L != 0)
            {
                e_last = e;
                break;
            }
        }
    }
    super_bool &= check_46(e_last);

    foreach (auto e, blocks)
    {
        if (e->funnel)
        {
            super_bool &= check_47(e);
            break;
        }
    }

    foreach (auto e, blocks)
    {
        if (e->foremast)
        {
            super_bool &= check_48(e);
            break;
        }
    }

    foreach (auto e, blocks)
    {
        if (e->mainmast)
        {
            super_bool &= check_49(e);
            break;
        }
    }

    foreach (auto e, blocks)
    {
        super_bool &= check_51(e);
    }

    foreach (auto e, blocks)
    {
        if (e->pap)
        {
            super_bool &= check_52(e);
            super_bool &= check_53(e);
            break;
        }
    }

    SBlockData *e_funn = nullptr;
    foreach (auto e, blocks)
    {
        if (e->funnel)
        {
            e_funn = e;
            break;
        }
    }
    foreach (auto e, blocks)
    {
        if (e->X.iv >= e_funn->X.iv + e_funn->a)
        {
            super_bool &= check_54(e, e);
        }
    }

    super_bool &= check_55();

    return super_bool;
}

bool SAlgorithm::check_37(SBlockData *e_h, SBlockData *e_s)
{
    bool prop = (e_s->X.iv >= e_h->X.iv + e_h->h * my_ctg(e_h->alpha_A.iv));

    qDebug(logInfo()) << prop << "check_37" << e_s->titleblock << "host - " << e_h->titleblock;
    return prop;
}

bool SAlgorithm::check_38(SBlockData *e_h, SBlockData *e_s)
{
    bool prop = (e_s->X.iv + e_s->a <= e_h->X.iv + e_h->a - e_h->h * my_ctg(e_h->alpha_A.iv));
    qDebug(logInfo()) << prop << "check_38" << e_s->titleblock << "host - " << e_h->titleblock;
    return prop;
}

bool SAlgorithm::check_41(SBlockData *e)
{
    bool prop = (e->b > 0);
    qDebug(logInfo()) << prop << "check_41" << e->titleblock;
    return prop;
}

bool SAlgorithm::check_43()
{
    double S_main_without_hal = 0;
    for (int i = 1; i < blocks.size(); ++i)
    {
        if (blocks[i]->habitability)
        {
            S_main_without_hal += blocks[i]->S;
        }
    }

    bool prop = (S_main_without_hal >= (general->k_DS * general->L * general->FB));
    qDebug(logInfo()) << prop << "check_43" << "general";
    return prop;
}

bool SAlgorithm::check_44()
{
    double S_mul_Z = 0;
    for (int i = 0; i < blocks.size(); ++i)
    {
        S_mul_Z += blocks[i]->S * blocks[i]->z_g;
    }

    bool prop = (general->p_w * S_mul_Z/(general->D * general->GM) <= qDegreesToRadians(15.0));
    qDebug(logInfo()) << prop << "check_44" << "general";
    return prop;
}

bool SAlgorithm::check_45(SBlockData *e)
{
    bool prop = (e->X.iv >= 20);
    qDebug(logInfo()) << prop << "check_45" << e->titleblock;
    return prop;
}

bool SAlgorithm::check_46(SBlockData *e)
{
    bool prop = (e->a + e->X.iv <= general->L);
    qDebug(logInfo()) << prop << "check_46" << e->titleblock;
    return prop;
}

bool SAlgorithm::check_47(SBlockData *e)
{
    bool prop = (8.0 <= e->h and e->h <= 12.0);
    qDebug(logInfo()) << prop << "check_47" << e->titleblock;
    return prop;
}

bool SAlgorithm::check_48(SBlockData *e)
{
    bool prop = (15.0 <= e->h and e->h <= 20.0);
    qDebug(logInfo()) << prop << "check_48" << e->titleblock;
    return prop;
}

bool SAlgorithm::check_49(SBlockData *e)
{
    bool prop = (5.0 <= e->h and e->h <= 12.0);
    qDebug(logInfo()) << prop << "check_49" << e->titleblock;
    return prop;
}

bool SAlgorithm::check_51(SBlockData *e)
{
    double argument = e->X.iv + e->h * my_ctg(e->alpha_A.iv);
    bool prop = (e->h + e->Z <= functionV_33(argument));
    qDebug(logInfo()) << prop << "check_51" << e->titleblock;
    return prop;
}

bool SAlgorithm::check_52(SBlockData *e)
{
    bool prop = (e->S >= 20.0);
    qDebug(logInfo()) << prop << "check_52" << e->titleblock;
    return prop;
}

bool SAlgorithm::check_53(SBlockData *e)
{
    bool prop = (e->h >= 6.3);
    qDebug(logInfo()) << prop << "check_53" << e->titleblock;
    return prop;
}

bool SAlgorithm::check_54(SBlockData *e, SBlockData *e_funn)
{
    bool prop = (e->Z + e->h >= e_funn->Z + e_funn->h);
    qDebug(logInfo()) << prop << "check_54" << e->titleblock;
    return prop;
}

bool SAlgorithm::check_55()
{
    double S_mul_x_g = 0;
    double S_main = 0;
    foreach (auto el, blocks)
    {
        S_mul_x_g += el->S * el->x_g;
        S_main += el->S;
    }

    double arg = S_mul_x_g / (general->L * S_main);
    bool prop = (0.41 <= arg and arg <= 0.48);
    qDebug(logInfo()) << prop << "check_41" << "general";
    return prop;
}


void SAlgorithm::optimizationStep()
{
    ++M;

    qDebug(logInfo()) << "__________________";
    qDebug(logInfo()) << "M = " << M;
    qDebug(logInfo()) << "__________________";

    emitStatusBarSignal(QString::number(M));

    foreach (auto e, blocks)
    {
        qDebug(logInfo()) << "!!!!!!!!!!!!!!!!!";
        qDebug(logInfo()) << "Block " << e->titleblock;
        qDebug(logInfo()) << "K_L";
        optimizeVal(&e->K_L);
        qDebug(logInfo()) << "K_H";
        optimizeVal(&e->K_H);
        qDebug(logInfo()) << "alpha_A";
        optimizeVal(&e->alpha_A);
        qDebug(logInfo()) << "alpha_F";
        optimizeVal(&e->alpha_F);
        qDebug(logInfo()) << "X";
        optimizeVal(&e->X);
    }

    emitUpdateFormulaeSignal();
    qDebug() << startChecks();
}

double SAlgorithm::generateRandomForY()
{
    std::uniform_real_distribution<> dist(-1, 1);
    return dist(*QRandomGenerator::global());
}

double SAlgorithm::functionV_33(double x)
{
    SBlockData *e = nullptr;
    foreach (auto el, blocks)
    {
        if (el->wheelhause)
        {
            e = el;
        }
    }
    double k_num = e->h + e->Z;
    double k_den = e->X.iv + e->a + e->h * my_ctg(e->alpha_F.iv) - general->L - general->L_V_max;
    double k = k_num / k_den;
    double g_num = (e->h + e->Z) * (-general->L - general->L_V_max);
    double g_den = e->X.iv + e->a + e->h * my_ctg(e->alpha_F.iv) - general->L - general->L_V_max;
    double g = g_num / g_den;
    double v_x = k * x + g;
    return v_x;
}

void SAlgorithm::optimizeVal(TypesOfOptimizeVar *var)
{
    Y = generateRandomForY();
    if (var->type == DISC)
    {
        qDebug(logInfo()) << "--------------------------";
        qDebug(logInfo()) << "DISC, av = " << var->av;
        qDebug(logInfo()) << "av_i = " << var->av_i;
        discOpt(var);
    }
    else if (var->type == CONT)
    {
        qDebug(logInfo()) << "--------------------------";
        qDebug(logInfo()) << "CONT, av = " << var->av;
        contOpt(var);
    }
    else
    {
        qDebug(logInfo()) << "--------------------------";
        qDebug(logInfo()) << "CONS, av = " << var->av;
        qDebug(logInfo()) << "--------------------------";
        qDebug(logInfo()) << "";
    }
}

void SAlgorithm::contOpt(TypesOfOptimizeVar *var)
{
    var->iv = var->av + (var->cont_max - var->cont_min) * pow(Y, M);
    qDebug(logInfo()) << "min = " << var->cont_min;
    qDebug(logInfo()) << "max = " << var->cont_max;
    qDebug(logInfo()) << "pow(Y, M) = " << pow(Y, M);
    qDebug(logInfo()) << "iv = " << var->iv;

    if (var->iv > var->cont_max)
    {
        var->iv = var->cont_max;
        qDebug(logInfo()) << "was overflow iv = " << var->iv;
    }
    else if (var->iv < var->cont_min)
    {
        var->iv = var->cont_min;
        qDebug(logInfo()) << "was overflow iv = " << var->iv;
    }
    qDebug(logInfo()) << "--------------------------";
    qDebug(logInfo()) << "";
}

void SAlgorithm::discOpt(TypesOfOptimizeVar *var)
{
    int max_i = var->desc_link.size() - 1;
    int min_i = 0;
    var->iv_i = var->av_i + max_i * pow(Y, M);
    qDebug(logInfo()) << "min_i = " << 0;
    qDebug(logInfo()) << "max_i = " << var->desc_link.size()-1;
    qDebug(logInfo()) << "pow(Y, M) = " << pow(Y, M);
    qDebug(logInfo()) << "iv_i = " << var->iv_i;

    if (var->iv_i > max_i)
    {
        var->iv_i = max_i;
        qDebug(logInfo()) << "was overflow iv_i = " << var->iv_i;
    }
    else if (var->iv_i < min_i)
    {
        var->iv_i = min_i;
        qDebug(logInfo()) << "was overflow iv_i = " << var->iv_i;
    }

    var->iv = var->desc_link[var->iv_i];
    qDebug(logInfo()) << "iv = " << var->iv;
    qDebug(logInfo()) << "--------------------------";
    qDebug(logInfo()) << "";
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
