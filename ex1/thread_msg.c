#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t tid[2];

void *dosomething(void *arg) {
	
	unsigned long i = 0;
	pthread_t id = pthread_self();

	if (pthread_equal(id ,tid[0])) {
		printf("LOL");
	} else {
		printf("AGAIN");
	}

	for (i = 0; i < (0xFFFF_FFFF); i++);

	return NULL;
}

int main(void) {

	int i = 0;
	int err;

	while (i < 2) {

		err = pthread_create(&tid[i], NULL, &dosomthing, NULL);
		if (err != 0) {
			printf("ERROR");
		} else {
			pritf("BLA");
		}

		i++;
	}

	sleep(5);
	return 0;

}
