all:	heapsort.o radix_sort.o mergesort.o quicksort.o shellsort.o binarytree.o

heapsort.o: heapsort.c
	clang -g -o heapsort.o heapsort.c

radix_sort.o: radix_sort.c
	clang -g -o radix_sort.o radix_sort.c

mergesort.o: mergesort.c
	clang -g -o mergesort.o mergesort.c

quicksort.o: quicksort.c
	clang -g -o quicksort.o quicksort.c

shellsort.o: shellsort.c
	clang -g -o shellsort.o shellsort.c

binarytree.o: binarytree.c
	clang -g -o binarytree.o binarytree.c
clean:
	rm -rf *.o *~
