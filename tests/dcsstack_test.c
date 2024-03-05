#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "DcsLinear.h"
#include "DcsStack.h"

// test data
unsigned char dat10[10];
DcsStack dcss[] = {
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
const DcsStack T2 = {3, 5, 5, (ElementPtr) T2DAT};

bool test_dcsstack_init() {
  bool pass = true;
  Byte datpool[200];
  ElementSize size_a[] = {1, 2, 4, 8};
  ElementIdx cap_a[] = {3, 4, 5, 6};
  DcsStack expected[] = {
    {1, 3, 0, datpool},
    {2, 4, 0, datpool + 1},
    {4, 5, 0, datpool + 2},
    {8, 6, 0, datpool + 3}
  };
  for (unsigned int i = 0; i < sizeof (size_a) / sizeof (size_a[0]); ++i) {
    DcsStack result = dcsstack_init(size_a[i], cap_a[i], datpool + i);
    if (memcmp(&expected[i], &result, sizeof (DcsStack))) {
      fprintf(stderr, "dcsstack_init() failed at input #%u\n", i);
      pass = false;
    }
  }
  return pass;
}

bool test_dcsstack_size() {
  bool pass = true;
  size_t exp_size[] = {0, 1, 5};
  for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
    size_t dcss_size = dcsstack_size(&dcss[i]);
    if (exp_size[i] != dcss_size) {
      fprintf(stderr, "dcsstack_size() failed at input #%u\n", i);
      pass = false;
    }
  }
  return pass;
}

bool test_dcsstack_capacity() {
  bool pass = true;
  size_t exp_cap[] = {2, 2, 5};
  for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
    size_t dcss_cap = dcsstack_capacity(&dcss[i]);
    if (exp_cap[i] != dcss_cap) {
      fprintf(stderr, "dcsstack_capacity() failed at input #%u\n", i);
      pass = false;
    }
  }
  return pass;
}

bool test_dcsstack_empty() {
  bool pass = true;
  bool exp_empty[] = {true, false, false};
  for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
    bool dcss_empty = dcsstack_empty(&dcss[i]);
    if (exp_empty[i] != dcss_empty) {
      fprintf(stderr, "dcsstack_empty() failed at input #%u\n", i);
      pass = false;
    }
  }
  return pass;
}

bool test_dcsstack_full() {
  bool pass = true;
  bool expected[] = {false, false, true};
  for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
    bool result = dcsstack_full(&dcss[i]);
    if (expected[i] != result) {
      fprintf(stderr, "dcsstack_full() failed at input #%u\n", i);
      pass = false;
    }
  }
  return pass;
}

bool test_dcsstack_push() {
  bool pass = true;

  DcsLinear store = T2;
  char pattern[] = "zzz";
  char *expected_content[] = {
    "zzzab1ab2ab3ab4",
    "ab0zzzab2ab3ab4",
    "ab0ab1zzzab3ab4",
    "ab0ab1ab2zzzab4",
    "ab0ab1ab2ab3zzz",
    "ab0ab1ab2ab3ab4"
  };
  DcsIterator expected[] = {
    1, 2, 3, 4, 5, 5
  };
  for (ElementIdx i = 0; i < store.capacity + 1; ++i) {
    memcpy(store.dat, T2DAT_INIT, store.itemsize * store.capacity);
    store.size = i;

    DcsIterator result = dcsstack_push(&store, (ElementPtr) pattern);
    if (memcmp(expected_content[i], store.dat, store.itemsize * store.capacity)) {
      fprintf(stderr, "dcsstack_push() content failed\n");
      pass = false;
    }
    if (expected[i] != result) {
      fprintf(stderr, "dcsstack_push() return failed\n");
      pass = false;
    }
  }
  return pass;
}

bool test_dcsstack_pop() {
  bool pass = true;

  DcsLinear store = T2;
  ElementPtr expected[] = {
    store.dat, store.dat,
    store.dat + 1 * store.itemsize,
    store.dat + 2 * store.itemsize,
    store.dat + 3 * store.itemsize,
  };
  for (ElementIdx i = 0; i < store.capacity; ++i) {
    store.size = i;

    ElementPtr result = dcsstack_pop(&store);
    if (expected[i] != result) {
      fprintf(stderr, "dcsstack_pop() return failed\n");
      pass = false;
    }
  }
  return pass;
}

bool test_dcsstack_begin() {
  bool pass = true;
  DcsIterator expected[] = {0, 0, 0};
  for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
    DcsIterator result = dcsstack_begin(&dcss[i]);
    if (expected[i] != result) {
      fprintf(stderr, "dcsstack_begin() failed at input #%u\n", i);
      pass = false;
    }
  }
  return pass;
}

bool test_dcsstack_end() {
  bool pass = true;
  DcsIterator expected[] = {0, 1, 5};
  for (unsigned int i = 0; i < sizeof (dcss) / sizeof (dcss[0]); ++i) {
    DcsIterator result = dcsstack_end(&dcss[i]);
    if (expected[i] != result) {
      fprintf(stderr, "dcsstack_begin() failed at input #%u\n", i);
      pass = false;
    }
  }
  return pass;
}

bool test_dcsstack_it_all() {
  bool pass = true;
  DcsIterator it0 = dcsstack_begin(&T2);
  for (ElementIdx i = 0; i < T2.capacity; ++i) {
    DcsIterator it_nxt = dcsstack_next_iterator(&T2, it0);
    if (it_nxt != it0 + 1) {
      fprintf(stderr, "dcsstack_next_iterator() failed at iteration #%zu\n", i);
      pass = false;
    }
    if (dcsstack_iterator_equals(&T2, it_nxt, it0)) {
      fprintf(stderr, "!dcsstack_iterator_equals() failed at iteration #%zu\n", i);
      pass = false;
    }
    ElementPtr dat0 = dcsstack_deref_iterator(&T2, it0);
    if (dat0 != T2.dat + i * T2.itemsize) {
      fprintf(stderr, "dcsstack_deref_iterator() failed at iteration #%zu\n", i);
      pass = false;
    }
    it0 = it_nxt;
  }
  return pass;
}

int main(int argc, const char *argv[]) {
  if (1 < argc) {
    fprintf(stderr, "Test program %s does not require any arguments\n", argv[0]);
  }

  assert(test_dcsstack_init());
  assert(test_dcsstack_size());
  assert(test_dcsstack_capacity());
  assert(test_dcsstack_empty());
  assert(test_dcsstack_full());
  assert(test_dcsstack_begin());
  assert(test_dcsstack_end());

  assert(test_dcsstack_push());
  assert(test_dcsstack_pop());

  assert(test_dcsstack_it_all());

  return 0;
}
