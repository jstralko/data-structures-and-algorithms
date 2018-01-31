all:	heapsort.o radix_sort.o mergesort.o quicksort.o \
	shellsort.o binarytree.o rbtree.o tree234.o \
	heap.o dfs.o bfs.o topo.o shortest_path.o

heapsort.o: heapsort.c
	clang -g -o heapsort.o heapsort.c

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

binarytree.o: binarytree.c
	clang -g -o binarytree.o binarytree.c

rbtree.o: rbtree.c
	clang -g -o rbtree.o rbtree.c

tree234.o: tree234.c
	clang -g -o tree234.o tree234.c

dfs.o:	dfs.c
	clang -g -o dfs.o dfs.c

bfs.o:	bfs.c
	clang -g -o bfs.o bfs.c

topo.o: topo.c
	clang -g -o topo.o topo.c

shortest_path.o: shortest_path.c
	clang -g -o shortest_path.o shortest_path.c

clean:
	rm -rf *.o *~ *.o.dSYM *.class
