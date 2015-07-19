#include <stdio.h>

int array[] = { 23, 67, 8, 1, 2, 5, 3, 99, 12, 9 }; 
int array2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#define ARRAYSIZE(x) (sizeof(x)/sizeof(*x))

void print_array()
{
	for (int i = 0; i < ARRAYSIZE(array); i++) {
		printf("a[%d]: %d\n", i, array[i]);
	}
}

void copy_array(int begin, int end)
{
	for (int i = begin; i < end; i++) {
		array[i] = array2[i];
	}
}

/*
 * left half is a[begin to middle - 1]
 * right half is a[middle to end - 1]
 */
void merge(int begin, int middle, int end)
{
	int i, j;

	i = begin;
	j = middle;

	for (int k = begin; k < end; k++) {
		if (i < middle && 
			(j >= end || array[i] <= array[j])) {
			array2[k] = array[i];
			i++;
		} else {
			array2[k] = array[j];
			j++;
		}
	}
}

void merge_split(int begin, int len)
{
	int middle;
	
	if (len - begin < 2)
		return;

	middle = ((len - begin) / 2) + begin;

	merge_split(begin, middle);
	merge_split(middle, len);

	merge(begin, middle, len);
	copy_array(begin, len);
}

int main(int argv, char *argc[])
{
	merge_split(0, ARRAYSIZE(array));

	print_array();

	return 0;
}
