#include "DcsHoF.h"
#include <string.h>

DcsHoF dcshof_init(ItemSize itemsize, size_t capacity, const ItemPtr dat, const ItemRel less) {
 DcsHoF retv={itemsize, capacity, 0, dat, less};
 return retv;
}

size_t dcshof_size(const DcsHoF *a) {
 return a->size;
}

size_t dcshof_capacity(const DcsHoF *a) {
 return a->capacity;
}

size_t dcshof_insert(DcsHoF *a, const ItemPtr b) {
 size_t idx = 0;
 ItemPtr ptr = a->dat;
 bool go = true;
 while (go && idx < a->size) {
  bool is_before = a->less(b,ptr);
  if (!is_before) {
   ++idx;
   ptr+=a->itemsize;
  } else {
   go = false;
  }
 }
 if (idx<a->capacity) {
  if (a->size < a->capacity) {
   ++a->size;
  }
  for (size_t i=a->size - 1; idx<i; --i) {
   if (i == a->capacity) {
    continue;	// just forget last item
   }
   memcpy(a->dat+(i*a->itemsize), a->dat + ((i-1)*a->itemsize), a->itemsize);
  }
  memcpy(a->dat + (idx*a->itemsize), b, a->itemsize);
 }
 return a->size;
}

ItemPtr dcshof_get(const DcsHoF *a, size_t i) {
 return (ItemPtr)((int)(a->dat)) + (i*a->itemsize);
}

