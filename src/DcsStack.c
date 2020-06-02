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
#include "DcsStack.h"
#include "DcsLinear.h"
#include <string.h>

DcsStack dcsstack_init(ElementSize elemsize, ElementIdx capacity, const ElementPtr dat) {
  return dcslinear_init(elemsize, capacity, dat);
}

ElementIdx dcsstack_size(const DcsStack *a) {
  return dcslinear_size(a);
}

bool dcsstack_empty(const DcsStack *a) {
  return dcslinear_empty(a);
}

ElementIdx dcsstack_capacity(const DcsStack *a) {
  return dcslinear_capacity(a);
}

bool dcsstack_full(const DcsStack *a) {
  return dcslinear_full(a);
}

ElementIdx dcsstack_push(DcsStack *a, const ElementPtr b) {
  if (a->size < a->capacity) {
    dcslinear_set(a, a->size, b);
    ++a->size;
  }
  return a->size;
}

ElementPtr dcsstack_pop(DcsStack *a) {
  if (0 < a->size) {
    --a->size;
  }
  return dcslinear_get(a, a->size);
}
