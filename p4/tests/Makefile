C_FILES := $(wildcard *.c)
TARGETS := ${C_FILES:.c=}

all: ${TARGETS}

# Build each TARGET from its corresponding C source file
%: %.c
	gcc -I.. -g -m64 -Xlinker -rpath=.. -o $@ $< -L.. -lheap -std=gnu99

# Run the tests that only require allocating space on the heap
partA:
	./test_alloc1.c
	./test_alloc1_nospace
	./test_writeable
	./test_align1
	./test_alloc2
	./test_alloc2_nospace
	./test_align2
	./test_alloc3
	./test_align3

# Run the tests that require allocating space on the heap and freeing works
partB:
	./test_free1
	./test_free2
	./test_fit1
	./test_fit1_nospace
	./test_fit2
	./test_fit2_nospace

# Run the tests that require allocating, freeing, and coalescing  works
partC:
	./test_coalesce1
	./test_coalesce2
	./test_coalesce3

# Remove all generated target files (executables)
# Use before running make to get a clean re-build of all targets.
clean:
	rm -rf ${TARGETS} *.o

