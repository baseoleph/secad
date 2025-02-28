﻿// Ship Exterior CAD
// Copyright (C) 2020 baseoleph@gmail.com,
//					  nepryaho@gmail.com

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef SALGORITHM_H
#define SALGORITHM_H

#include <QFile>
#include <QDir>
#include <QRandomGenerator>
#include <random>
#include <QTimer>
#include <QDebug>
#include "typesofoptimizevar.h"
#include "sm_algorithms.h"
#include "sblockdata.h"
#include "sgeneraldata.h"
#include <QObject>

class SAlgorithm : public QObject
{
    Q_OBJECT

public:
    SAlgorithm(BlocksVector new_blocks, SGeneralData *new_general);
    ~SAlgorithm();
    bool optimizationSteps();
    double M = 0;
    int EC_cnt = 0;
    bool onOptimize = false;
    bool stopOpt = false;
    bool goodTry = false;
    QString log_data;

signals:
    void emitUpdateFormulaeSignal();
    void emitStatusBarSignal(const QString str);

private:
    QTimer *timer;
    BlocksVector blocks;
    SGeneralData *general;
    double iterator = 0.001;
    double Y = 0;
    double EC = NOTHING_VALUE;

    int cnt = 0;
    bool is_optimized = false;
    bool super_dis_bool = false;
    bool super_38 = false;
    int cnt_38 = 0;
    bool super_41 = false;
    int cnt_41 = 0;
    bool super_43 = false;
    int cnt_43 = 0;
    bool super_44 = false;
    int cnt_44 = 0;
    bool super_45 = false;
    int cnt_45 = 0;
    bool super_46 = false;
    int cnt_46 = 0;
    bool super_47 = false;
    int cnt_47 = 0;
    bool super_48 = false;
    int cnt_48 = 0;
    bool super_49 = false;
    int cnt_49 = 0;
    bool super_51 = false;
    int cnt_51 = 0;
    bool super_52 = false;
    int cnt_52 = 0;
    bool super_53 = false;
    int cnt_53 = 0;
    bool super_54 = false;
    int cnt_54 = 0;
    bool super_55 = false;
    int cnt_55 = 0;
    void clear_supers();

    void updateEC();
    void updateAV();
    void updateIV();

    bool startChecks();
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
