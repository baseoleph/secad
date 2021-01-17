// Ship Exterior CAD
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

#ifndef SMAINCLASS_H
#define SMAINCLASS_H

#include "sm_algorithms.h"
#include "sblockdata.h"
#include "sgeneraldata.h"
#include "salgorithm.h"
#include <QtMath>
#include <vector>
#include <QObject>


class SMainClass : public QObject
{
    Q_OBJECT
public:
    SMainClass();
    ~SMainClass();


    void prepareToOptimize();
    void setSubstractureZ_16(SBlockData &block);
    void setH_19(SBlockData &block);
    void setA_17(SBlockData &block);
    void set_18(SBlockData &block);
    void set_20(SBlockData &block);
    void set_21(SBlockData &block);
    void set_22(SBlockData &block);
    void set_x(SBlockData &block);
    void set_23(SBlockData &block);
    void set_24(SBlockData &block);
    void set_25(SBlockData &block);
    void set_26(SBlockData &block);


    void addBlock();
    void restoreSGeneralData();
    SGeneralData *general = nullptr;
    BlocksVector blocks;
    SAlgorithm *alg = nullptr;

signals:
    void emitStatusBarSignal(const QString str);

public slots:
    void updateFormulaeSlot();

private slots:
    void statusBarSlot(const QString str);
};

#endif // SMAINCLASS_H
