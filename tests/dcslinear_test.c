#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "DcsLinear.h"

// test data
unsigned char dat10[10];
DcsLinear dcss[] = {
 {
  .itemsize = 5,
  .capacity = 2,
  .size = 0,
  .dat = dat10
 },
 {
  .itemsize = 5,
  .capacity = 2,
  .size = 1,
  .dat = dat10
 },
 {
  .itemsize = 2,
  .capacity = 5,
  .size = 5,
  .dat = dat10
 }
};

const char T2DAT_INIT[] = "ab0ab1ab2ab3ab4";
char T2DAT[15];
const DcsLinear T2 = {3, 5, 5, (ElementPtr) T2DAT};

bool test_dcsstack_init() {
 bool pass = true;
 Byte datpool[200];
 ElementSize size_a[] = {1, 2, 4, 8};
 ElementIdx cap_a[] = {3, 4, 5, 6};
 DcsLinear expected[] = {
  {1, 3, 0, datpool},
  {2, 4, 0, datpool + 1},
  {4, 5, 0, datpool + 2},
  {8, 6, 0, datpool + 3}
 };
 for (unsigned int i = 0; i < sizeof (size_a) / sizeof (size_a[0]); ++i) {
  DcsLinear result = dcslinear_init(size_a[i], cap_a[i], datpool + i);
  if (memcmp(&expected[i], &result, sizeof (DcsLinear))) {
   fprintf(stderr, "dcslinear_init() failed at input #%u\n", i);
   pass = false;
  }
 }
 return pass;
}

bool test_dcslinear_size() {
 bool pass = true;
 size_t exp_size[] = {0, 1, 5};
 for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
  size_t dcsl_size = dcslinear_size(&dcss[i]);
  if (exp_size[i] != dcsl_size) {
   fprintf(stderr, "dcslinear_size() failed at input #%u\n", i);
   pass = false;
  }
 }
 return pass;
}

bool test_dcslinear_capacity() {
 bool pass = true;
 size_t exp_cap[] = {2, 2, 5};
 for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
  size_t dcsl_cap = dcslinear_capacity(&dcss[i]);
  if (exp_cap[i] != dcsl_cap) {
   fprintf(stderr, "dcslinear_capacity() failed at input #%u\n", i);
   pass = false;
  }
 }
 return pass;
}

bool test_dcslinear_empty() {
 bool pass = true;
 bool exp_empty[] = {true, false, false};
 for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
  bool dcsl_empty = dcslinear_empty(&dcss[i]);
  if (exp_empty[i] != dcsl_empty) {
   fprintf(stderr, "dcslinear_empty() failed at input #%u\n", i);
   pass = false;
  }
 }
 return pass;
}

bool test_dcslinear_full() {
 bool pass = true;
 bool expected[] = {false, false, true};
 for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
  bool result = dcslinear_full(&dcss[i]);
  if (expected[i] != result) {
   fprintf(stderr, "dcslinear_full() failed at input #%u\n", i);
   pass = false;
  }
 }
 return pass;
}

bool test_dcslinear_get() {
 bool pass = true;
 for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
  for (ElementIdx idx = 0; idx < dcss[i].capacity; ++idx) {
   ElementPtr result = dcslinear_get(&dcss[i], idx);
   if (dcss[i].dat + idx * dcss[i].itemsize != result) {
    fprintf(stderr, "dcslinear_get() failed at input #%u\n", i);
    pass = false;
   }
  }
 }
 return pass;
}

bool test_dcslinear_set() {
 bool pass = true;

 DcsLinear store = T2;
 memcpy(store.dat, T2DAT_INIT, store.itemsize * store.capacity);
 char pattern[] = "zzz";
 ElementIdx idx = 1;
 char expected[] = "ab0zzzab2ab3ab4";

 dcslinear_set(&store, idx, (ElementPtr) pattern);
 if (memcmp(expected, store.dat, store.itemsize * store.capacity)) {
  fprintf(stderr, "dcslinear_set() failed\n");
  pass = false;
 }
 return pass;
}

bool test_dcslinear_xtract() {
 bool pass = true;

 DcsLinear store = T2;
 memcpy(store.dat, T2DAT_INIT, store.itemsize * store.capacity);
 char result[] = "zzzz";
 ElementIdx idx = 3;
 char expected[] = "ab3z";

 dcslinear_copy_to(&store, idx, (ElementPtr) result);
 if (strncmp(expected, result, 4)) {
  fprintf(stderr, "dcslinear_copy_to() failed. Expected: %s, actual: %s\n", expected, result);
  pass = false;
 }
 return pass;
}

bool test_dcslinear_begin() {
 bool pass = true;
 DcsIterator expected[] = {0, 0, 0};
 for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
  DcsIterator result = dcslinear_begin(&dcss[i]);
  if (expected[i] != result) {
   fprintf(stderr, "dcslinear_begin() failed at input #%u\n", i);
   pass = false;
  }
 }
 return pass;
}

bool test_dcslinear_end() {
 bool pass = true;
 DcsIterator expected[] = {0, 1, 5};
 for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
  DcsIterator result = dcslinear_end(&dcss[i]);
  if (expected[i] != result) {
   fprintf(stderr, "dcslinear_begin() failed at input #%u\n", i);
   pass = false;
  }
 }
 return pass;
}

bool test_dcslinear_it_all() {
 bool pass = true;
 DcsIterator it0 = dcslinear_begin(&T2);
 for (ElementIdx i = 0; i < T2.capacity; ++i) {
  DcsIterator it_nxt = dcslinear_next_iterator(&T2, it0);
  if (it_nxt != it0 + 1) {
   fprintf(stderr, "dcslinear_next_iterator() failed at iteration #%zu\n", i);
   pass = false;
  }
  if (dcslinear_iterator_equals(&T2, it_nxt, it0)) {
   fprintf(stderr, "!dcslinear_iterator_equals() failed at iteration #%zu\n", i);
   pass = false;
  }
  ElementPtr dat0 = dcslinear_deref_iterator(&T2, it0);
  if (dat0 != dcslinear_get(&T2, i)) {
   fprintf(stderr, "dcslinear_deref_iterator() failed at iteration #%zu\n", i);
   pass = false;
  }
  dcslinear_inc_iterator(&T2, &it0);
  if (it_nxt != it0) {
   fprintf(stderr, "dcslinear_inc_iterator() failed at iteration #%zu\n", i);
   pass = false;
  }
  if (!dcslinear_iterator_equals(&T2, it_nxt, it0)) {
   fprintf(stderr, "dcslinear_iterator_equals() failed at iteration #%zu\n", i);
   pass = false;
  }
 }
 return pass;
}

int main(int argc, const char *argv[]) {
 if (1 < argc) {
  fprintf(stderr, "Test program %s does not require any arguments\n", argv[0]);
 }

 assert(test_dcsstack_init());
 assert(test_dcslinear_size());
 assert(test_dcslinear_capacity());
 assert(test_dcslinear_empty());
 assert(test_dcslinear_full());
 assert(test_dcslinear_get());
 assert(test_dcslinear_set());
 assert(test_dcslinear_xtract());
 assert(test_dcslinear_begin());
 assert(test_dcslinear_end());

 assert(test_dcslinear_it_all());

 return 0;
}
