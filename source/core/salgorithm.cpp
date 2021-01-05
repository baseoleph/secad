#include "salgorithm.h"

SAlgorithm::SAlgorithm(BlocksVector new_blocks, SGeneralData *new_general)
{
    general = new_general;
    blocks = new_blocks;
    clearTypesOpt();
    onOptimize = false;
}

SAlgorithm::~SAlgorithm()
{
}

bool SAlgorithm::startOpt()
{
    if (not onOptimize)
    {
        M = 0;
        cnt = 0;
        EC_cnt = 0;
        general->ECB = NOTHING_VALUE;
        clear_supers();
        onOptimize = true;
    }

    QString str;
    while (M < 1000 && (cnt < 1000000 || EC_cnt))
    {
        ++cnt;
        if (EC_cnt == 0)
        {
            clearTypesOpt();
        }
        optimizationStep();
        str = "cnt = " + QString::number(cnt);
        str += "; EC_cnt = " + QString::number(EC_cnt);
        str += "; M = " + QString::number(M);
        emitStatusBarSignal(str);
        if (cnt % 10000 == 0)
        {
            return onOptimize;
        }
    }

    if (EC_cnt == 0) emitStatusBarSignal("Более " + QString::number(cnt) + " итераций.");
    updateIV();
    emitUpdateFormulaeSignal();

    qDebug() << "super_37" << super_37;
    qDebug() << "super_38" << super_38;
    qDebug() << "super_41" << super_41;
    qDebug() << "super_43" << super_43;
    qDebug() << "super_44" << super_44;
    qDebug() << "super_45" << super_45;
    qDebug() << "super_46" << super_46;
    qDebug() << "super_47" << super_47;
    qDebug() << "super_48" << super_48;
    qDebug() << "super_49" << super_49;
    qDebug() << "super_51" << super_51;
    qDebug() << "super_52" << super_52;
    qDebug() << "super_53" << super_53;
    qDebug() << "super_54" << super_54;
    qDebug() << "super_55" << super_55;
    qDebug() << "cnt_37" << cnt_37;
    qDebug() << "cnt_38" << cnt_38;
    qDebug() << "cnt_41" << cnt_41;
    qDebug() << "cnt_43" << cnt_43;
    qDebug() << "cnt_44" << cnt_44;
    qDebug() << "cnt_45" << cnt_45;
    qDebug() << "cnt_46" << cnt_46;
    qDebug() << "cnt_47" << cnt_47;
    qDebug() << "cnt_48" << cnt_48;
    qDebug() << "cnt_49" << cnt_49;
    qDebug() << "cnt_51" << cnt_51;
    qDebug() << "cnt_52" << cnt_52;
    qDebug() << "cnt_53" << cnt_53;
    qDebug() << "cnt_54" << cnt_54;
    qDebug() << "cnt_55" << cnt_55;

    onOptimize = false;
    return onOptimize;
}

void SAlgorithm::calcedFormulae()
{
    is_calcing_formulae = false;
}

void SAlgorithm::clear_supers()
{
    super_37 = false;
    super_38 = false;
    super_41 = false;
    super_43 = false;
    super_44 = false;
    super_45 = false;
    super_46 = false;
    super_47 = false;
    super_48 = false;
    super_49 = false;
    super_51 = false;
    super_52 = false;
    super_53 = false;
    super_54 = false;
    super_55 = false;
    cnt_37 = 0;
    cnt_38 = 0;
    cnt_41 = 0;
    cnt_43 = 0;
    cnt_44 = 0;
    cnt_45 = 0;
    cnt_46 = 0;
    cnt_47 = 0;
    cnt_48 = 0;
    cnt_49 = 0;
    cnt_51 = 0;
    cnt_52 = 0;
    cnt_53 = 0;
    cnt_54 = 0;
    cnt_55 = 0;
}

