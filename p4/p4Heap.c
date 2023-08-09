///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020-2023 Nawaf Alsrehin based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission SPRING 2023, CS354-n_alsrehin
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "p4Heap.h"

 
/*
 * This structure serves as the header for each allocated and free block.
 * It also serves as the footer for each free block but only containing size.
 */
typedef struct blockHeader {

    int size_status;

    /*
     * Size of the block is always a multiple of 8.
     * Size is stored in all block headers and in free block footers.
     *
     * Status is stored only in headers using the two least significant bits.
     *   Bit0 => least significant bit, last bit
     *   Bit0 == 0 => free block
     *   Bit0 == 1 => allocated block
     *
     *   Bit1 => second last bit 
     *   Bit1 == 0 => previous block is free
     *   Bit1 == 1 => previous block is allocated
     * 
     * Start Heap: 
     *  The blockHeader for the first block of the heap is after skip 4 bytes.
     *  This ensures alignment requirements can be met.
     * 
     * End Mark: 
     *  The end of the available memory is indicated using a size_status of 1.
     * 
     * Examples:
     * 
     * 1. Allocated block of size 24 bytes:
     *    Allocated Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 25
     *      If the previous block is allocated p-bit=1 size_status would be 27
     * 
     * 2. Free block of size 24 bytes:
     *    Free Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 24
     *      If the previous block is allocated p-bit=1 size_status would be 26
     *    Free Block Footer:
     *      size_status should be 24
     */
} blockHeader;         

/* Global variable - DO NOT CHANGE NAME or TYPE. 
 * It must point to the first block in the heap and is set by init_heap()
 * i.e., the block at the lowest address.
 */
blockHeader *heap_start = NULL;     

/* Size of heap allocation padded to round to nearest page size.
 */
int alloc_size;

/*
 * Additional global variables may be added as needed below
 * TODO: add global variables needed by your function
 */
blockHeader  *heap_end = NULL;
blockHeader  *heap_current = NULL;

/*
 * Function for allocating 'size' bytes of heap memory.
 * Argument size: requested size for the payload
 * Returns address of allocated block (payload) on success.
 * Returns NULL on failure.
 *
 * This function must:
 * - Check size - Return NULL if size < 1 
 * - Determine block size rounding up to a multiple of 8 
 *   and possibly adding padding as a result.
 *
 * - Use BEST-FIT PLACEMENT POLICY to choose a free block
 *
 * - If the BEST-FIT block that is found is exact size match
 *   - 1. Update all heap blocks as needed for any affected blocks
 *   - 2. Return the address of the allocated block payload
 *
 * - If the BEST-FIT block that is found is large enough to split 
 *   - 1. SPLIT the free block into two valid heap blocks:
 *         1. an allocated block
 *         2. a free block
 *         NOTE: both blocks must meet heap block requirements 
 *       - Update all heap block header(s) and footer(s) 
 *              as needed for any affected blocks.
 *   - 2. Return the address of the allocated block payload
 *
 *   Return if NULL unable to find and allocate block for required size
 *
 * Note: payload address that is returned is NOT the address of the
 *       block header.  It is the address of the start of the 
 *       available memory for the requester.
 *
 * Tips: Be careful with pointer arithmetic and scale factors.
 */
