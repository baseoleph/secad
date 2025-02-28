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

#include "smainclass.h"

SMainClass::SMainClass()
{
    general = new SGeneralData();
}

SMainClass::~SMainClass()
{
    delete general;
    foreach (auto e, blocks)
    {
        delete e;
    }
}

void SMainClass::prepareToOptimize()
{
    if (alg != nullptr)
    {
        disconnect(alg, &SAlgorithm::emitUpdateFormulaeSignal, this, &SMainClass::updateFormulaeSlot);
        disconnect(alg, &SAlgorithm::emitStatusBarSignal, this, &SMainClass::statusBarSlot);
        delete alg;
        alg = nullptr;
    }
    alg = new SAlgorithm(blocks, general);
    connect(alg, &SAlgorithm::emitUpdateFormulaeSignal, this, &SMainClass::updateFormulaeSlot);
    connect(alg, &SAlgorithm::emitStatusBarSignal, this, &SMainClass::statusBarSlot);
}

void SMainClass::setSubstractureZ_16(SBlockData &block)
{
    if (block.is_hull)
    {
        block.Z = 0;
        return;
    }

    if (block.HB_H != 0)
    {
        block.Z = blocks[block.HB_H-1]->Z + blocks[block.HB_H-1]->h;
    }
}

void SMainClass::setH_19(SBlockData &block)
{
    block.h = block.K_H.iv * general->FB;
}

void SMainClass::setA_17(SBlockData &block)
{
    block.a = block.K_L.iv * general->L;
}

void SMainClass::set_18(SBlockData &block)
{
    block.b = my_trunc(block.a - block.h * (my_ctg(block.alpha_F.iv) + my_ctg(block.alpha_A.iv)));
}

void SMainClass::set_20(SBlockData &block)
{
    block.S = my_trunc((block.a + block.b)/2 * block.h);
}

void SMainClass::set_21(SBlockData &block)
{
    block.M_a = my_trunc(qPow(block.a, 2)/2);
}

void SMainClass::set_22(SBlockData &block)
{
    block.M_b = my_trunc(block.b * (block.h * my_ctg(block.alpha_F.iv) + block.b/2));
}

void SMainClass::set_x(SBlockData &block)
{
    if (block.HB_L != 0)
    {
        SBlockData *parent_block = blocks[block.HB_L - 1];
        block.X.iv = parent_block->X.iv + parent_block->a + block.L_HB_L;
    }
}

void SMainClass::set_23(SBlockData &block)
{
    block.x_g = my_trunc((block.M_a + block.M_b)/(block.a + block.b)+ block.X.iv);
}

void SMainClass::set_24(SBlockData &block)
{
    block.z_g = my_trunc(block.h - block.h/3 * (2* block.b + block.a)/
            (block.a + block.b) + block.Z);
}

void SMainClass::set_25(SBlockData &block)
{
    block.X_U_A = my_trunc(block.X.iv + block.a - block.h * my_ctg(block.alpha_A.iv));
}

void SMainClass::set_26(SBlockData &block)
{
    block.X_U_F = my_trunc(block.X.iv + block.h * my_ctg(block.alpha_F.iv));
}

void SMainClass::addBlock()
{
    blocks.push_back(new SBlockData());
    if (blocks.size() == 1)
    {
        blocks[0]->is_hull = true;
    }
}

void SMainClass::restoreSGeneralData()
{
    // clear data;
    general->theta = WHA;
    general->p_w = WIND_PRESSURE;
}

void SMainClass::updateFormulaeSlot()
{
    foreach (auto e, blocks)
    {
        setH_19(*e);
        setSubstractureZ_16(*e);
        setA_17(*e);
        set_18(*e);
        set_20(*e);
        set_21(*e);
        set_22(*e);

        set_x(*e);

        set_23(*e);
        set_24(*e);
        set_25(*e);
        set_26(*e);
    }
}

void SMainClass::statusBarSlot(const QString str)
{
    emitStatusBarSignal(str);
}
