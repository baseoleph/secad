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

#include "typesofoptimizevar.h"

TypesOfOptimizeVar::TypesOfOptimizeVar()
{

}

void TypesOfOptimizeVar::setRandomAvValue()
{
    QRandomGenerator rand = QRandomGenerator();

    if (type == CONS)
    {
        av = cons;
    }
    else if (type == CONT)
    {
        av = cons;
        double frac = rand.global()->generateDouble();
        if ((int)cont_min == (int)cont_max)
        {
            av = frac;
        }
        else
        {
            av = rand.global()->bounded((int)cont_min, (int)cont_max) + frac;
        }
    }
    else if (type == DISC)
    {
        av_i = rand.global()->bounded((int)0, (int)desc_link.size());
        av = desc_link[av_i];

        iv_i = av_i;
    }
    iv = av;
}
