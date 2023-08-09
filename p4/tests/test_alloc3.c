// many odd sized allocations
#include <assert.h>
#include <stdlib.h>
#include "p4Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   assert(balloc(1) != NULL);
   assert(balloc(5) != NULL);
   assert(balloc(14) != NULL);
   assert(balloc(8) != NULL);
   assert(balloc(1) != NULL);
   assert(balloc(4) != NULL);
   assert(balloc(55) != NULL);
   assert(balloc(9) != NULL);
   assert(balloc(33) != NULL);
   exit(0);
}
