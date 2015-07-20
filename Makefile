all:	heap.o radix_sort.o mergesort.o quicksort.o shellsort.o

heap.o: heap.c
	clang -g -o heap.o heap.c

radix_sort.o: radix_sort.c
	clang -g -o radix_sort.o radix_sort.c

mergesort.o: mergesort.c
	clang -g -o mergesort.o mergesort.c

quicksort.o: quicksort.c
	clang -g -o quicksort.o quicksort.c

shellsort.o: shellsort.c
	clang -g -o shellsort.o shellsort.c

clean:
	rm -rf *.o *~
