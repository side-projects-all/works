#include <stdio.h>

extern int test(int, int);

int test(int a, int b) {
	printf("here!\n");

	return a + b;
}
