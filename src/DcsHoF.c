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

/**
 * Wrapper to dcslinear_size().
 * Tells the occupied size of the container (number of valid elements).
 * @param a Subject of the function.
 * @return Number of valid elements in the container.
 */
ElementIdx dcshof_size(const DcsHoF *a) {
  return dcslinear_size(&a->base);
}

/**
 * Wrapper to dcslinear_empty().
 * @param a Subject of the function.
 * @return The container is empty.
 */
bool dcshof_empty(const DcsHoF *a) {
  return dcslinear_empty(&a->base);
}

/**
 * Wrapper to dcslinear_capacity().
 * @param a Subject of the function.
 * @return How many elements can be stored in the container.
 */
ElementIdx dcshof_capacity(const DcsHoF *a) {
  return dcslinear_capacity(&a->base);
}

/**
 * Wrapper to dcslinear_full().
 * @param a Subject of the function.
 * @return The container is full.
 */
bool dcshof_full(const DcsHoF *a) {
  return dcslinear_full(&a->base);
}

/**
 * Finds the suitable insert point for an item in an ordered array.
 * @param a The container.to examine.
 * @param b The item for which the insert point must be found.
 * @return The first element index in the container so that the underlying element
 * is not before the given item /size of the container, if no suitable insert point was found/.
 */
ElementIdx dcshof_lower_bound(const DcsHoF *a, const ElementPtr b) {
  ElementIdx idx = 0;
  while (idx < a->base.size && a->less(dcslinear_get(&a->base, idx), b)) {
    ++idx;
  }
  return idx;
}

/**
 * Inserts an item into the ordered container.
 * All the elements after the insert point are shifted to the next index.
 * If the size of the container after the insert would be greater than the
 * capacity of the container, the last element is dropped.
 * If the item to insert would be inserted after the last element and the
 * container is already full, the item is dropped.
 * @param a The container to extend.
 * @param b The item to insert.
 * @return 
 */
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

/**
 * Get a pointer to an element by index.
 * @param a The container to examine.
 * @param i Index.
 * @return Pointer to the ith element in the container.
 */
ElementPtr dcshof_get(const DcsHoF *a, ElementIdx i) {
  return dcslinear_get(&a->base, i);
}
