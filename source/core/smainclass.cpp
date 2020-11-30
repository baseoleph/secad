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

void SMainClass::calculateData()
{
    foreach (auto e, blocks)
    {
        if (true || e->hrc.av == NOTHING_VALUE) e->hrc.setRandomAvValue();
        if (true || e->lrc.av == NOTHING_VALUE) e->lrc.setRandomAvValue();
        if (true || e->fwih.av == NOTHING_VALUE) e->fwih.setRandomAvValue();
        if (true || e->awih.av == NOTHING_VALUE) e->awih.setRandomAvValue();
        if (true || e->x.av == NOTHING_VALUE) e->x.setRandomAvValue();

        setH_19(*e);
        setSubstractureZ_16(*e);
        setA_17(*e);
        set_18(*e);
        set_20(*e);
        set_21(*e);
        set_22(*e);
        set_23(*e);
        set_24(*e);
    }
}

void SMainClass::setSubstractureZ_16(SBlockData &block)
{
    if (block.is_hull)
    {
        block.z = 0;
        return;
    }

    if (block.hb_h != 0)
    {
        block.z = blocks[block.hb_h-1]->z + blocks[block.hb_h-1]->h;
    }
}

void SMainClass::setH_19(SBlockData &block)
{
    block.h = block.hrc.av + general->freeboard;
}

void SMainClass::setA_17(SBlockData &block)
{
    block.bb_l = block.lrc.av + general->length;
}

void SMainClass::set_18(SBlockData &block)
{
    block.bb_u = block.bb_l - block.h * (qCos(block.fwih.av)/qSin(block.fwih.av) +
                                         qCos(block.awih.av)/qSin(block.awih.av));
}

void SMainClass::set_20(SBlockData &block)
{
    block.s = (block.bb_l + block.bb_u)/2*block.h;
}

void SMainClass::set_21(SBlockData &block)
{
    block.m_a = qPow(block.bb_l, 2)/2;
}

void SMainClass::set_22(SBlockData &block)
{
    block.m_b = block.bb_u * (block.h * qCos(block.awih.av)/qSin(block.awih.av) + block.bb_u/2);
}

void SMainClass::set_23(SBlockData &block)
{
    block.x_g = (block.m_a + block.m_b)/(block.bb_l + block.bb_u)+ block.x.av;
}

void SMainClass::set_24(SBlockData &block)
{
    block.z_g = block.h - block.h/3 * (2* block.bb_u + block.bb_l)/
                                        (block.bb_l + block.bb_u) + block.z;
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
    general->wha = WHA;
    general->wind_pressure = WIND_PRESSURE;
}
