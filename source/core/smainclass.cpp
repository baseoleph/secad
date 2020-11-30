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
        if (e->lrc.av == NOTHING_VALUE) e->lrc.setRandomAvValue();
        if (e->fwih.av == NOTHING_VALUE) e->fwih.setRandomAvValue();
        if (e->awih.av == NOTHING_VALUE) e->awih.setRandomAvValue();
        if (e->x.av == NOTHING_VALUE) e->x.setRandomAvValue();
        qDebug() << e->hrc.av;
    }
}

void SMainClass::setSubstractureZ(SBlockData &block)
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
    else
    {
        qDebug() << "hi";
    }
}

void SMainClass::setH(SBlockData &block)
{
//    block.h = block.hrc
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
