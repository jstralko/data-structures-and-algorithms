all:	heap.o radix_sort.o mergesort.o quicksort.o

heap.o: heap.c
	clang -g -o heap.o heap.c

radix_sort.o: radix_sort.c
	clang -g -o radix_sort.o radix_sort.c

mergesort.o: mergesort.c
	clang -g -o mergesort.o mergesort.c

quicksort.o: quicksort.c
	clang -g -o quicksort.o quicksort.c

clean:
	rm -rf *.o *~
