#include <stdio.h>

#define ARRAY_LEN(x)	sizeof(x)/sizeof(*x)

int array[] = { 23, 3, 56, 99, 2, 1, 5, 66, 33, 4 };

void display_array()
{
	for (int i = 0; i < ARRAY_LEN(array); i++) {
		printf("array[%d]: %d\n", i, array[i]);
	}
}

int find_gap_sequence()
{
	int h, nh;
       
	h = nh = 1;
	while (nh < ARRAY_LEN(array)) {
		h = nh;
		nh = 3*h+1;
	}
	return h;
}

void shellsort() 
{
	int h;

	h = find_gap_sequence();
	while (h > 0) {
		for(int outer = h; outer <= ARRAY_LEN(array); outer++) {
			int tmp, inner;
		       
			tmp = array[outer];
			inner = outer;
			while (inner >= h && array[inner - h] >= tmp) {
				array[inner] = array[inner-h];
				inner -= h;
			}
			array[inner] = tmp;
		}
		h = (h - 1) / 3;
	}
}

int main(int argv, char *argc[]) 
{
	shellsort();
	display_array();

	return 0;
}
