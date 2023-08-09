// check for coalesce free space
#include <assert.h>
#include <stdlib.h>
#include "p4Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   void * ptr[5];

   ptr[0] = balloc(500);
   assert(ptr[0] != NULL);

   ptr[1] = balloc(500);
   assert(ptr[1] != NULL);

   ptr[2] = balloc(500);
   assert(ptr[2] != NULL);

   ptr[3] = balloc(500);
   assert(ptr[3] != NULL);

   ptr[4] = balloc(500);
   assert(ptr[4] != NULL);

   while (balloc(500) != NULL)
     ;

   assert(bfree(ptr[1]) == 0);
   assert(bfree(ptr[3]) == 0);
   assert(bfree(ptr[2]) == 0);

   ptr[3] = balloc(1300);
   assert(ptr[3] == NULL);

   coalesce();

   ptr[3] = balloc(1300);
   assert(ptr[3] != NULL);

   exit(0);
}
