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
#include <stdio.h>

/**
 * Finds the place of an element in the hashset.
 * The output of the function is a pair of pointers:
 * **slot_occupied_wptr -- the pointed value is the place in the bucket chain
 * where it is denoted whether the element is member of the hashset;
 * **slot_idx_wptr -- the pointed value is the place in the bucket chain
 * where the slot of the element is stored.
 * Of course, if **slot_occupied_wptr is false, the value of **slot_idx_wptr is invalid.
 * In case of element insert / remove operations the invoking function has to modify
 * the bucket chaining, hence it requires write access to the memory where slot_occupation
 * and slot_idx are stored. That is why these parameters are wptrs (write-pointers).
 */
static void _internal_find(const DcsHashSet *a, const ElementPtr b, ElementIdx **slot_idx_wptr, bool **slot_occupied_wptr) {
  ElementIdx hx = (a->hash(b)) % a->buckets;
  *slot_occupied_wptr = a->bucket_head_valid_a + hx;
  *slot_idx_wptr = a->bucket_head_sidx_a + hx;
  while (**slot_occupied_wptr) {
    if (a->equals(a->dat + **slot_idx_wptr * a->itemsize, b)) {
      break;
    }
    *slot_occupied_wptr = a->bucket_next_valid_a + **slot_idx_wptr;
    *slot_idx_wptr = a->bucket_next_sidx_a + **slot_idx_wptr;
  }
}


/**
 * Standard data initializer function.
 * @param itemsize Size of the stored element type in bytes.
 * @param capacity Capacity of the storage in number of elements.
 * @param buckets Number of hash buckets.
 * @param dat Memory area of the storage. Must be of size itemsize * capacity [bytes].
 * @param aux_idx_a Auxilliary indixes are stored here. Must be of size (4*capacity + 1*buckets) [ElementIdx].
 * @param aux_flag_a Validity of indices are denoted here. Must be of size capacity + buckets [bool].
 * @param hash Hash function used to map elements into buckets.
 * @param equals Checks equality of two elements. Used to distinguish between elements mapped into the same bucket.
 * @return Constructed and initialized HashSet stucture.
 */
DcsHashSet dcshashset_init(
        ElementSize itemsize, size_t capacity, size_t buckets,
        const ElementPtr dat,
        ElementIdx *aux_idx_a, bool *aux_flag_a,
        const IntFunction hash, const ElementRel equals) {
  DcsHashSet retv = {
    .itemsize = itemsize,

    .begin_sidx = capacity,
    .last_sidx = capacity,

    .next_sidx_a = aux_idx_a,
    .prev_sidx_a = aux_idx_a + capacity,

    .bucket_head_sidx_a = aux_idx_a + (2 * capacity),
    .bucket_head_valid_a = aux_flag_a,
    .bucket_next_sidx_a = aux_idx_a + (2 * capacity + 1 * buckets),
    .bucket_next_valid_a = aux_flag_a + buckets,

    retv.dat_free_slot_a = aux_idx_a + (3 * capacity + 1 * buckets),
    .dat_free_slot_i = capacity,

    .dat = dat,
    .capacity = capacity,
    .buckets = buckets,
    .hash = hash,
    .equals = equals
  };
  memset(retv.bucket_head_valid_a, 0, buckets * sizeof (bool));
  memset(retv.bucket_next_valid_a, 0, capacity * sizeof (bool));
  for (ElementIdx i = 0; i < capacity; ++i) {
    retv.dat_free_slot_a[i] = capacity - i - 1;
  }
  return retv;
}

/**
 * Reports the actual size (number of contained elements) of the set.
 */
ElementIdx dcshashset_size(const DcsHashSet *a) {
  return a->capacity - a->dat_free_slot_i;
}

/**
 * Tells whether the set is empty.
 */
bool dcshashset_empty(const DcsHashSet *a) {
  return a->capacity == a->dat_free_slot_i;
}

/**
 * Reports the constant capacity of the set.
 */
ElementIdx dcshashset_capacity(const DcsHashSet *a) {
  return a->capacity;
}

/**
 * Tells whether the set is full (its size has reached its capacity).
 */
bool dcshashset_full(const DcsHashSet *a) {
  return a->dat_free_slot_i == 0;
}

/**
 * Inserts (copies) an element into the set.
 * Preconditions:
 * 1.) The element is not member of the set.
 * 2.) The set is not full.
 * @return Success - the element has been inserted into the set.
 */
