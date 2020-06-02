#ifndef _DCS_LINEAR_H_
#define _DCS_LINEAR_H_

#include <stddef.h>
#include "DcsTypes.h"

struct DcsLinear_ {
 const ElementSize itemsize;
 const ElementIdx capacity;
 ElementIdx size;
 const ElementPtr dat;
};

DcsLinear dcslinear_init(ElementSize, ElementIdx, const ElementPtr);
ElementIdx dcslinear_size(const DcsLinear*);
bool dcslinear_empty(const DcsLinear*);
ElementIdx dcslinear_capacity(const DcsLinear*);
bool dcslinear_full(const DcsLinear*);
void dcslinear_set(const DcsLinear*, ElementIdx, const ElementPtr);
ElementPtr dcslinear_get(const DcsLinear*, ElementIdx);
void dcslinear_copy_to(const DcsLinear*, ElementIdx, ElementPtr);

#endif // _DCS_HOF_H_

