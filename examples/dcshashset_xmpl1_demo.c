/*****************************************
 * This example file demonstrates basic
 * operations on DcsHashSet:
 *  - inserting an element;
 *  - searching for an element;
 *  - iterating through the set;
 *  - removing an element.
 *****************************************/

#include "DcsHashSet.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define USERNAME_LEN 20
#define BUFSIZE 80
#define HASHSET_SIZE 4
#define BUCKETS 8

typedef struct {
  char name[USERNAME_LEN];
  int level;
} User;

// Printer function for User.

int sprintf_user(char *dest, const User *a) {
  return sprintf(dest, "%s\t%d", a->name, a->level);
}

ElementIdx user_hash(ElementPtr a) {
  User *auser = (User*) a;
  ElementIdx retv = 0;
  int len = strlen(auser->name);
  for (int i = 0; i < len; ++i)
    retv += auser->name[i];
  return retv;
}

bool user_equals(ElementPtr a, ElementPtr b) {
  User *auser = (User*) a;
  User *buser = (User*) b;
  return strcmp(auser->name, buser->name) == 0;
}

void print_hashset_raw(const DcsHashSet *hs) {
  printf("capacity: %u, top: %u\n", hs->capacity, hs->dat_free_slot_i);
  printf("begin: %u, last: %u\n", hs->begin_sidx, hs->last_sidx);
  printf("slot chaining by age:\n");
  for (ElementIdx i = 0; i < hs->capacity; ++i) {
    printf("\t%u <- %u -> %u\n", hs->prev_sidx_a[i], i, hs->next_sidx_a[i]);
  }
  printf("bucket to slot mapping:\n");
  for (ElementIdx i = 0; i < hs->buckets; ++i) {
    bool valid = hs->bucket_head_valid_a[i];
    printf("\t%u: (%c)", i, (valid ? '*' : '-'));
    if (valid) {
      printf(" -> %u", hs->bucket_head_sidx_a[i]);
    }
    printf("\n");
  }
  printf("slot successors (within bucket):\n");
  for (ElementIdx i = 0; i < hs->capacity; ++i) {
    bool valid = hs->bucket_next_valid_a[i];
    printf("\t%u: (%c)", i, (valid ? '*' : '-'));
    if (valid) {
      printf(" -> %u",  hs->bucket_next_sidx_a[i]);
    }
    printf("\n");
  }
  printf("free slot stack:\n");
  for (ElementIdx i = 0; i < hs->capacity; ++i) {
    bool valid = (i < hs->dat_free_slot_i);
    printf("\t(%c)", (valid ? '*' : '-'));
    if (valid) {
      printf(" %u",  hs->dat_free_slot_a[i]);
    }
    printf("\n");
  }
}

void print_user_hashset_content(const DcsHashSet *hs) {
  char strbuf[BUFSIZE];
  for (DcsIterator i = dcshashset_begin(hs);
          !dcshashset_iterator_equals(hs, i, dcshashset_end(hs));
          i = dcshashset_next_iterator(hs, i)) {
    User *item = (User*) dcshashset_deref_iterator(hs, i);
    sprintf_user(strbuf, item);
    printf("HashSet #%u:\t{%s}\n", (unsigned int) i, strbuf);
  }
}

