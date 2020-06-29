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
#ifndef _DCS_STACK_H_
#define _DCS_STACK_H_

#include <stddef.h>
#include "DcsTypes.h"

typedef DcsLinear DcsStack;

DcsStack dcsstack_init(ElementSize, ElementIdx, const ElementPtr);
ElementIdx dcsstack_size(const DcsStack*);
bool dcsstack_empty(const DcsStack*);
ElementIdx dcsstack_capacity(const DcsStack*);
bool dcsstack_full(const DcsStack*);
DcsIterator dcsstack_push(DcsStack*, const ElementPtr);
ElementPtr dcsstack_pop(DcsStack*);

DcsIterator dcsstack_begin(const DcsStack*);
DcsIterator dcsstack_end(const DcsStack*);
bool dcsstack_iterator_equals(const DcsStack*, const DcsIterator, const DcsIterator);
DcsIterator dcsstack_next_iterator(const DcsStack*, const DcsIterator);
ElementPtr dcsstack_deref_iterator(const DcsStack*, const DcsIterator);

#endif // _DCS_STACK_H_

