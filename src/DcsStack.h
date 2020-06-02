#ifndef _DCS_STACK_H_
#define _DCS_STACK_H_

#include <stddef.h>
#include "DcsTypes.h"

typedef DcsLinear DcsStack;

DcsStack dcsstack_init(ElementSize, ElementIdx, const ElementPtr);
ElementIdx dcsstack_size(const DcsStack*);
bool dcsstack_empty(const DcsStack*);
ElementIdx dcsstack_capacity(const DcsStack*);
bool dcsstack_full(const DcsStack*);
ElementIdx dcsstack_push(DcsStack*, const ElementPtr);
ElementPtr dcsstack_pop(DcsStack*);

#endif // _DCS_STACK_H_

