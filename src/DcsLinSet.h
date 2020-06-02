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

#ifndef DCSLINSET_H
#define DCSLINSET_H

#include <stddef.h>
#include "DcsTypes.h"
#include "DcsLinear.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set based on an ordered array.
 */
typedef struct {
  DcsLinear base;
  ElementRel less;
} DcsLinSet;

DcsLinSet dcslinset_init(ElementSize, size_t, const ElementPtr, const ElementRel);
ElementIdx dcslinset_size(const DcsLinSet*);
bool dcslinset_empty(const DcsLinSet*);
ElementIdx dcslinset_capacity(const DcsLinSet*);
bool dcslinset_full(const DcsLinSet*);
ElementIdx dcslinset_lower_bound(const DcsLinSet*, const ElementPtr);
ElementIdx dcslinset_insert(DcsLinSet*, const ElementPtr);
bool dcslinset_remove(DcsLinSet*, const ElementPtr);
bool dcslinset_contains(const DcsLinSet*, const ElementPtr);

#ifdef __cplusplus
}
#endif

#endif /* DCSLINSET_H */