void* balloc(int size) {
    //TODO: Your code goes in here.
    if (size < 1){  // illegal size
        return NULL;
    }

    if (heap_start == NULL){  // failed init_heap
        return NULL;
    }

    // record the time that head has been allocated
    // for the first time allocation, there is only one block free
    static int allocated_once = 0;
    //size_needed is the payload plus header
    int size_needed = size + 4;
    int min = 4096;  // ptr for comparison later to find proper mem block
    void* ptr = NULL;  // ptr that records address of ideal mem block
    int bestfit_size;  // int that records best-fit size of mem block
    blockHeader  *best_fit = NULL;  // ptr for best_fit
    blockHeader  *heap_split = NULL; // ptr for splitting blocks

    if ((size_needed % 8) != 0){
        // make size_needed divisible by 8
        size_needed += 8 - (size_needed % 8);
    }

    // allocate for first time allocation
    // I found that this first-time-allocation case might be some extra work
    // but I think it's okay :)
    if (allocated_once == 0){  //if a-bit is 0 (first-time allocation)
        // minus 2 for p-bit
        if ((heap_start->size_status - 2) < size_needed){
            return NULL;  // return null when there is not enough memory
        }
        allocated_once = 1;  // update this for successful first allocation
        heap_current = heap_start;  // the pointer for next allocation
        // declare the end of the heap
        heap_end = (blockHeader*)((void *)heap_start +
                heap_start->size_status - heap_start->size_status % 8);
        heap_end->size_status = 1; // mark the end of the heap's size 1
    }

    // allocate for non-first-time allocation， check for best fit
    else{
        best_fit = heap_start;  // search from the start of the heap
        // keep searching for best-fit until reach to the end
        // skip for allocated or non-best-fit blocks
        while ((best_fit->size_status & 1) == 1 ||
        (best_fit->size_status - (best_fit->size_status % 8)) !=
        size_needed) {
            best_fit = (blockHeader *) ((void *) best_fit +
                    best_fit->size_status - best_fit->size_status % 8);
            if (best_fit->size_status == 1) {
                // reach to the end and no best-fit found, reset to start
                best_fit = heap_start;
                break;
            }
        }
        // no best-fit found
        // look for the block that maximize memory utilization
        if (best_fit == heap_start){
            while (best_fit->size_status != 1){ // search till the end
                // skip allocated block
                if ((best_fit->size_status & 1) == 1){
                    // continue searching the rest of memory
                    best_fit = ((void *)best_fit +
                            best_fit->size_status -
                            best_fit->size_status % 8);
                    continue;
                }
                // search for the least size of block
                // that able to allocate, and mark its location
                if ((best_fit->size_status - size_needed) < min &&
                best_fit->size_status - size_needed > 0){
                    // record the size of best-fit
                    bestfit_size = best_fit->size_status;
                    // update the minimum block
                    min = best_fit->size_status - size_needed;
                    // update the location of best-fit
                    ptr = (void*)best_fit;
                    // continue searching for the rest of the memory
                    best_fit = (void*)best_fit +
                            best_fit->size_status -
                            best_fit->size_status % 8;
                }
                else{
                    best_fit = ((void *)best_fit +
                            best_fit->size_status -
                            best_fit->size_status % 8);
                }
            }
            if (ptr == NULL) return NULL; // no best-fit found ,return NULL
            // replace location of best_fit to recorded ptr
            best_fit = ptr;
            // replace size of best_fit to recorded bestfit_size
            best_fit->size_status = bestfit_size;
        }
        heap_current = best_fit; // update heap_current
    }

    // get payoff size and p-bit of the next allocation block
    int size_next = heap_current->size_status - heap_current->size_status % 8;
    int pbit = heap_current->size_status % 8;

    // return NULL for insufficient or allocated block
    if (size_next < size_needed || (heap_current->size_status & 1) == 1){
        return NULL;
    }

    // splitting the blocks if needed
    if (size_next > size_needed && (size_next - size_needed) % 8 == 0){
        // declare the split block that located after heap_current
        heap_split = (blockHeader*)((void*)heap_current + size_needed);
        // update size and p-bit
        heap_split->size_status = size_next - size_needed + 2;
        heap_current->size_status = size_needed + pbit;  // update heap_current
    }
    else{
        // declare the block after current block for np splitting case
        blockHeader *block_succ = (blockHeader*)((void*)heap_current +
                heap_current->size_status -
                heap_current->size_status % 8);
        if ((void*)block_succ < (void*)heap_end){
            // update-bit for block_succ
            block_succ->size_status += 2;
        }
        // when block_succ is beyond end, set it to NULL
        else{
            block_succ = NULL;
        }
    }

    // add footers
    blockHeader *heap_footer = (blockHeader*)((void*)heap_current +
            size_next - 4);
    if (size_needed == size_next){  // no space for footer
        heap_footer = NULL;
    }
    // update footer if there is space
    else{
        heap_footer->size_status = size_next - size_needed;
    }
    // finally, update a-bit and total size for heap_current
    heap_current->size_status = size_needed + pbit + 1;

    return (void*)heap_current + 4;  // return location of alloc
} 
 
/* 
 * Function for freeing up a previously allocated block.
 * Argument ptr: address of the block to be freed up.
 * Returns 0 on success.
 * Returns -1 on failure.
 * This function should:
 * - Return -1 if ptr is NULL.
 * - Return -1 if ptr is not a multiple of 8.
 * - Return -1 if ptr is outside the heap space.
 * - Return -1 if ptr block is already freed.
 * - Update header(s) and footer as needed.
 */                    
