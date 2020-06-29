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
DcsIterator dcshof_lower_bound(const DcsHoF*, const ElementPtr);
DcsIterator dcshof_insert(DcsHoF*, const ElementPtr);
ElementPtr dcshof_get(const DcsHoF*, ElementIdx);

DcsIterator dcshof_begin(const DcsHoF*);
DcsIterator dcshof_end(const DcsHoF*);
bool dcshof_iterator_equals(const DcsHoF*, const DcsIterator, const DcsIterator);
DcsIterator dcshof_next_iterator(const DcsHoF*, const DcsIterator);
void dcshof_inc_iterator(const DcsHoF*, DcsIterator*);
ElementPtr dcshof_deref_iterator(const DcsHoF*, const DcsIterator);

#endif // _DCS_HOF_H_

