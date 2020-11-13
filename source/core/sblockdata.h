#ifndef SBLOCKDATA_H
#define SBLOCKDATA_H

#include "svarparent.h"
#include <vector>

class SBlockData
{
public:
    SBlockData();

    std::vector<SVarParent *> optimize_vect;
};

#endif // SBLOCKDATA_H
