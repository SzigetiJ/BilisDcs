#include "DcsHoF.h"
#include "DcsLinear.h"
#include <string.h>
/**
 * Standard data initializer function.
 * @param itemsize 
 * @param capacity
 * @param dat
 * @param less
 * @return 
 */
DcsHoF dcshof_init(ElementSize elemsize, ElementIdx capacity, const ElementPtr dat, const ElementRel less) {
  DcsHoF retv = {
    {elemsize, capacity, 0, dat}, less
  };
  return retv;
}

ElementIdx dcshof_size(const DcsHoF *a) {
  return dcslinear_size(&a->base);
}

bool dcshof_empty(const DcsHoF *a) {
  return dcslinear_empty(&a->base);
}

ElementIdx dcshof_capacity(const DcsHoF *a) {
  return dcslinear_capacity(&a->base);
}

bool dcshof_full(const DcsHoF *a) {
  return dcslinear_full(&a->base);
}

ElementIdx dcshof_lower_bound(const DcsHoF *a, const ElementPtr b) {
  ElementIdx idx = 0;
  while (idx < a->base.size && a->less(dcslinear_get(&a->base, idx), b)) {
    ++idx;
  }
  return idx;
}

ElementIdx dcshof_insert(DcsHoF *a, const ElementPtr b) {
  const DcsLinear *cab = &a->base;
  ElementIdx idx = dcshof_lower_bound(a, b);

  if (idx < a->base.capacity) {
    if (a->base.size < a->base.capacity) {
      ++a->base.size;
    }
    for (size_t i = a->base.size - 1; idx < i; --i) {
      dcslinear_set(cab, i, dcslinear_get(cab, i - 1));
    }
    dcslinear_set(cab, idx, b);
  }
  return a->base.size;
}

ElementPtr dcshof_get(const DcsHoF *a, ElementIdx i) {
  return dcslinear_get(&a->base, i);
}

