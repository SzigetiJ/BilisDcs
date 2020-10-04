#include <assert.h>
#include "DcsLinear.h"
#include <stdbool.h>

// test data
unsigned char dat10[10];
DcsLinear dcsl0 = {
  .itemsize=5,
  .capacity=2,
  .size=0,
  .dat=dat10
};
DcsLinear dcsl1 = {
  .itemsize=5,
  .capacity=2,
  .size=1,
  .dat=dat10
};

bool test_dcslinear_size00() {
 int dcsl_size = dcslinear_size(&dcsl0);
 return (0 == dcsl_size);
}

bool test_dcslinear_size01() {
 int dcsl_size = dcslinear_size(&dcsl1);
 return (1 == dcsl_size);
}

bool test_dcslinear_empty00() {
 bool dcsl_empty = dcslinear_empty(&dcsl0);
 return (dcsl_empty);
}
bool test_dcslinear_empty01() {
 bool dcsl_empty = dcslinear_empty(&dcsl1);
 return (!dcsl_empty);
}

int main(int argc, const char *argv[]) {
 assert(test_dcslinear_size00());
 assert(test_dcslinear_size01());
 assert(test_dcslinear_empty00());
 assert(test_dcslinear_empty01());
 return 0;
}
