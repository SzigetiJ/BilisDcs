/*****************************************************************************

    Copyright 2020 SZIGETI János

    This file is part of bilisdcs library (Data Container Structures).

    BilisDcs is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Biguint is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*****************************************************************************/
#ifndef _DCS_HOF_H_
#define _DCS_HOF_H_

#include <stddef.h>
#include "DcsTypes.h"
#include "DcsLinear.h"

typedef struct {
  DcsLinear base;
  ElementRel less;
} DcsHoF;

DcsHoF dcshof_init(ElementSize, size_t, const ElementPtr, const ElementRel);
ElementIdx dcshof_size(const DcsHoF*);
bool dcshof_empty(const DcsHoF*);
ElementIdx dcshof_capacity(const DcsHoF*);
bool dcshof_full(const DcsHoF*);
ElementIdx dcshof_lower_bound(const DcsHoF*, const ElementPtr);
ElementIdx dcshof_insert(DcsHoF*, const ElementPtr);
ElementPtr dcshof_get(const DcsHoF*, ElementIdx);

#endif // _DCS_HOF_H_

