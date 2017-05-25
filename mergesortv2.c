#include <stdio.h>

int array[] = { 3, 4, 2, 7, 5, 8, 9, 0, 6 };
int array2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#define ARRAYSIZE(x) (sizeof(x)/sizeof(*x))

void print_array()
{
	for (int i = 0; i < ARRAYSIZE(array2); i++) {
		printf("%d, ", array[i]);
	}
	printf("\n");
}

//Think tree inorder traversal
void merge(int start, const int mid, const int end)
{
	const int start_start = start;
	int high_start = mid + 1;
	int array2_start = start;

	//printf("start: %d mid: %d end: %d\n", start, mid, end);

	//merge subarray into array2
	while (start <= mid && high_start <= end) {
		if (array[start] > array[high_start]) {
			array2[array2_start++] = array[high_start++];
		} else {
			array2[array2_start++] = array[start++];
		}
	}

	while (start <= mid) {
		array2[array2_start++] = array[start++];
	}

	while (high_start <= end) {
		array2[array2_start++] = array[high_start++];
	}

	//Copy merged array2 into orignal array.
	for (int i = start_start; i <= end; i++) {
		array[i] = array2[i];
	}
}

void mergesort(int start, int end)
{
	if (start == end) return; //one item is considered sorted.

	int mid = (start + end) / 2;

	mergesort(start, mid);
	mergesort(mid + 1, end);
	//We have 2 subarrays:
	//	- Merge: [0] and [1] = [01]
	//					 [12] and [34] = [1234]
	//					 [1234] and [5678] = [12345678]
	//					 [and so on...]
	merge(start, mid, end);
}

int main(int argv, char *argc[])
{
	mergesort(0, ARRAYSIZE(array) - 1);
	print_array();

	return 0;
}
