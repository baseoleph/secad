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
