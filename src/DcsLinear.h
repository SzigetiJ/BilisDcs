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

#endif // _DCS_HOF_H_

