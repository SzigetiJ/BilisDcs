#include "DcsHoF.h"
#include <stdbool.h>
#include <stdio.h>

#define HALL_OF_FAME_SIZE 2

typedef struct {
 long date;
 int points;
 char user[20];
} Entry;

bool entry_order(ItemPtr a, ItemPtr b) {
 Entry *aa=(Entry*)a;
 Entry *bb=(Entry*)b;

 if (aa->points > bb->points) return true;
 if (bb->points > aa->points) return false;
 if (aa->date > bb->date) return true;
 if (bb->date > aa->date) return false;
 return false;
}

int main(int argc, const char *argv[]) {
 Entry hof_dat_raw[HALL_OF_FAME_SIZE];
 DcsHoF hof = dcshof_init(sizeof(Entry), HALL_OF_FAME_SIZE, (ItemPtr)hof_dat_raw, entry_order);

 Entry foo={1234567890, 54, "Bir"};
 Entry bar={1234567891, 65, "Fee"};
 Entry baz={1234567891, 60, "Bez"};

 dcshof_insert(&hof, (ItemPtr)&foo);
 dcshof_insert(&hof, (ItemPtr)&bar);
 dcshof_insert(&hof, (ItemPtr)&baz);
 dcshof_insert(&hof, (ItemPtr)&foo);
 dcshof_insert(&hof, (ItemPtr)&baz);

 size_t hof_size = dcshof_size(&hof);
 
 for (size_t i=0; i<hof_size; ++i) {
  Entry *item = (Entry*)dcshof_get(&hof, i);
  printf("%u:\t%s\t%d\n", i, item->user, item->points);
 }
 return 0;
}

