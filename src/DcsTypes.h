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
#ifndef DCSTYPES_H
#define DCSTYPES_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef size_t ElementSize;
typedef size_t ElementIdx;
typedef size_t DcsIterator;

typedef unsigned char* ElementPtr;
typedef bool (*ElementRel)(ElementPtr, ElementPtr);

typedef struct DcsLinear_ DcsLinear;

#ifdef __cplusplus
}
#endif

#endif /* DCSTYPES_H */