bool dcshashset_insert(DcsHashSet *a, const ElementPtr b) {
  if (dcshashset_full(a))
    return false;
  ElementIdx *slot_idx_wptr;
  bool *slot_occupied_wptr;
  _internal_find(a, b, &slot_idx_wptr, &slot_occupied_wptr);
  if (*slot_occupied_wptr) {
    return false;
  }

  // get a free slot
  --a->dat_free_slot_i;
  ElementIdx slot_idx = a->dat_free_slot_a[a->dat_free_slot_i];

  // put data into the bucket
  *slot_occupied_wptr = true;
  *slot_idx_wptr = slot_idx;
  memcpy(a->dat + slot_idx * a->itemsize, b, a->itemsize);

  // chaining by age
  if (a->last_sidx == a->capacity) { // first element is being inserted
    a->begin_sidx = slot_idx;
    a->prev_sidx_a[slot_idx] = a->capacity;
    a->last_sidx = slot_idx;
  } else {
    a->next_sidx_a[a->last_sidx] = slot_idx;
    a->prev_sidx_a[slot_idx] = a->last_sidx;
    a->last_sidx = slot_idx;
  }
  a->next_sidx_a[slot_idx] = a->capacity;
  return true;
}

/**
 * Removes an element from the set.
 * Preconditions:
 * 1.) The element must be member of the set.
 * Postconditions:
 * 1.) Iterators to the removed element become invalid.
 * @return Success -- the element was found and removed from the set.
 */
bool dcshashset_remove(DcsHashSet *a, const ElementPtr b) {
  ElementIdx slot_idx;
  ElementIdx *slot_idx_wptr;
  bool *slot_occupied_wptr;
  _internal_find(a, b, &slot_idx_wptr, &slot_occupied_wptr);
  if (*slot_occupied_wptr == false) {
    return false;
  }
  slot_idx = *slot_idx_wptr;

  // bucket
  *slot_idx_wptr = a->bucket_next_sidx_a[slot_idx];
  *slot_occupied_wptr = a->bucket_next_valid_a[slot_idx];

  // free slots
  a->dat_free_slot_a[a->dat_free_slot_i++]=slot_idx;

  // chaining by age
  ElementIdx *next_wptr = (slot_idx == a->begin_sidx) ? &a->begin_sidx : (a->next_sidx_a + a->prev_sidx_a[slot_idx]);
  ElementIdx *prev_wptr = (slot_idx == a->last_sidx) ? &a->last_sidx : (a->prev_sidx_a + a->next_sidx_a[slot_idx]);
  *next_wptr = a->next_sidx_a[slot_idx];
  *prev_wptr = a->prev_sidx_a[slot_idx];

  return true;
}

/**
 * Tells whether an element is member of the set.
 */
bool dcshashset_contains(const DcsHashSet *a, const ElementPtr b) {
  ElementIdx *slot_idx_wptr;
  bool *slot_occupied_wptr;
  _internal_find(a, b, &slot_idx_wptr, &slot_occupied_wptr);
  return *slot_occupied_wptr;
}

/**
 * Finds an element within the set.
 * @return Success: iterator to the element; Failure: end iterator.
 */
DcsIterator dcshashset_find(const DcsHashSet *a, const ElementPtr b) {
  ElementIdx *slot_idx_wptr;
  bool *slot_occupied_wptr;
  _internal_find(a, b, &slot_idx_wptr, &slot_occupied_wptr);
  return *slot_occupied_wptr?*slot_idx_wptr:a->capacity;
}

/**
 * @return Iterator to the first element (by age).
 */
DcsIterator dcshashset_begin(const DcsHashSet *a) {
  return a->begin_sidx;
}

/**
 * @return Iterator to the first after the last element.
 */
DcsIterator dcshashset_end(const DcsHashSet *a) {
  return a->capacity;
}

/**
 * Equality check of two iterators. Usually, reaching the end-iterator is checked in conventional for-loops.
 */
bool dcshashset_iterator_equals(const DcsHashSet *a, const DcsIterator it0, const DcsIterator it1) {
  return it0 == it1;
}

/**
 * Tells the successor of an iterator.
 */
DcsIterator dcshashset_next_iterator(const DcsHashSet *a, const DcsIterator it) {
  return a->next_sidx_a[it];
}

/**
 * Gives access to the stored element associated by the iterator.
 */
ElementPtr dcshashset_deref_iterator(const DcsHashSet *a, const DcsIterator it) {
  return a->dat + (a->itemsize * it);
}
