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
#include "DcsHashSet.h"
#include <string.h>

/**
 * Standard data initializer function.
 * @param itemsize 
 * @param capacity
 * @param dat
 * @param less
 * @return 
 */
DcsHashSet dcshashset_init(ElementSize size, size_t capacity, const ElementPtr dat, ElementIdx *aux_idx_a, bool *aux_flag_a, const IntFunction hash, const ElementRel equals) {
  DcsHashSet retv = {
    .itemsize = size,

  .begin_idx=capacity,
  .last_idx=capacity,

  .next_idx_a = aux_idx_a,
  .prev_idx_a = aux_idx_a + capacity,

  .bucket_first_idx_a = aux_idx_a + (2 * capacity),
  .bucket_has_first_a = aux_flag_a,
  .bucket_next_idx_a = aux_idx_a + (3 * capacity),
  .bucket_has_next_a = aux_flag_a + capacity,

  retv.dat_free_slot_a = aux_idx_a + (4 * capacity),
  .dat_free_slot_i = capacity,

  .dat = dat,
  .capacity = capacity,
  .hash = hash,
    .equals = equals
  };
  memset(retv.bucket_has_first_a,0,capacity*sizeof(bool));
  memset(retv.bucket_has_next_a,0,capacity*sizeof(bool));
  for (ElementIdx i = 0; i < capacity; ++i) {
    retv.dat_free_slot_a[i] = capacity - i - 1;
  }
  return retv;
}

ElementIdx dcshashset_size(const DcsHashSet *a) {
  return a->capacity - a->dat_free_slot_i;
}

bool dcshashset_empty(const DcsHashSet *a) {
  return a->capacity == a->dat_free_slot_i;
}

ElementIdx dcshashset_capacity(const DcsHashSet *a) {
  return a->capacity;
}

bool dcshashset_full(const DcsHashSet *a) {
  return a->dat_free_slot_i == 0;
}

bool dcshashset_insert(DcsHashSet *a, const ElementPtr b) {
  if (dcshashset_full(a))
    return false;
  ElementIdx hx = (a->hash(b)) % a->capacity;
  bool *slot_occupied_wptr = a->bucket_has_first_a + hx;
  ElementIdx *slot_idx_wptr = a->bucket_first_idx_a + hx;
  while (*slot_occupied_wptr) {
    if (a->equals(a->dat + *slot_idx_wptr * a->itemsize, b)) {
      return false;
    }
    slot_occupied_wptr = a->bucket_has_next_a + *slot_idx_wptr;
    slot_idx_wptr = a->bucket_next_idx_a + *slot_idx_wptr;
  }
  --a->dat_free_slot_i;
  ElementIdx slot_idx = a->dat_free_slot_a[a->dat_free_slot_i];
  *slot_occupied_wptr = true;
  *slot_idx_wptr = slot_idx;
  memcpy(a->dat + slot_idx * a->itemsize, b, a->itemsize);

  if (a->last_idx == a->capacity) { // first element is being inserted
    a->begin_idx = slot_idx;
    a->prev_idx_a[slot_idx] = a->capacity;
    a->last_idx = slot_idx;
  } else {
    a->next_idx_a[a->last_idx] = slot_idx;
    a->prev_idx_a[slot_idx] = a->last_idx;
    a->last_idx = slot_idx;
  }
    a->next_idx_a[slot_idx] = a->capacity;
  return true;
}

// TODO
bool dcshashset_remove(DcsHashSet *a, const ElementPtr b) {
  return false;
}

// TODO
bool dcshashset_contains(const DcsHashSet *a, const ElementPtr b) {
  return false;
}

DcsIterator dcshashset_begin(const DcsHashSet *a) {
  return a->begin_idx;
}

DcsIterator dcshashset_end(const DcsHashSet *a) {
  return a->capacity;
}

bool dcshashset_iterator_equals(const DcsHashSet *a, const DcsIterator it0, const DcsIterator it1) {
  return it0 == it1;
}

DcsIterator dcshashset_next_iterator(const DcsHashSet *a, const DcsIterator it) {
  return a->next_idx_a[it];
}

ElementPtr dcshashset_deref_iterator(const DcsHashSet *a, const DcsIterator it) {
  return a->dat + (a->itemsize * it);
}