void SAlgorithm::updateEC()
{
    EC = 0;
    foreach (auto e, blocks)
    {
        double arg1 = general->sef_function(e->X_U_A) - (e->h + e->Z);
        double arg2 = general->sef_function(e->X_U_F) - (e->h + e->Z);
        EC += pow(arg1, 2) + pow(arg2, 2);
    }

    if (general->ECB == NOTHING_VALUE)
    {
        general->ECB = EC;
        updateAV();
        ++EC_cnt;
        M = 0;
    }
    else
    {
        if (general->ECB > EC)
        {
            general->ECB = EC;
            updateAV();
            ++EC_cnt;
            M = 0;
        }
        else
        {
            M += iterator;
        }
    }
}

void SAlgorithm::updateAV()
{

    foreach (auto e, blocks)
    {
        e->K_H.av = e->K_H.iv;
        e->K_H.av_i = e->K_H.iv_i;

        e->K_L.av = e->K_L.iv;
        e->K_L.av_i = e->K_L.iv_i;

        e->alpha_F.av = e->alpha_A.iv;
        e->alpha_F.av_i = e->alpha_A.iv_i;

        e->alpha_A.av = e->alpha_F.iv;
        e->alpha_A.av_i = e->alpha_F.iv_i;

        e->X.av = e->X.iv;
        e->X.av_i = e->X.iv_i;
    }
}

void SAlgorithm::updateIV()
{
    foreach (auto e, blocks)
    {
        e->K_H.iv = e->K_H.av;
        e->K_H.iv_i = e->K_H.av_i;

        e->K_L.iv = e->K_L.av;
        e->K_L.iv_i = e->K_L.av_i;

        e->alpha_F.iv = e->alpha_A.av;
        e->alpha_F.iv_i = e->alpha_A.av_i;

        e->alpha_A.iv = e->alpha_F.av;
        e->alpha_A.iv_i = e->alpha_F.av_i;

        e->X.iv = e->X.av;
        e->X.iv_i = e->X.av_i;
    }
}

bool SAlgorithm::startChecks()
{
    bool super_bool = true;

    foreach (auto e, blocks)
    {
        SBlockData *e_host = nullptr;
        if (e->HB_H != 0)
        {
            e_host = blocks[e->HB_H - 1];
            bool bl = check_37(e_host, e);
            super_37 |= bl;
            super_bool &= bl;
            if (not bl) ++cnt_37;

            bl = check_38(e_host, e);
            super_bool &= bl;
            super_38 |= bl;
            if (not bl) ++cnt_38;
        }
    }

    super_37 = true;
    super_38 = true;

    foreach (auto e, blocks)
    {
        bool bl = check_41(e);
        super_bool &= bl;
        super_41 |= bl;
        if (not bl) ++cnt_41;
    }

    bool bl = check_43();
    super_bool &= bl;
    super_43 |= bl;
    if (not bl) ++cnt_43;

//super_43 = true;

    bl = check_44();
    super_bool &= bl;
    super_44 |= bl;
    if (not bl) ++cnt_44;

    foreach (auto e, blocks)
    {
        if (e->HB_L == 0 && e->HB_H == 1)
        {
            bool bl = check_45(e);
            super_bool &= bl;
            super_45 |= bl;
            if (not bl) ++cnt_45;
            break;
        }
    }

    SBlockData *e_last = nullptr;

    foreach (auto e, blocks)
    {
        if (e->HB_H == 1)
        {
            if (e->HB_L == 0)
            {
                e_last = e;
            }
            if (e->HB_L != 0)
            {
                e_last = e;
            }
        }

    }

    bl = check_46(e_last);
    super_bool &= bl;
    super_46 |= bl;
    if (not bl) ++cnt_46;
    super_46 = true;

    foreach (auto e, blocks)
    {
        if (e->funnel)
        {
            bool bl = check_47(e);
            super_bool &= bl;
            super_47 |= bl;
            if (not bl) ++cnt_47;
            break;
        }
    }
    super_47 = true;

//    foreach (auto e, blocks)
//    {
//        if (e->foremast)
//        {
//            bool bl = check_48(e);
//            super_bool &= bl;
//            super_48 |= bl;
//            break;
//        }
//    }

//    foreach (auto e, blocks)
//    {
//        if (e->mainmast)
//        {
//            bool bl = check_49(e);
//            super_bool &= bl;
//            super_49 |= bl;
//            break;
//        }
//    }

    super_48 = true;
    super_49 = true;

    SBlockData *wheel_e;
    foreach (auto e, blocks)
    {
        if (e->wheelhause)
        {
            wheel_e = e;
            break;
        }
    }

    foreach (auto e, blocks)
    {
        if (e->X_U_F < wheel_e->X_U_F)
        {
            bool bl = check_51(e);
            super_bool &= bl;
            super_51 |= bl;
            if (not bl) ++cnt_51;
        }
    }
//super_51 = true;
    foreach (auto e, blocks)
    {
        if (e->pap)
        {
            bool bl = check_52(e);
            super_bool &= bl;
            super_52 |= bl;
            if (not bl) ++cnt_52;

            bl = check_53(e);
            super_bool &= bl;
            super_53 |= bl;
            if (not bl) ++cnt_53;

            break;
        }
    }
//    super_52 = true;
//    super_53 = true;

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
        if (e_funn == nullptr)
        {
            super_54 = true;
            break;
        }
        if (e->funnel == false)
        {
            if (e->X_U_A >= e_funn->X_U_A)
            {
                bool bl = check_54(e, e_funn);
                super_bool &= bl;
                super_54 |= bl;
                if (not bl) ++cnt_54;
            }
        }
    }

