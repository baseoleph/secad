#ifndef SALGORITHM_H
#define SALGORITHM_H

#include <QRandomGenerator>
#include <random>
#include <QTimer>
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
    ~SAlgorithm();
    void startOpt();

signals:
    void emitUpdateFormulaeSignal();
    void emitStatusBarSignal(const QString str);

private:
    QTimer *timer;
    BlocksVector blocks;
    SGeneralData *general;
    double M = 0;
    double iterator = 0.001;
    double Y = 0;
    double EC = NOTHING_VALUE;
    int EC_cnt = 0;
    int cnt = 0;
    bool is_optimized = false;
    bool super_dis_bool = false;
    bool super_37 = false;
    bool super_38 = false;
    bool super_41 = false;
    bool super_43 = false;
    bool super_44 = false;
    bool super_45 = false;
    bool super_46 = false;
    bool super_47 = false;
    bool super_48 = false;
    bool super_49 = false;
    bool super_51 = false;
    bool super_52 = false;
    bool super_53 = false;
    bool super_54 = false;
    bool super_55 = false;
    void clear_supers();

    void updateEC();
    void updateAV();
    void updateIV();

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
    void step();
    double generateRandomForY();

    double functionV_33(double x);
    void optimizeVal(TypesOfOptimizeVar *var);
    void contOpt(TypesOfOptimizeVar *var);
    void discOpt(TypesOfOptimizeVar *var);
    void clearTypesOpt();
};

#endif // SALGORITHM_H
