#include "smainclass.h"

SMainClass::SMainClass()
{
    general = new SGeneralData();
}

SMainClass::~SMainClass()
{
    delete general;
    foreach (auto e, blocks)
    {
        delete e;
    }
}

void SMainClass::optimizeData()
{
    if (alg != nullptr) delete alg;
    alg = new SAlgorithm;
    alg->init();

    foreach (auto e, blocks)
    {
        alg->optimizeVal(&e->K_L);
        alg->optimizeVal(&e->K_H);
        alg->optimizeVal(&e->alpha_A);
        alg->optimizeVal(&e->alpha_F);
    }
}

void SMainClass::calculateData()
{
    foreach (auto e, blocks)
    {
        if (true || e->K_H.av == NOTHING_VALUE) e->K_H.setRandomAvValue();
        if (true || e->K_L.av == NOTHING_VALUE) e->K_L.setRandomAvValue();
        if (true || e->alpha_F.av == NOTHING_VALUE) e->alpha_F.setRandomAvValue();
        if (true || e->alpha_A.av == NOTHING_VALUE) e->alpha_A.setRandomAvValue();
        if (true || e->X.av == NOTHING_VALUE) e->X.setRandomAvValue();

        setH_19(*e);
        setSubstractureZ_16(*e);
        setA_17(*e);
        set_18(*e);
        set_20(*e);
        set_21(*e);
        set_22(*e);
        set_23(*e);
        set_24(*e);
        set_25(*e);
        set_26(*e);
    }
}

void SMainClass::setSubstractureZ_16(SBlockData &block)
{
    if (block.is_hull)
    {
        block.Z = 0;
        return;
    }

    if (block.HB_H != 0)
    {
        block.Z = blocks[block.HB_H-1]->Z + blocks[block.HB_H-1]->h;
    }
}

void SMainClass::setH_19(SBlockData &block)
{
    block.h = block.K_H.av * general->FB;
}

void SMainClass::setA_17(SBlockData &block)
{
    block.a = block.K_L.av * general->L;
}

void SMainClass::set_18(SBlockData &block)
{
    qreal alpha_F_av = qDegreesToRadians(block.alpha_F.av);
    qreal alpha_A_av = qDegreesToRadians(block.alpha_A.av);
    block.b = my_trunc(block.a - block.h * (qCos(alpha_F_av)/qSin(alpha_F_av) +
                                         qCos(alpha_A_av)/qSin(alpha_A_av)));
}

void SMainClass::set_20(SBlockData &block)
{
    block.S = my_trunc((block.a + block.b)/2*block.h);
}

void SMainClass::set_21(SBlockData &block)
{
    block.M_a = my_trunc(qPow(block.a, 2)/2);
}

void SMainClass::set_22(SBlockData &block)
{
    qreal alpha_F_av = qDegreesToRadians(block.alpha_F.av);
    block.M_b = my_trunc(block.b * (block.h * qCos(alpha_F_av)/qSin(alpha_F_av) + block.b/2));
}

void SMainClass::set_23(SBlockData &block)
{
    block.x_g = my_trunc((block.M_a + block.M_b)/(block.a + block.b)+ block.X.av);
}

void SMainClass::set_24(SBlockData &block)
{
    block.z_g = my_trunc(block.h - block.h/3 * (2* block.b + block.a)/
            (block.a + block.b) + block.Z);
}

void SMainClass::set_25(SBlockData &block)
{
    qreal alpha_A_av = qDegreesToRadians(block.alpha_A.av);
    block.X_U_A = my_trunc(block.X.av + block.a - block.h * qCos(alpha_A_av)/qSin(alpha_A_av));
}

void SMainClass::set_26(SBlockData &block)
{
    qreal alpha_F_av = qDegreesToRadians(block.alpha_F.av);
    block.X_U_F = my_trunc(block.X.av + block.h * qCos(alpha_F_av)/qSin(alpha_F_av));
}

void SMainClass::addBlock()
{
    blocks.push_back(new SBlockData());
    if (blocks.size() == 1)
    {
        blocks[0]->is_hull = true;
    }
}

void SMainClass::restoreSGeneralData()
{
    // clear data;
    general->theta = WHA;
    general->p_w = WIND_PRESSURE;
}