//    super_54 = true;

    bl = check_55();
    super_bool &= bl;
    super_55 |= bl;
    if (not bl) ++cnt_55;

//    super_55 = true;

    return super_bool;
}

bool SAlgorithm::check_37(SBlockData *e_h, SBlockData *e_s)
{
//    bool prop = (e_s->X.iv >= e_h->X.iv + e_h->h * my_ctg(e_h->alpha_A.iv));
    bool prop = (e_s->X.iv >= e_h->X_U_F);
    if (prop)
    {

    }
    return prop;
}

bool SAlgorithm::check_38(SBlockData *e_h, SBlockData *e_s)
{
//    bool prop = (e_s->X.iv + e_s->a <= e_h->X.iv + e_h->a - e_h->h * my_ctg(e_h->alpha_A.iv));
    bool prop = (e_s->X.iv + e_s->a <= e_h->X_U_A);
    if (prop)
    {

    }
    return prop;
}

bool SAlgorithm::check_41(SBlockData *e)
{
    bool prop = (e->b > 0);
    return prop;
}

bool SAlgorithm::check_43()
{
    if (blocks.size() < 2)
    {
        return true;
    }

    double S_main_without_hal = 0;
    for (int i = 1; i < blocks.size(); ++i)
    {
        if (blocks[i]->habitability)
        {
            S_main_without_hal += blocks[i]->S;
        }
    }

    bool prop = (S_main_without_hal >= (general->k_DS * general->L * general->FB));
    return prop;
}

bool SAlgorithm::check_44()
{
    double S_mul_Z = 0;
    for (int i = 0; i < blocks.size(); ++i)
    {
        S_mul_Z += blocks[i]->S * blocks[i]->z_g;
    }

    bool prop = ((general->p_w * S_mul_Z)/(general->D * general->GM * 1000 * GRAV) <= qDegreesToRadians(15.0));
    return prop;
}

bool SAlgorithm::check_45(SBlockData *e)
{
    if (blocks.size() < 2)
    {
        return true;
    }
    bool prop = (e->X.iv >= 20);
    return prop;
}

bool SAlgorithm::check_46(SBlockData *e)
{
    if (blocks.size()<2)
    {
        return true;
    }
    bool prop = ((e->a + e->X.iv) <= (general->L - 15));
    return prop;
}

bool SAlgorithm::check_47(SBlockData *e)
{
    bool prop = (8.0 <= e->h and e->h <= 12.0);
    return prop;
}

