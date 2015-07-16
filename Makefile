all:	heap.o radix_sort.o

heap.o: heap.c
	clang -g -o heap.o heap.c

radix_sort.o: radix_sort.c
	clang -g -o radix_sort.o radix_sort.c

clean:
	rm -rf *.o *~
