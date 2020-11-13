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

void SMainClass::addBlock()
{
    blocks.push_back(new SBlockData());
}

void SMainClass::restoreSGeneralData()
{
    // clear data;
    general->wha = WHA;
    general->wind_pressure = WIND_PRESSURE;
}
