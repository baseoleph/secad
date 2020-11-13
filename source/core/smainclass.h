#ifndef SMAINCLASS_H
#define SMAINCLASS_H

#include "sblockdata.h"
#include "sgeneraldata.h"

#include <vector>

typedef  std::vector<SBlockData *> BlocksVector;

class SMainClass : SGeneralData
{
public:
    SMainClass();
    ~SMainClass();

    void addBlock();
    void restoreSGeneralData();
    SGeneralData *general;
    BlocksVector blocks;
};

#endif // SMAINCLASS_H
