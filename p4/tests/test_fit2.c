// many odd sized allocations and interspersed frees
#include <assert.h>
#include <stdlib.h>
#include "p4Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   void * ptr[9];
   ptr[0] = balloc(1);
   ptr[1] = (balloc(5));
   ptr[2] = (balloc(8));
   void *p3 = ptr[3] = (balloc(14));
   assert(ptr[0] != NULL);
   assert(ptr[1] != NULL);
   assert(ptr[2] != NULL);
   assert(ptr[3] != NULL);
   
   assert(bfree(ptr[1]) == 0);
   assert(bfree(ptr[0]) == 0);
   assert(bfree(ptr[3]) == 0);
   
   assert((ptr[3] = balloc(13)) == p3);

   ptr[4] = (balloc(1));
   ptr[5] = (balloc(4));
   assert(ptr[4] != NULL);
   assert(ptr[5] != NULL);
   assert(bfree(ptr[5]) == 0);
   
   ptr[6] = (balloc(9));
   ptr[7] = (balloc(33));
   assert(ptr[6] != NULL);
   assert(ptr[7] != NULL);
   
   assert(bfree(ptr[4]) == 0);

   ptr[8] = (balloc(55));
   assert(ptr[8] != NULL);

   assert(bfree(ptr[2]) == 0);
   assert(bfree(ptr[7]) == 0);
   assert(bfree(ptr[8]) == 0);
   assert(bfree(ptr[6]) == 0);

   assert(balloc(5) < ptr[8]);

   exit(0);
}
