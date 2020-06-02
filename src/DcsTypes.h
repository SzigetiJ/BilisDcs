#ifndef DCSTYPES_H
#define DCSTYPES_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef size_t ElementSize;
typedef size_t ElementIdx;
typedef unsigned char* ElementPtr;
typedef bool (*ElementRel)(ElementPtr, ElementPtr);

typedef struct DcsLinear_ DcsLinear;

#ifdef __cplusplus
}
#endif

#endif /* DCSTYPES_H */

