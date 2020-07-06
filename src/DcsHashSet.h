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

#ifndef DCSHASHSET_H
#define DCSHASHSET_H

#define DCSHASHSET_AUXIDX_SIZE(B, C) ((B) + 4*(C))
#define DCSHASHSET_AUXFLAG_SIZE(B, C) ((B) + (C))

#include <stddef.h>
#include "DcsTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * HashSet data container structure with two levels of indexing.
 * The container can store values (V) of size itemsize (L).
 * The container cannot store more values than its capacity (C).
 * Data lookup is accelerated by hash function ($h(x): x \in V => unsigned integer$).
 * DcsHashSet deals with buckets (B). The first level index (bucket index, bidx) of a value is given by $h(x) mod B$.
 * The second level index (slot index, sidx) of the value is its index in the storage array.
 * 
 * In this implementation all the arrays and indices
 * are stored in a raw form (i.e., are not compressed).
 * Auxilliary data requires (3 + 4 * capacity + 1 * buckets) * sizeof(ElementIdx) + (1 * capacity + 1 * buckets) * sizeof(bool) additional space.
 */
typedef struct {
  const ElementSize itemsize;
  // allocated dat slots chained by age
  // for accelerating remove operation
  ElementIdx begin_sidx;
  ElementIdx last_sidx;
  ElementIdx *next_sidx_a;  ///< Length: capacity
  ElementIdx *prev_sidx_a;  ///< Length: capacity

  // per bucket chains
  ElementIdx *bucket_head_sidx_a; ///< Length: buckets
  bool *bucket_head_valid_a;      ///< Length: buckets
  ElementIdx *bucket_next_sidx_a; ///< Length: capacity
  bool *bucket_next_valid_a;      ///< Length: capacity

  // stack of free slots in dat array
  // for accelerating insert operation
  ElementIdx *dat_free_slot_a;    ///< Length: capacity
  ElementIdx dat_free_slot_i;     ///< top of the stack

  // basic container
  const ElementPtr dat;
  const ElementIdx capacity;
  const ElementIdx buckets;
  IntFunction hash;
  ElementRel equals;
} DcsHashSet;

DcsHashSet dcshashset_init(ElementSize, size_t, size_t, const ElementPtr, ElementIdx*, bool*, const IntFunction, const ElementRel);
ElementIdx dcshashset_size(const DcsHashSet*);
bool dcshashset_empty(const DcsHashSet*);
ElementIdx dcshashset_capacity(const DcsHashSet*);
bool dcshashset_full(const DcsHashSet*);

bool dcshashset_insert(DcsHashSet*, const ElementPtr);
bool dcshashset_remove(DcsHashSet*, const ElementPtr);
bool dcshashset_contains(const DcsHashSet*, const ElementPtr);

DcsIterator dcshashset_find(const DcsHashSet*, const ElementPtr);
DcsIterator dcshashset_begin(const DcsHashSet*);
DcsIterator dcshashset_end(const DcsHashSet*);
bool dcshashset_iterator_equals(const DcsHashSet*, const DcsIterator, const DcsIterator);
DcsIterator dcshashset_next_iterator(const DcsHashSet*, const DcsIterator);
ElementPtr dcshashset_deref_iterator(const DcsHashSet*, const DcsIterator);

#ifdef __cplusplus
}
#endif

#endif /* DCSHASHSET_H */

