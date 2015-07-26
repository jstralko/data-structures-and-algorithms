#include <stdio.h>

int heap_array[20];
int next_index = 0;
/*
 * Heaps are simple.
 *
 * parents must be higher order
 * than its children. Weak ordering.
 *
 * Max item is at the root.
 *
 * To traverse the heap:
 * (where x is zero based counting)
 * parent = (x - 1) / 2
 * left   = (2*x + 1
 * right  = (2*x + 2)
 */

int get_parent_index(int i)
{
	return (i - 1) >> 1;
}

int get_left_index(int i)
{
	return (i << 1) + 1;
}

int get_right_index(int i)
{
	return (i << 1) + 2;
}

void swap(int i, int j)
{
	int tmp;

	tmp = heap_array[i];
	heap_array[i] = heap_array[j];
	heap_array[j] = tmp;
}

void heapify(int i)
{
	int p;

	if (i == 0)
		return;
	
	p = get_parent_index(i);
	if (heap_array[p] < heap_array[i]) {
		swap(i, p);
		heapify(p);
	}	
}

/*
 * This is a slightly faster version of heapify 
 * (no recursion, and fewer copies)
 */
void trickle_up(int i)
{
	int saved, parent;

	saved = heap_array[i];
	parent = get_parent_index(i);

	while (i > 0 && 
		saved > heap_array[parent]) {
		
		heap_array[i] = heap_array[parent];
		i = parent;
		parent = get_parent_index(parent);
	}
	heap_array[i] = saved; 
}

void insert(int v)
{
	heap_array[next_index] = v;
	//heapify(next_index);
	trickle_up(next_index);
	next_index++;
}

void trickle_down(int i)
{
	int saved, left, right, parent;

	saved = heap_array[i];

	while (i < next_index/2) {
		left = get_left_index(i);
		right = get_right_index(i);
		
		if (right < next_index && 
			heap_array[right] > heap_array[left])
			parent = right;
		else
			parent = left;

		if (saved >= heap_array[parent])
			break;
		
		heap_array[i] = heap_array[parent];
		i = parent;
	}

	heap_array[i] = saved;
}

/*
 * remove is declared in stdio.h so
 * I had to name it remove_from_heap
 */
int remove_from_heap()
{
	int r;

	r = heap_array[0];
	heap_array[0] = heap_array[--next_index];
	trickle_down(0);

	return r;	
}

/*
 * Simple function to change the priority
 * of a index.
 */
void change(int index, int v)
{
	int old;

	if (index < 0 || index >= next_index)
		return;

	old = heap_array[index];
	heap_array[index] = v;

	if (old > v)
		trickle_down(index);
	else
		trickle_up(index);
}

void display_heap()
{
	int i;

	for(i = 0; i < next_index; i++) {
		printf("a[%d]: %d\n", i, heap_array[i]);
	}
}

int main(int argv, char *argc[])
{
	insert(10);
	insert(23);
	insert(1);
	insert(9);
	insert(33);
	insert(2);

	printf("Before the remove_from_heap\n");
	display_heap();
	
	remove_from_heap();

	printf("After the remove_from_heap\n");
	display_heap();

	return 0;
}
