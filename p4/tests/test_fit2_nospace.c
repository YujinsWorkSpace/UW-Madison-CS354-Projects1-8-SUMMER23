// many odd sized allocations and interspersed frees
#include <assert.h>
#include <stdlib.h>
#include "p4Heap.h"

int main() {
   assert(init_heap(4096) == 0);
	void *ptr[9];
   ptr[0] = balloc(1);
   ptr[1] = (balloc(5));
   ptr[2] = (balloc(8));
   ptr[3] = (balloc(18));
   ptr[4] = (balloc(80));

   assert(ptr[0] != NULL);
   assert(ptr[1] != NULL);
   assert(ptr[2] != NULL);
   assert(ptr[3] != NULL);
   assert(ptr[4] != NULL);
   
   assert(bfree(ptr[1]) == 0);
   assert(bfree(ptr[0]) == 0);
   assert(bfree(ptr[3]) == 0);
   
   assert(balloc(13) < ptr[4]);
   assert(balloc(1) < ptr[1]);

   assert((ptr[5] = balloc(4)) < ptr[2]);
   assert((ptr[6] = balloc(200)) > ptr[4]);
   assert((ptr[7] = balloc(300)) > ptr[6]);
   assert((ptr[8] = balloc(400)) > ptr[7]);

   assert(bfree(ptr[8]) == 0);
   assert(bfree(ptr[6]) == 0);
   assert(bfree(ptr[7]) == 0);

   assert((ptr[8] = balloc(400)) > ptr[7]);

   exit(0);
}
