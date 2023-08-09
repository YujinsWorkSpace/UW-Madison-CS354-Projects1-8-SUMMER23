// many odd sized allocations checked for alignment
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "p4Heap.h"

int main() {
    assert(init_heap(4096) == 0);
    void* ptr[9];
    ptr[0] = balloc(1);
    ptr[1] = balloc(14);
    ptr[2] = balloc(33);
    ptr[3] = balloc(8);
    ptr[4] = balloc(1);
    ptr[5] = balloc(4);
    ptr[6] = balloc(5);
    ptr[7] = balloc(9);
    ptr[8] = balloc(55);
   
    for (int i = 0; i < 9; i++) {
        assert(ptr[i] != NULL);
    }

    for (int i = 0; i < 9; i++) {
        assert(((int)ptr[i]) % 8 == 0);
    }
    exit(0);
}