int bfree(void *ptr) {    
    if (ptr == NULL) return -1;  // check for NULL ptr
    if ((int)&ptr % 8 != 0) return -1;  // check for divisibility by 8
    // check for out of range
    if (ptr >= (void*)heap_end || ptr < (void*)heap_start) return -1;
    // check for already freed
    if ((((blockHeader*)(ptr - 4))->size_status & 1) == 0) return -1;
    // declare header given the payload
    blockHeader *header = (blockHeader*)(ptr - 4);

    // find location of the next header
    blockHeader *next_header = (blockHeader*)((void*)header +
            header->size_status -
            header->size_status % 8);
    next_header->size_status -= 2;  // set p-bit to 0 for next header

    // declare the block size (excluding p and a-bits)
    int size_free = header->size_status - header->size_status % 8;

    // initialize footer when block comes free
    // declare new footer pointer
    blockHeader *footer = (blockHeader *)((void*)header + size_free - 4);
    footer->size_status = size_free; // update footer
    header->size_status--; // update the a-bit

    return 0;  // success on returning 0
} 

/*
 * Function for traversing heap block list and coalescing all adjacent 
 * free blocks.
 *
 * This function is used for user-called coalescing.
 * Updated header size_status and footer size_status as needed.
 */
int coalesce() {
    //TODO: Your code goes in here.
    // declare first continuous free block
    blockHeader *first = heap_start;
    // declare second continuous free block
    blockHeader *second = (blockHeader *)((void*)heap_start +
            heap_start->size_status - heap_start->size_status % 8);

    // continue search for all following contiguous free blocks
    while (second->size_status != 1 && (char *)second <= (char*)heap_end){
        if ((first->size_status & 1) != 0 ||
        (second->size_status & 1) != 0){
            // skip for allocated non-continuous-free-blocks
            first = (blockHeader *)((void*)first +
                    first->size_status -
                    first->size_status % 8);
            second = (blockHeader*)((void*)second +
                    second->size_status -
                    second->size_status % 8);
            continue;  // skip allocated blocks
        }
        // found a continuous free block piece
        blockHeader *footer = NULL; // declare footer
        // declare the next block that comes free, if any
        blockHeader *next_free = (blockHeader*)((void*)second +
                second->size_status);
        //  declare size of sum of all free continuous blocks
        int size_accumulative = 0;
        // update size_accumulative
        size_accumulative += second->size_status;
        // search for next_free block
        while ((next_free->size_status & 1) == 0){
            footer = (void*)next_free - 4;
            footer = NULL;  //set extra footer to NULL
            // calculate the total free space
            size_accumulative += next_free->size_status;
            next_free = NULL;
            // update next_free
            next_free = (void*)second +
                    second->size_status +
                    size_accumulative;
        }
        // declare p-bit of first free block
        int p_bit = first->size_status % 8;
        // update the first free block
        first->size_status = p_bit +
                first->size_status +
                size_accumulative;
        // remove redundant footer
        footer = (void*)second - 4;
        footer = NULL;  // remove redundant footer
        second = NULL;  // remove redundant header
        // update location of first free block for next search
        first =
                (blockHeader*)((void*)first +
                               first->size_status -
                               first->size_status % 8);
        // update location of second free block for next search
        second = (blockHeader*)((void*)first +
                                first->size_status
                                - first->size_status % 8);
        // update footer
        footer = first - 4;
        footer->size_status = first->size_status - first->size_status % 8;
    }

	return 0;
}
 
/* 
 * Function used to initialize the memory allocator.
 * Intended to be called ONLY once by a program.
 * Argument sizeOfRegion: the size of the heap space to be allocated.
 * Returns 0 on success.
 * Returns -1 on failure.
 */                    
