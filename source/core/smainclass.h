#ifndef SMAINCLASS_H
#define SMAINCLASS_H

#include "sm_algorithms.h"
#include "sblockdata.h"
#include "sgeneraldata.h"
#include "salgorithm.h"
#include "loggingcategories.h"
#include <QtMath>
#include <vector>
#include <QObject>


class SMainClass : public QObject
{
    Q_OBJECT
public:
    SMainClass();
    ~SMainClass();


    void optimizeData();
    void setSubstractureZ_16(SBlockData &block);
    void setH_19(SBlockData &block);
    void setA_17(SBlockData &block);
    void set_18(SBlockData &block);
    void set_20(SBlockData &block);
    void set_21(SBlockData &block);
    void set_22(SBlockData &block);
    void set_23(SBlockData &block);
    void set_24(SBlockData &block);
    void set_25(SBlockData &block);
    void set_26(SBlockData &block);


    void addBlock();
    void restoreSGeneralData();
    SGeneralData *general = nullptr;
    BlocksVector blocks;
    SAlgorithm *alg = nullptr;

public slots:
    void updateFormulaeSlot();
};

#endif // SMAINCLASS_H
