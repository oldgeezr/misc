#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void allocate(int value) {
	int *ptr = NULL;
	ptr = malloc(100000 * sizeof(int));
	ptr = NULL;
	if (ptr == NULL) {
		perror("Malloc returned NULL");
	} else {
		*ptr = value;
		printf("test of allocated memory: %d\n", *ptr);
	}
}

int main(void) {
	// while(1) {
	allocate(2);
	// }
	return 0;
}
