#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int num = atoi(argv[1]);

	while(num != 1) {
		int oldNum = num;
		if (num % 2) {
			//odd
			num = 3 * num + 1;
			printf("%d is ODD: %d\n", oldNum, num);
		} else {
			//even
			num /= 2;
			printf("%d is EVEN: %d\n", oldNum, num);
		}
	}

	return 0;
}