bool SAlgorithm::check_48(SBlockData *e)
{
    bool prop = (15.0 <= e->h and e->h <= 20.0);
    return prop;
}

bool SAlgorithm::check_49(SBlockData *e)
{
    bool prop = (5.0 <= e->h and e->h <= 12.0);
    return prop;
}

bool SAlgorithm::check_51(SBlockData *e)
{
    if (blocks.size() < 2)
    {
        return true;
    }
    double argument = e->X_U_F;
    bool prop = (e->h + e->Z <= functionV_33(argument));
    return prop;
}

bool SAlgorithm::check_52(SBlockData *e)
{
    bool prop = (e->S >= 20.0);
    return prop;
}

bool SAlgorithm::check_53(SBlockData *e)
{
    bool prop = (e->h >= 6.3);
    return prop;
}

bool SAlgorithm::check_54(SBlockData *e, SBlockData *e_funn)
{
    bool prop = (e->Z + e->h < e_funn->Z + e_funn->h);
    return prop;
}

bool SAlgorithm::check_55()
{
    if (blocks.size() < 2)
    {
        return true;
    }
    double S_mul_x_g = 0;
    double S_main = 0;
    foreach (auto el, blocks)
    {
        S_mul_x_g += el->S * el->x_g;
        S_main += el->S;
    }

    double arg = S_mul_x_g / (general->L * S_main);
    bool prop = (0.41 <= arg and arg <= 0.48);
    return prop;
}


void SAlgorithm::optimizationStep()
{
    M += iterator;

    foreach (auto e, blocks)
    {
        if (e->HB_H != 0 )
        {
            if (e->HB_H != 1)
            {
                SBlockData *parent_block = blocks[e->HB_H - 1];
                e->X.type = 1;
                if (parent_block->X_U_F < parent_block->X_U_A)
                {
                    e->X.cont_min = parent_block->X_U_F;
                    e->X.cont_max = parent_block->X_U_A;
                }
            }
        }

        optimizeVal(&e->K_L);
        optimizeVal(&e->K_H);
        optimizeVal(&e->alpha_A);
        optimizeVal(&e->alpha_F);
        optimizeVal(&e->X);
    }

    is_calcing_formulae = true;

    emitUpdateFormulaeSignal();
    while (is_calcing_formulae);

    bool check_status = startChecks();

    if (check_status)
    {
        updateEC();
    }
    else
    {
        if (general->ECB == NOTHING_VALUE)
        {
//            M = 0;
        }
    }
}

double SAlgorithm::generateRandomForY()
{
    std::uniform_real_distribution<> dist666(-1, 1);
    double sd = dist666(*QRandomGenerator::global());
    return sd;
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
    double k_den = e->X_U_F + general->L_V_max;
    double k = k_num / k_den;
    double g_num = (e->h + e->Z) * (general->L_V_max);
    double g_den = e->X_U_F + general->L_V_max;
    double g = g_num / g_den;
    double v_x = k * x + g;
    return v_x;
}

void SAlgorithm::optimizeVal(TypesOfOptimizeVar *var)
{
    Y = generateRandomForY();
    if (var->type == DISC)
    {
        discOpt(var);
    }
    else if (var->type == CONT)
    {
        contOpt(var);
    }
}

void SAlgorithm::contOpt(TypesOfOptimizeVar *var)
{
    var->iv = var->av + (var->cont_max - var->cont_min) * pow(Y, trunc(M));

    if (var->iv > var->cont_max)
    {
        var->iv = var->cont_max;
    }
    else if (var->iv < var->cont_min)
    {
        var->iv = var->cont_min;
    }
}

void SAlgorithm::discOpt(TypesOfOptimizeVar *var)
{
    int max_i = var->desc_link.size() - 1;
    int min_i = 0;
    var->iv_i = var->av_i + max_i * pow(Y, trunc(M));

    if (var->iv_i > max_i)
    {
        var->iv_i = max_i;
    }
    else if (var->iv_i < min_i)
    {
        var->iv_i = min_i;
    }

    var->iv = var->desc_link[var->iv_i];
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
