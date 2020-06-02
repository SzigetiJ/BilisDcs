#ifndef _DCS_HOF_H_
#define _DCS_HOF_H_

#include <stddef.h>
#include "DcsTypes.h"
#include "DcsLinear.h"

typedef struct {
  DcsLinear base;
  ElementRel less;
} DcsHoF;

DcsHoF dcshof_init(ElementSize, size_t, const ElementPtr, const ElementRel);
ElementIdx dcshof_size(const DcsHoF*);
bool dcshof_empty(const DcsHoF*);
ElementIdx dcshof_capacity(const DcsHoF*);
bool dcshof_full(const DcsHoF*);
ElementIdx dcshof_lower_bound(const DcsHoF*, const ElementPtr);
ElementIdx dcshof_insert(DcsHoF*, const ElementPtr);
ElementPtr dcshof_get(const DcsHoF*, ElementIdx);

#endif // _DCS_HOF_H_

