#include <stdio.h>

#define ARRAYSIZE(x) sizeof(x)/sizeof(*x)
int array[] = { 10, 34, 1, 6, 3, 2, 12, 77 };

int right_index(int x) 
{
	return (x << 1) + 2;
}

int left_index(int x)
{
	return (x << 1) + 1;
}

int parent_index(int x)
{
	//floor
	return (x - 1) >> 1;
}

void swap(int a, int b) 
{
	int tmp;
	
	tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}

void insert_into_heap(int index) 
{
	int p_index;

	p_index = parent_index(index);
	if (p_index == index) return;

	if (array[index] >= array[p_index]) {
		swap(index, p_index);
		insert_into_heap(p_index);
	}
}

void print_array()
{
	for (int i = 0; i < ARRAYSIZE(array); i++) {
		printf("array[%d]: %d\n", i, array[i]);
	}
}

void heapify()
{
	int next_heap_index = 1;
	for (int i = 1; i < ARRAYSIZE(array); i++) {
		insert_into_heap(next_heap_index);
		next_heap_index++;
	}
}

void sift_down(int len) 
{
	int root, cur;
	int left, right;

	root = cur = 0;
	while (left_index(root) < len) {
		left = left_index(cur);
		right = right_index(cur);
		
		if (array[cur] < array[left]) {
			cur = left;
		}
		
		if (right < len && array[cur] < array[right]) {
			cur = right;
		}

		if (cur == root) return;

		swap(root, cur);
		root = cur;
	}
}

void heap_sort()
{
	int len;

	heapify();
	len = ARRAYSIZE(array);
	//sort now that we have a heap
	do {
		swap(0, len-1);
		len--;
		sift_down(len);
	} while(len > 0);
}

int main(int argv, char *argc[]) 
{
	heap_sort();
	print_array();
	return 0;
}
