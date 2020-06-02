#include "DcsStack.h"
#include "DcsLinear.h"
#include <string.h>

DcsStack dcsstack_init(ElementSize elemsize, ElementIdx capacity, const ElementPtr dat) {
  return dcslinear_init(elemsize, capacity, dat);
}

ElementIdx dcsstack_size(const DcsStack *a) {
  return dcslinear_size(a);
}

bool dcsstack_empty(const DcsStack *a) {
  return dcslinear_empty(a);
}

ElementIdx dcsstack_capacity(const DcsStack *a) {
  return dcslinear_capacity(a);
}

bool dcsstack_full(const DcsStack *a) {
  return dcslinear_full(a);
}

ElementIdx dcsstack_push(DcsStack *a, const ElementPtr b) {
  if (a->size < a->capacity) {
    dcslinear_set(a, a->size, b);
    ++a->size;
  }
  return a->size;
}

ElementPtr dcsstack_pop(DcsStack *a) {
  if (0 < a->size) {
    --a->size;
  }
  return dcslinear_get(a, a->size);
}
