#include "DcsHoF.h"
#include <stdbool.h>
#include <stdio.h>

#define BUFSIZE 80
#define HALL_OF_FAME_SIZE 2

typedef struct {
  long date;
  int points;
  char user[20];
} Entry;

int sprintf_entry(char *dest, const Entry *a) {
  return sprintf(dest, "%d\t%s\t%ld", a->points, a->user, a->date);
}

bool entry_order(ElementPtr a, ElementPtr b) {
  Entry *aa = (Entry*) a;
  Entry *bb = (Entry*) b;

  if (aa->points > bb->points) return true;
  if (bb->points > aa->points) return false;
  if (aa->date > bb->date) return true;
  if (bb->date > aa->date) return false;
  return false;
}

int main(int argc, const char *argv[]) {
  char strbuf[BUFSIZE];
  Entry hof_dat_raw[HALL_OF_FAME_SIZE];
  DcsHoF hof = dcshof_init(sizeof (Entry), HALL_OF_FAME_SIZE, (ElementPtr) hof_dat_raw, entry_order);

  Entry foo = {1234567890, 54, "Bir"};
  Entry bar = {1234567891, 65, "Fee"};
  Entry baz = {1234567891, 60, "Bez"};

  Entry * entry_flow[] = {&foo, &bar, &baz, &foo, &baz};
  size_t entry_flow_size = sizeof (entry_flow) / sizeof (entry_flow[0]);

  printf("HallOfFame capacity: %u,\tsize: %u\n", dcshof_capacity(&hof), dcshof_size(&hof));

  for (size_t i = 0; i < entry_flow_size; ++i) {
    sprintf_entry(strbuf, entry_flow[i]);
    printf("Inserting into HallOfFame: {%s}\n", strbuf);
    dcshof_insert(&hof, (ElementPtr) entry_flow[i]);
  }

  printf("HallOfFame capacity: %u,\tsize: %u\n", dcshof_capacity(&hof), dcshof_size(&hof));

  for (ElementIdx i = 0; i < dcshof_size(&hof); ++i) {
    Entry *item = (Entry*) dcshof_get(&hof, i);
    sprintf_entry(strbuf, item);
    printf("HallOfFame #%u:\t{%s}\n", (unsigned int) i, strbuf);
  }
  return 0;
}

