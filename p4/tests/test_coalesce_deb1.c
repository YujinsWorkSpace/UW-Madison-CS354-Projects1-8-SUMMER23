// check for coalesce free space
#include <assert.h>
#include <stdlib.h>
#include "p4Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   void * ptr[4];

   ptr[0] = balloc(800);
   assert(ptr[0] != NULL);

   ptr[1] = balloc(800);
   assert(ptr[1] != NULL);

   ptr[2] = balloc(800);
   assert(ptr[2] != NULL);

   ptr[3] = balloc(800);
   assert(ptr[3] != NULL);

   while (balloc(800) != NULL) {
	// just allocate space don't need to save ptr
   }  ;

   disp_heap();

   assert(bfree(ptr[0]) == 0);
   assert(bfree(ptr[1]) == 0);

   disp_heap();

   assert((ptr[1] = balloc(1600)) == NULL);

   coalesce();

   disp_heap();
   assert((ptr[1] = balloc(1600)) != NULL);

   disp_heap();

   exit(0);
}
