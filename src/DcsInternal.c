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
#include "DcsInternal.h"
#include "DcsLinear.h"

DcsIterator _dcslinear_lower_bound(const DcsLinear *a, const ElementRel less, const ElementPtr b) {
  DcsIterator lo = dcslinear_begin(a);
  DcsIterator hi = dcslinear_end(a);
  // math..
  // here we expoit the fact that DcsIterators are raw data indices
  while (!dcslinear_iterator_equals(a, lo, hi)) {
    ElementIdx mid = (lo + hi) / 2;
    if (less(dcslinear_deref_iterator(a, mid), b)) {
      lo = (lo==mid) ? (lo + 1) : mid;
    } else {
      hi = mid;
    }
  }
  return lo;
}
