// a few allocations in multiples of 4 bytes followed by frees
#include <assert.h>
#include <stdlib.h>
#include "p4Heap.h"

int main() {

   assert(init_heap(4096) == 0);
   void* rest = balloc(3908);

   void* ptr[8];

   ptr[0] = balloc(8);
   ptr[1] = balloc(8);
   ptr[2] = balloc(8);
   ptr[3] = balloc(8);
   ptr[4] = balloc(16);
   ptr[5] = balloc(16);
   ptr[6] = balloc(24);
   ptr[7] = balloc(24);

   assert(balloc(40) == NULL);
disp_heap();

   assert(bfree(ptr[4]) == 0);
   assert(bfree(ptr[5]) == 0);
   assert(bfree(ptr[6]) == 0);
disp_heap();

	void* fits = balloc(20); 
	assert(fits != NULL);
disp_heap();

   exit(0);
}
