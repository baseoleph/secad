#ifndef SVARPARENT_H
#define SVARPARENT_H

#include "varclasses/scontinuousvar.h"
#include "varclasses/sconstantvar.h"
#include "varclasses/sdiscretevar.h"

enum {
CONS,
CONT,
DISC
};

struct var_values{
    SConstantVar cons;
    SContinuousVar cont;
    SDiscreteVar disc;
};

class SVarParent
{
public:
    SVarParent();
    void setType(int type);
    int getInt(int type);

    int type = 0;
    SConstantVar constant;
    SDiscreteVar discrete;
    SContinuousVar continuous;
};

#endif // SVARPARENT_H
