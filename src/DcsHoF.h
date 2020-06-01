#ifndef _DCS_HOF_H_
#define _DCS_HOF_H_

#include <stddef.h>
#include <stdbool.h>

typedef size_t ItemSize;
typedef unsigned char* ItemPtr;
typedef bool (*ItemRel)(ItemPtr, ItemPtr);


typedef struct {
 ItemSize itemsize;
 size_t capacity;
 size_t size;
 ItemPtr dat;
 ItemRel less;
} DcsHoF;

DcsHoF dcshof_init(ItemSize, size_t, const ItemPtr, const ItemRel);
size_t dcshof_size(const DcsHoF*);
size_t dcshof_capacity(const DcsHoF*);
size_t dcshof_insert(DcsHoF*, const ItemPtr);
ItemPtr dcshof_get(const DcsHoF*, size_t);

#endif // _DCS_HOF_H_

