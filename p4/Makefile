# Create the shared object libheap.so file
# 1. Compile p4Heap.c to create p4Heap.o    (ROF)
# 2. Make it a shared object file for tests/ (SOF)
p4Heap: p4Heap.c p4Heap.h
	gcc -g -c -Wall -m32 -fpic p4Heap.c
	gcc -shared -Wall -m32 -o libheap.so p4Heap.o

clean:
	rm -rf p4Heap.o libheap.so
