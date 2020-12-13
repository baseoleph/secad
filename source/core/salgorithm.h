#ifndef SALGORITHM_H
#define SALGORITHM_H

#include <QRandomGenerator>
#include <random>
#include <QDebug>
#include "typesofoptimizevar.h"
#include "sm_algorithms.h"
#include "sblockdata.h"
#include "sgeneraldata.h"
#include "loggingcategories.h"
#include <QObject>

class SAlgorithm : public QObject
{
    Q_OBJECT

public:
    SAlgorithm(BlocksVector new_blocks, SGeneralData *new_general);
    void startOpt();

signals:
    void emitUpdateFormulaeSignal();
    void emitStatusBarSignal(const QString str);

private:
    BlocksVector blocks;
    SGeneralData *general;
    int M = 0;
    double Y = 0;

    bool startChecks();
    bool check_37(SBlockData *e_h, SBlockData *e_s);
    bool check_38(SBlockData *e_h, SBlockData *e_s);
    bool check_41(SBlockData *e);
    bool check_43();
    bool check_44();
    bool check_45(SBlockData *e);
    bool check_46(SBlockData *e);
    bool check_47(SBlockData *e);
    bool check_48(SBlockData *e);
    bool check_49(SBlockData *e);
    bool check_51(SBlockData *e);
    bool check_52(SBlockData *e);
    bool check_53(SBlockData *e);
    bool check_54(SBlockData *e, SBlockData *e_funn);
    bool check_55();
    void optimizationStep();
    double generateRandomForY();

    double functionV_33(double x);
    void optimizeVal(TypesOfOptimizeVar *var);
    void contOpt(TypesOfOptimizeVar *var);
    void discOpt(TypesOfOptimizeVar *var);
    void clearTypesOpt();
};

#endif // SALGORITHM_H
