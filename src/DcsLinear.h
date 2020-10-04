/*****************************************************************************

    Copyright 2020 SZIGETI János

    This file is part of bilisdcs library (Data Container Structures).

    BilisDcs is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    BilisDcs is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*****************************************************************************/
#ifndef _DCS_LINEAR_H_
#define _DCS_LINEAR_H_

#include <stddef.h>
#include "DcsTypes.h"

struct DcsLinear_ {
 const ElementSize itemsize;
 const ElementIdx capacity;
 ElementIdx size;
 const ElementPtr dat;
};

DcsLinear dcslinear_init(ElementSize, ElementIdx, const ElementPtr);
ElementIdx dcslinear_size(const DcsLinear*);
bool dcslinear_empty(const DcsLinear*);
ElementIdx dcslinear_capacity(const DcsLinear*);
bool dcslinear_full(const DcsLinear*);
void dcslinear_set(const DcsLinear*, ElementIdx, const ElementPtr);
ElementPtr dcslinear_get(const DcsLinear*, ElementIdx);
void dcslinear_copy_to(const DcsLinear*, ElementIdx, ElementPtr);

DcsIterator dcslinear_begin(const DcsLinear*);
DcsIterator dcslinear_end(const DcsLinear*);
bool dcslinear_iterator_equals(const DcsLinear*, const DcsIterator, const DcsIterator);
DcsIterator dcslinear_next_iterator(const DcsLinear*, const DcsIterator);
void dcslinear_inc_iterator(const DcsLinear*, DcsIterator*);
ElementPtr dcslinear_deref_iterator(const DcsLinear*, const DcsIterator);

#endif // _DCS_LINEAR_H_

