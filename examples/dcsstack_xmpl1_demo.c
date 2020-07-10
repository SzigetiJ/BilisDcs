/*****************************************
 * This example file demonstrates basic
 * operations on DcsStack:
 *  - push operation;
 *  - pop operation.
 *****************************************/

#include "DcsStack.h"
#include "DcsLinear.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define STACK_SIZE 5
#define BUFFER_SIZE 12

typedef int StackItem;

StackItem init_a[] = {2, 4, 6, 8, 10, 12};
StackItem item_0 = 3;
StackItem item_1 = 5;

void sprintf_item(char *out, size_t out_len, StackItem *a) {
  snprintf(out, out_len, "%d", *a);
}

void print_stack(DcsStack *st) {
  char buffer[BUFFER_SIZE];
  printf("Capacity: %u, size: %u\n", st->capacity, st->size);
  for (ElementIdx i = 0; i<st->capacity; ++i) {
    bool valid = i < st->size;
    printf(" #%u (%c)", i, (valid?'*':'-'));
    if (valid) {
      sprintf_item(buffer, BUFFER_SIZE, (StackItem*)(st->dat + i * st->itemsize));
      printf(" %s", buffer);
    }
    printf("\n");
  }
}

int main(int argc, const char *argv[]) {
  char buffer[BUFFER_SIZE];

  // store
  int stack_raw[STACK_SIZE];
  DcsStack demo_st = dcsstack_init(sizeof (int), STACK_SIZE, (ElementPtr)stack_raw);

  printf("### AFTER INIT\n");
  print_stack(&demo_st);
  printf("Empty?\t%s\n", (dcsstack_empty(&demo_st)?"YES":"NO"));
  printf("Full?\t%s\n", (dcsstack_full(&demo_st)?"YES":"NO"));

  // fill
  int init_a_len = sizeof(init_a) / sizeof(StackItem);
  for (int i=0; i<init_a_len; ++i) {
    StackItem *item = init_a + i;
    sprintf_item(buffer, BUFFER_SIZE, item);
    printf("Inserting item \"%s\"\n", buffer);
    dcsstack_push(&demo_st, (ElementPtr)item);
  }
  printf("### AFTER FILL\n");
  print_stack(&demo_st);
  printf("Empty?\t%s\n", (dcsstack_empty(&demo_st)?"YES":"NO"));
  printf("Full?\t%s\n", (dcsstack_full(&demo_st)?"YES":"NO"));

  // pop
  ElementPtr pop0_result = dcsstack_pop(&demo_st);
  sprintf_item(buffer, BUFFER_SIZE, (StackItem*)pop0_result);
  printf("Popped: %s\n", buffer);

  {
    StackItem *item = &item_0;
    sprintf_item(buffer, BUFFER_SIZE, item);
    printf("Inserting item \"%s\"\n", buffer);
    dcsstack_push(&demo_st, (ElementPtr)item);
  }

  {
    StackItem *item = &item_1;
    sprintf_item(buffer, BUFFER_SIZE, item);
    printf("Inserting item \"%s\"\n", buffer);
    dcsstack_push(&demo_st, (ElementPtr)item);
  }

  while (!dcsstack_empty(&demo_st)){
    printf("Popping...\n");
    dcsstack_pop(&demo_st);
    print_stack(&demo_st);
  }
  printf("Empty?\t%s\n", (dcsstack_empty(&demo_st)?"YES":"NO"));
  printf("Full?\t%s\n", (dcsstack_full(&demo_st)?"YES":"NO"));

  return 0;
}
