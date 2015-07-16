#include <stdio.h>

#define ARRAY_LEN(x) sizeof(x)/sizeof(*x)
#define RADIX	10
/*
 * Radiux Sort Big-O(kn)
 */
int array[] = { 359, 383, 548, 911, 479, 599 };
int buckets[RADIX][ARRAY_LEN(array)];

void print_array()
{
	for(int i = 0; i < ARRAY_LEN(array); i++) {
		printf("a[%d]: %d\n", i, array[i]);
	}
}

void radix_sort(int placement)
{
	int bucket_cnt[RADIX] = { 0 };
	int stored_index;
	
	stored_index = 0;
	for (int i = 0; i < ARRAY_LEN(array); i++) {
		int tmp, cipher;
	       
		tmp = array[i] / placement;
		cipher = tmp % RADIX;
		
		stored_index = bucket_cnt[cipher];
		buckets[cipher][stored_index] = array[i];

		bucket_cnt[cipher] = ++stored_index;
	}

	int k = 0;
	for (int i = 0; i < RADIX; i++) {
		for (int j = 0; j < bucket_cnt[i]; j++) {
			array[k] = buckets[i][j];
			k++;	
		}
	}
}

int main(int argv, char *argc[])
{

	int placement = 1;
	radix_sort(1);

	placement *= RADIX;
	radix_sort(placement);

	placement *= RADIX;
	radix_sort(placement);
	
	print_array();
	return 0;
}