int main(int argc, const char *argv[]) {
  // serializer buffer
  char strbuf[BUFSIZE];

  // store
  User hashset_dat_raw[HASHSET_SIZE];
  ElementIdx auxidx_a[DCSHASHSET_AUXIDX_SIZE(BUCKETS, HASHSET_SIZE)];
  bool auxflag_a[DCSHASHSET_AUXFLAG_SIZE(BUCKETS, HASHSET_SIZE)];
  DcsHashSet user_hs = dcshashset_init(sizeof (User), HASHSET_SIZE, BUCKETS, (ElementPtr) hashset_dat_raw, auxidx_a, auxflag_a, user_hash, user_equals);

  // data, Pt. 1
  User u0 = {"John", 12};
  User u1 = {"Joe", 10};
  User u2 = {"Steve", 14};

  User * user_flow[] = {&u0, &u2, &u1, &u0};
  size_t user_flow_size = sizeof (user_flow) / sizeof (User*);

  // data, Pt. 2
  User ux0 = {"Mary", 8};
  User ux1 = {"Jane", 9};
  User ux2 = {"Kate", 10};

  User * userx_flow[] = {&ux0, &ux1, &ux2};
  size_t userx_flow_size = sizeof (userx_flow) / sizeof (User*);

  // fill, Pt.1
  printf("HashSet capacity: %u,\tsize: %u\n", dcshashset_capacity(&user_hs), dcshashset_size(&user_hs));

  for (size_t i = 0; i < user_flow_size; ++i) {
    sprintf_user(strbuf, user_flow[i]);
    fprintf(stderr, "Inserting into HashSet: {%s}... ", strbuf);
    bool insert_result = dcshashset_insert(&user_hs, (ElementPtr) user_flow[i]);
    printf("%s\n", (insert_result ? "OK" : "FAIL"));
  }

  printf("\n### After inserting data set 1 ###\n");
  printf("HashSet capacity: %u,\tsize: %u\n", dcshashset_capacity(&user_hs), dcshashset_size(&user_hs));
  print_user_hashset_content(&user_hs);

  // fill, Pt.2
  for (size_t i = 0; i < userx_flow_size; ++i) {
    sprintf_user(strbuf, userx_flow[i]);
    printf("Inserting into HashSet: {%s}... ", strbuf);
    bool insert_result = dcshashset_insert(&user_hs, (ElementPtr) userx_flow[i]);
    printf("%s\n", (insert_result ? "OK" : "FAIL"));
  }

  printf("\n### After inserting data set 2 ###\n");
  printf("HashSet capacity: %u,\tsize: %u\n", dcshashset_capacity(&user_hs), dcshashset_size(&user_hs));
  print_user_hashset_content(&user_hs);
  printf("\n### Internals ###\n");
  print_hashset_raw(&user_hs);

  // search
  User us0 = {"Joe", 0}; // note: level is 0 - as search functions (hash / equals) do not deal with level value.
  User us1 = {"Andrew", 0}; // note: level is 0 - as search functions (hash / equals) do not deal with level value.

  bool joe_is_there = dcshashset_contains(&user_hs, (ElementPtr) & us0);
  printf("User %s is %sthere.\n", us0.name, (joe_is_there ? "" : "not "));

  bool andrew_is_there = dcshashset_contains(&user_hs, (ElementPtr) & us1);
  printf("User %s is %sthere.\n", us1.name, (andrew_is_there ? "" : "not "));

  DcsIterator us0x_it = dcshashset_find(&user_hs, (const ElementPtr) &us0);
  if (!dcshashset_iterator_equals(&user_hs, us0x_it, dcshashset_end(&user_hs))) {
    User *us0x = (User*) dcshashset_deref_iterator(&user_hs, us0x_it);
    sprintf_user(strbuf, us0x);
    printf("User data: %s\n", strbuf);
  } else {
    printf("User %s not found.\n", us0.name);
  }

  DcsIterator us1x_it = dcshashset_find(&user_hs, (const ElementPtr) &us1);
  if (!dcshashset_iterator_equals(&user_hs, us1x_it, dcshashset_end(&user_hs))) {
    User *us1x = (User*) dcshashset_deref_iterator(&user_hs, us1x_it);
    sprintf_user(strbuf, us1x);
    printf("User data: %s\n", strbuf);
  } else {
    printf("User %s not found.\n", us1.name);
  }

  // remove
  bool us0rm = dcshashset_remove(&user_hs, (const ElementPtr) &us0);
  printf("Removing user %s %s.\n", us0.name, (us0rm ? "Done" : "FAILED"));
  bool us0rmx = dcshashset_remove(&user_hs, (const ElementPtr) &us0);
  printf("Removing user %s %s.\n", us0.name, (us0rmx ? "Done" : "FAILED"));

  printf("\n### After removing element ###\n");
  print_user_hashset_content(&user_hs);
  printf("\n### Internals ###\n");
  print_hashset_raw(&user_hs);

  return 0;
}
