#include "DcsLinear.h"
#include <string.h>

DcsLinear dcslinear_init(ElementSize elemsize, ElementIdx capacity, const ElementPtr dat) {
    DcsLinear retv = {elemsize, capacity, 0, dat};
    return retv;
}

ElementIdx dcslinear_size(const DcsLinear *a) {
    return a->size;
}

bool dcslinear_empty(const DcsLinear *a) {
    return a->size == 0;
}

ElementIdx dcslinear_capacity(const DcsLinear *a) {
    return a->capacity;
}

bool dcslinear_full(const DcsLinear *a) {
    return a->size == a->capacity;
}

ElementPtr dcslinear_get(const DcsLinear *a, ElementIdx i) {
    return a->dat + i * a->itemsize;
}

void dcslinear_set(const DcsLinear *a, ElementIdx i, const ElementPtr b) {
    memcpy(dcslinear_get(a, i), b, a->itemsize);
}

void dcslinear_copy_to(const DcsLinear *a, ElementIdx i, ElementPtr b) {
    memcpy(b, dcslinear_get(a, i), a->itemsize);
}
