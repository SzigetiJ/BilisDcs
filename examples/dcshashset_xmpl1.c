#include "DcsHashSet.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define USERNAME_LEN 20
#define BUFSIZE 80
#define HASHSET_SIZE 4

typedef struct {
  char name[USERNAME_LEN];
  int level;
} User;

// Printer function for User.
int sprintf_user(char *dest, const User *a) {
  return sprintf(dest, "%s\t%d", a->name, a->level);
}

ElementIdx user_hash(ElementPtr a) {
  User *auser = (User*)a;
  ElementIdx retv = 0;
  int len = strlen(auser->name);
  for (int i=0; i<len; ++i)
    retv+=auser->name[i];
  return retv;
}

bool user_equals(ElementPtr a, ElementPtr b) {
  User *auser = (User*)a;
  User *buser = (User*)b;
  return strcmp(auser->name, buser->name)==0;
}

int main(int argc, const char *argv[]) {
  char strbuf[BUFSIZE];
  User hashset_dat_raw[HASHSET_SIZE];
  ElementIdx auxidx_a[DCSHASHSET_AUXIDX_SIZE(HASHSET_SIZE)];
  bool auxflag_a[DCSHASHSET_AUXFLAG_SIZE(HASHSET_SIZE)];
  DcsHashSet user_hs = dcshashset_init(sizeof (User), HASHSET_SIZE, (ElementPtr) hashset_dat_raw, auxidx_a, auxflag_a, user_hash, user_equals);

  User u0={"John", 12};
  User u1={"Joe", 10};
  User u2={"Steve", 14};

  User *user_flow[]={&u0, &u2, &u1, &u0};
  size_t user_flow_size=sizeof(user_flow) / sizeof(User*);

  printf("HashSet capacity: %u,\tsize: %u\n", dcshashset_capacity(&user_hs), dcshashset_size(&user_hs));

  for (size_t i = 0; i < user_flow_size; ++i) {
    sprintf_user(strbuf, user_flow[i]);
    printf("Inserting into HashSet: {%s}... ", strbuf);
    bool insert_result = dcshashset_insert(&user_hs, (ElementPtr) user_flow[i]);
    printf("%s\n", (insert_result?"OK":"FAIL"));
  }

  printf("HashSet capacity: %u,\tsize: %u\n", dcshashset_capacity(&user_hs), dcshashset_size(&user_hs));

  // And here we list the content..
  for (DcsIterator i = dcshashset_begin(&user_hs);
          !dcshashset_iterator_equals(&user_hs, i, dcshashset_end(&user_hs));
          i = dcshashset_next_iterator(&user_hs, i)) {
    User *item = (User*) dcshashset_deref_iterator(&user_hs, i);
    sprintf_user(strbuf, item);
    printf("HashSet #%u:\t{%s}\n", (unsigned int) i, strbuf);
  }


  User ux0={"Mary", 8};
  User ux1={"Jane", 9};
  User ux2={"Kate", 10};

  User *userx_flow[]={&ux0, &ux1, &ux2};
  size_t userx_flow_size=sizeof(userx_flow) / sizeof(User*);

  printf("HashSet capacity: %u,\tsize: %u\n", dcshashset_capacity(&user_hs), dcshashset_size(&user_hs));

  for (size_t i = 0; i < userx_flow_size; ++i) {
    sprintf_user(strbuf, userx_flow[i]);
    printf("Inserting into HashSet: {%s}... ", strbuf);
    bool insert_result = dcshashset_insert(&user_hs, (ElementPtr) userx_flow[i]);
    printf("%s\n", (insert_result?"OK":"FAIL"));
  }

  printf("HashSet capacity: %u,\tsize: %u\n", dcshashset_capacity(&user_hs), dcshashset_size(&user_hs));

  return 0;
}

