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
#include "DcsLinSet.h"
#include "DcsLinear.h"
#include "DcsInternal.h"
#include <string.h>

/**
 * Standard data initializer function.
 * @param itemsize 
 * @param capacity
 * @param dat
 * @param less
 * @return 
 */
DcsLinSet dcslinset_init(ElementSize elemsize, ElementIdx capacity, const ElementPtr dat, const ElementRel less) {
  DcsLinSet retv = {
    {elemsize, capacity, 0, dat}, less
  };
  return retv;
}

/**
 * Wrapper to dcslinear_size().
 * Tells the occupied size of the container (number of valid elements).
 * @param a Subject of the function.
 * @return Number of valid elements in the container.
 */
ElementIdx dcslinset_size(const DcsLinSet *a) {
  return dcslinear_size(&a->base);
}

/**
 * Wrapper to dcslinear_empty().
 * @param a Subject of the function.
 * @return The container is empty.
 */
bool dcslinset_empty(const DcsLinSet *a) {
  return dcslinear_empty(&a->base);
}

/**
 * Wrapper to dcslinear_capacity().
 * @param a Subject of the function.
 * @return How many elements can be stored in the container.
 */
ElementIdx dcslinset_capacity(const DcsLinSet *a) {
  return dcslinear_capacity(&a->base);
}

/**
 * Wrapper to dcslinear_full().
 * @param a Subject of the function.
 * @return The container is full.
 */
bool dcslinset_full(const DcsLinSet *a) {
  return dcslinear_full(&a->base);
}

/**
 * Finds the suitable insert point for an item in an ordered array.
 * @param a The container.to examine.
 * @param b The item for which the insert point must be found.
 * @return The first element index in the container so that the underlying element
 * is not before the given item /size of the container, if no suitable insert point was found/.
 */
ElementIdx dcslinset_lower_bound(const DcsLinSet *a, const ElementPtr b) {
  return _dcslinear_lower_bound(&a->base, a->less, b);
}

/**
 * Inserts an item into the ordered container.
 * All the elements after the insert point are shifted to the next index.
 * If the size of the container after the insert would be greater than the
 * capacity of the container, the last element is dropped.
 * If the item to insert would be inserted after the last element and the
 * container is already full, the item is dropped.
 * @param a The container to extend.
 * @param b The item to insert.
 * @return 
 */
ElementIdx dcslinset_insert(DcsLinSet *a, const ElementPtr b) {
  const DcsLinear *cab = &a->base;
  if (dcslinear_full(cab)) {
    return cab->capacity;
  }
  ElementIdx idx = dcslinset_lower_bound(a, b);
  if (idx < cab->size && !a->less(b, dcslinear_get(cab, idx))) {
    // a already contains b
  } else {
    for (size_t i = a->base.size - 1; idx < i; --i) {
      dcslinear_set(cab, i, dcslinear_get(cab, i - 1));
    }
    dcslinear_set(cab, idx, b);
    ++a->base.size;
  }
  return idx;
}

bool dcslinset_remove(DcsLinSet *a, const ElementPtr b) {
  ElementIdx idx = dcslinset_lower_bound(a, b);
  bool retv = (idx != a->base.size);
  if (retv) {
    const DcsLinear *cab = &a->base;
    for (ElementIdx i = idx; i < cab->size - 1; ++i) {
      dcslinear_set(cab, i, dcslinear_get(cab, i + 1));
    }
    --a->base.size;
  }
  return retv;
}

bool dcslinset_contains(const DcsLinSet *a, const ElementPtr b) {
  ElementIdx idx = dcslinset_lower_bound(a, b);
  return (
          idx != a->base.size
          && !a->less(b, dcslinear_get(&a->base, idx))
          );
}

DcsIterator dcslinset_begin(const DcsLinSet *a) {
  return dcslinear_begin(&a->base);
}

DcsIterator dcslinset_end(const DcsLinSet *a) {
  return dcslinear_end(&a->base);
}

bool dcslinset_iterator_equals(const DcsLinSet *a, const DcsIterator it0, const DcsIterator it1) {
  return dcslinear_iterator_equals(&a->base, it0, it1);
}

DcsIterator dcslinset_next_iterator(const DcsLinSet *a, const DcsIterator it) {
  return dcslinear_next_iterator(&a->base, it);
}

ElementPtr dcslinset_deref_iterator(const DcsLinSet *a, const DcsIterator it) {
  return dcslinear_deref_iterator(&a->base, it);
}
