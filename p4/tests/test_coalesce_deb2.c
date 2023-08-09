// check for coalesce free space
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "p4Heap.h"

int main() {

   int size = 1020;

   assert(init_heap(4096) == 0);
   void * ptr[15];
   ptr[0] = balloc(size);

   int i=1;
   while ( ptr[i-1] != NULL ) {
	   ptr[i++] = balloc(size);
   }

   disp_heap();
   int result = bfree(ptr[1]);
   result = bfree(ptr[2]);

   disp_heap();

   ptr[1] = balloc(size*2);
   assert(ptr[1] == NULL);

   assert(coalesce()>0);

   disp_heap();

   ptr[1] = balloc(size*2);
   assert(ptr[1] != NULL);
   disp_heap();

   exit(0);
}
