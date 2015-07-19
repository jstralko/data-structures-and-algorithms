#include <stdio.h>

int array[] = { 2, 3, 6, 1, 9, 5, 12, 11, 23 };

//TODO: use Sedgewick method for choosing pivot
int choosePivot(int lo, int hi)
{
	return ((hi-lo)/2)+lo;			
}

void swap(int a, int b)
{
	int tmp;

	tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}

void print_array()
{
	for(int i = 0; i < 9; i ++) {
		printf("a[%d]: %d\n", i, array[i]);			
	}
}

int partition(int lo, int hi)
{
	int pivotIndex;
	int pivotValue;
	int storeIndex;

	pivotIndex = choosePivot(lo, hi);
	pivotValue = array[pivotIndex];

	printf("pivot choosen: a[%d]:%d\n", pivotIndex, pivotValue);
	
	/* move pivot out of the way and 
	 * swap it at the end
	 */
	swap(pivotIndex, hi);
	storeIndex = lo;

	for(int i = lo; i < hi; i++) {
		if (array[i] < pivotValue) {
			swap(i, storeIndex);
			storeIndex++;
		}
	}
	swap(storeIndex, hi);
	return storeIndex;
}

void quicksort(int lo, int hi)
{
	int p;
	if (lo < hi) {
		p = partition(lo, hi);
		quicksort(lo, p-1);
		quicksort(p+1, hi);
	}
}

int main(int argv, char *argc[]) 
{
	quicksort(0, 8);
	print_array();
	return 0;
}