int init_heap(int sizeOfRegion) {    
 
    static int allocated_once = 0; //prevent multiple myInit calls
 
    int   pagesize; // page size
    int   padsize;  // size of padding when heap size not a multiple of page size
    void* mmap_ptr; // pointer to memory mapped area
    int   fd;

    blockHeader* end_mark;
  
    if (0 != allocated_once) {
        fprintf(stderr, 
        "Error:mem.c: InitHeap has allocated space during a previous call\n");
        return -1;
    }

    if (sizeOfRegion <= 0) {
        fprintf(stderr, "Error:mem.c: Requested block size is not positive\n");
        return -1;
    }

    // Get the pagesize from O.S. 
    pagesize = getpagesize();

    // Calculate padsize as the padding required to round up sizeOfRegion 
    // to a multiple of pagesize
    padsize = sizeOfRegion % pagesize;
    padsize = (pagesize - padsize) % pagesize;

    alloc_size = sizeOfRegion + padsize;

    // Using mmap to allocate memory
    fd = open("/dev/zero", O_RDWR);
    if (-1 == fd) {
        fprintf(stderr, "Error:mem.c: Cannot open /dev/zero\n");
        return -1;
    }
    mmap_ptr = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == mmap_ptr) {
        fprintf(stderr, "Error:mem.c: mmap cannot allocate space\n");
        allocated_once = 0;
        return -1;
    }
  
    allocated_once = 1;

    // for double word alignment and end mark
    alloc_size -= 8;

    // Initially there is only one big free block in the heap.
    // Skip first 4 bytes for double word alignment requirement.
    heap_start = (blockHeader*) mmap_ptr + 1;

    // Set the end mark
    end_mark = (blockHeader*)((void*)heap_start + alloc_size);
    end_mark->size_status = 1;

    // Set size in header
    heap_start->size_status = alloc_size;

    // Set p-bit as allocated in header
    // note a-bit left at 0 for free
    heap_start->size_status += 2;

    // Set the footer
    blockHeader *footer = (blockHeader*) ((void*)heap_start + alloc_size - 4);
    footer->size_status = alloc_size;
  
    return 0;
} 
                  
/* 
 * Function can be used for DEBUGGING to help you visualize your heap structure.
 * Traverses heap blocks and prints info about each block found.
 * 
 * Prints out a list of all the blocks including this information:
 * No.      : serial number of the block 
 * Status   : free/used (allocated)
 * Prev     : status of previous block free/used (allocated)
 * t_Begin  : address of the first byte in the block (where the header starts) 
 * t_End    : address of the last byte in the block 
 * t_Size   : size of the block as stored in the block header
 */                     
void disp_heap() {     
 
    int    counter;
    char   status[6];
    char   p_status[6];
    char * t_begin = NULL;
    char * t_end   = NULL;
    int    t_size;

    blockHeader *current = heap_start;
    counter = 1;

    int used_size =  0;
    int free_size =  0;
    int is_used   = -1;

    fprintf(stdout, 
	"*********************************** HEAP: Block List ****************************\n");
    fprintf(stdout, "No.\tStatus\tPrev\tt_Begin\t\tt_End\t\tt_Size\n");
    fprintf(stdout, 
	"---------------------------------------------------------------------------------\n");
  
    while (current->size_status != 1) {
        t_begin = (char*)current;
        t_size = current->size_status;
    
        if (t_size & 1) {
            // LSB = 1 => used block
            strcpy(status, "alloc");
            is_used = 1;
            t_size = t_size - 1;
        } else {
            strcpy(status, "FREE ");
            is_used = 0;
        }

        if (t_size & 2) {
            strcpy(p_status, "alloc");
            t_size = t_size - 2;
        } else {
            strcpy(p_status, "FREE ");
        }

        if (is_used) 
            used_size += t_size;
        else 
            free_size += t_size;

        t_end = t_begin + t_size - 1;
    
        fprintf(stdout, "%d\t%s\t%s\t0x%08lx\t0x%08lx\t%4i\n", counter, status, 
        p_status, (unsigned long int)t_begin, (unsigned long int)t_end, t_size);
    
        current = (blockHeader*)((char*)current + t_size);
        counter = counter + 1;
    }

    fprintf(stdout, 
	"---------------------------------------------------------------------------------\n");
    fprintf(stdout, 
	"*********************************************************************************\n");
    fprintf(stdout, "Total used size = %4d\n", used_size);
    fprintf(stdout, "Total free size = %4d\n", free_size);
    fprintf(stdout, "Total size      = %4d\n", used_size + free_size);
    fprintf(stdout, 
	"*********************************************************************************\n");
    fflush(stdout);

    return;  
}

// end p4Heap.c (Spring 2023)                                         


