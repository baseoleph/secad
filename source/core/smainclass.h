#ifndef SMAINCLASS_H
#define SMAINCLASS_H

#include "sblockdata.h"
#include "sgeneraldata.h"
#include <QtMath>
#include <vector>

typedef  std::vector<SBlockData *> BlocksVector;

class SMainClass : SGeneralData
{
public:
    SMainClass();
    ~SMainClass();


    void calculateData();
    void setSubstractureZ_16(SBlockData &block);
    void setH_19(SBlockData &block);
    void setA_17(SBlockData &block);
    void set_18(SBlockData &block);
    void set_20(SBlockData &block);
    void set_21(SBlockData &block);
    void set_22(SBlockData &block);
    void set_23(SBlockData &block);
    void set_24(SBlockData &block);


    void addBlock();
    void restoreSGeneralData();
    SGeneralData *general;
    BlocksVector blocks;
};

#endif // SMAINCLASS_H
