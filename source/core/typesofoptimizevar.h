// Ship Exterior CAD
// Copyright (C) 2020 baseoleph@gmail.com,
//					  github.com/RoninHikami

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

#ifndef TYPESOFOPTIMIZEVAR_H
#define TYPESOFOPTIMIZEVAR_H

#include "sconstants.h"
#include <vector>
#include <algorithm>
#include <iomanip>
#include <QDebug>
#include <QRandomGenerator>

typedef std::vector<double> d_vector;

class TypesOfOptimizeVar
{
public:
    TypesOfOptimizeVar();
    int type = CONS;
    double cons = NOTHING_VALUE;
    double cont_min = NOTHING_VALUE;
    double cont_max = NOTHING_VALUE;

    double av = NOTHING_VALUE;
    int av_i = NOTHING_VALUE;

    double iv = NOTHING_VALUE;
    int iv_i = NOTHING_VALUE;

    bool is_golden_section = false;

    d_vector desc_link;
    d_vector desc_not_gs;

    void setRandomAvValue();
};

#endif // TYPESOFOPTIMIZEVAR_H
