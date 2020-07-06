BilisDcs
========

_Collection of Reliable Data Container Structures for Standard C_

Quick Intro
-----------

1. Define your type
```c
typedef struct {
 char name[20];
 int param_a;
 unsigned int param_b;
} NameAndValue;
```
2. Allocate space for the container
```c
#define STACKSIZE 16
NameAndValue name_and_values[STACKSIZE];
```
3. Initialize the container
```c
DcsStack nv_stack = dcsstack_init(sizeof(NameAndValue), STACKSIZE, name_and_values);
```
4. Use the container
```c
NameAndValue nv0 = {"Foo", -123, 4};
dcsstack_push(&nv_stack, &nv0);
int nv_size = dcsstack_size(&nv_stack);
// etc.
```


Provided Structures
-------------------

| Structure | Description | Implementation | Documentation | Tests | Examples |
| --------- | ----------- | -------------- | ------------- | ----- | -------- |
| DcsFIFO | Circular buffer based FIFO | _missing_ | _missing_ | _missing_ | _missing_ |
| DcsHashSet | Capacity constrained hashset | **READY** | **READY** | _missing_ | **1** |
| DcsHS | Size optimized hashset | _missing_ | _missing_ | _missing_ | _missing_ |
| DcsHoF | _Hall of Fame_ -- stores Top N elements | **READY** | **READY** | _missing_ | **1** |
| DcsLinSet | Array based, ordered set | **READY** | _in progress_ | _missing_ | _missing_ |
| DcsHashMultiMap | Multiple values with the same key| _missing_ | _missing_ | _missing_ | _missing_ |
| DcsStack | Simple, size constrained stack | **READY** | _missing_ | _missing_ | _missing_ |

Key Features
------------

* No dynamic memory allocation

   Memory area has to be allocated by the user. Initializer functions take a reference to the pre-allocated memory area as parameter.

* Access to container elements via byte pointers

   Standard C language does not support templates. There are multiple ways to overcome this gap.
   BilisDcs has chosen to employ the generic type: byte pointer (ElementPtr).
   Also, the size of the stored type (itemsize) always must be given at initialization of the container structure.

* Iterators and iterator functions

   Functions `~_begin()` and `~_end()` are defined for each container.
   Since the standard C language does not support operator overload,
   operators on iterators are also defined as functions:
   * `~_iterator_equals()`
   * `~_next_iterator()`
   * `~_deref_iterator()`

