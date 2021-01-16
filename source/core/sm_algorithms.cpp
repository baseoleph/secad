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

#include "sm_algorithms.h"

double my_trunc(double d)
{
    return  std::trunc(d * PRECISION) / PRECISION;
}

double my_ctg(double val_in_degrees)
{
    double val_in_rad = qDegreesToRadians(val_in_degrees);
    double ctg_val = qCos(val_in_rad)/qSin(val_in_rad);
    return ctg_val;
}
