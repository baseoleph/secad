#include "smainclass.h"

SMainClass::SMainClass()
{
    general = new SGeneralData();
}

SMainClass::~SMainClass()
{
    delete general;
}

void SMainClass::restoreSGeneralData()
{
    // clear data;
    general->wha = 15;
    general->wind_pressure = 1200;
}
