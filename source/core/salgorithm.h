#ifndef SALGORITHM_H
#define SALGORITHM_H

#include <QRandomGenerator>
#include <random>
#include <QDebug>
#include "typesofoptimizevar.h"
#include "sm_algorithms.h"
#include "sblockdata.h"
#include "loggingcategories.h"
#include <QObject>

class SAlgorithm : public QObject
{
    Q_OBJECT

public:
    SAlgorithm(BlocksVector new_blocks);
    void startOpt();

signals:
    void emitUpdateFormulaeSignal();
    void emitStatusBarSignal(const QString str);

private:
    BlocksVector blocks;
    int M = 0;
    double Y = 0;

    void startChecks();
    bool check_41(SBlockData *e);
    bool check_42(SBlockData *e);
    bool check_43(SBlockData *e);
    bool check_44(SBlockData *e);
    bool check_45(SBlockData *e);
    bool check_46(SBlockData *e);
    bool check_47(SBlockData *e);
    bool check_48(SBlockData *e);
    bool check_49(SBlockData *e);
    bool check_50(SBlockData *e);
    bool check_51(SBlockData *e);
    bool check_52(SBlockData *e);
    bool check_53(SBlockData *e);
    bool check_54(SBlockData *e);
    bool check_55(SBlockData *e);
    void optimizationStep();
    double generateRandomForY();

    void optimizeVal(TypesOfOptimizeVar *var);
    void contOpt(TypesOfOptimizeVar *var);
    void discOpt(TypesOfOptimizeVar *var);
    void clearTypesOpt();
};

#endif // SALGORITHM_H
