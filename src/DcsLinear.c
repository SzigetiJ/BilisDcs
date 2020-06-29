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
#include "DcsLinear.h"
#include <string.h>

DcsLinear dcslinear_init(ElementSize elemsize, ElementIdx capacity, const ElementPtr dat) {
    DcsLinear retv = {elemsize, capacity, 0, dat};
    return retv;
}

ElementIdx dcslinear_size(const DcsLinear *a) {
    return a->size;
}

bool dcslinear_empty(const DcsLinear *a) {
    return a->size == 0;
}

ElementIdx dcslinear_capacity(const DcsLinear *a) {
    return a->capacity;
}

bool dcslinear_full(const DcsLinear *a) {
    return a->size == a->capacity;
}

ElementPtr dcslinear_get(const DcsLinear *a, ElementIdx i) {
    return a->dat + i * a->itemsize;
}

void dcslinear_set(const DcsLinear *a, ElementIdx i, const ElementPtr b) {
    memcpy(dcslinear_get(a, i), b, a->itemsize);
}

void dcslinear_copy_to(const DcsLinear *a, ElementIdx i, ElementPtr b) {
    memcpy(b, dcslinear_get(a, i), a->itemsize);
}

DcsIterator dcslinear_begin(const DcsLinear *a) {
  return 0;
}

DcsIterator dcslinear_end(const DcsLinear *a) {
  return a->size;
}

bool dcslinear_iterator_equals(const DcsLinear *a, const DcsIterator it0, const DcsIterator it1) {
  return it0 == it1;
}

DcsIterator dcslinear_next_iterator(const DcsLinear *a, const DcsIterator it) {
  return it + 1;
}

void dcslinear_inc_iterator(const DcsLinear *a, DcsIterator *it) {
  ++*it;
}

ElementPtr dcslinear_deref_iterator(const DcsLinear *a, const DcsIterator it) {
  return a->dat + it;
}
