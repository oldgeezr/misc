#include <pthread.h>
#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>

int running = 1;
int var1 = 0;
int var2 = 0;

void *func1(void *arg) {

	while(running) {
		var1++;
		var2 = var1;
	}

	return 0;
}

void *func2(void *arg) {

	int i;

	for (i = 0; i < 20; i++) {

		printf("Number 1 is %d, number 2 is %d\n", var1, var2);
		sleep(0.1);
	}

	running = 0;
	return 0;
}

int main(void) {

	pthread_t tid[2];

	pthread_create(&tid[0], NULL, func1, NULL);
	pthread_create(&tid[1], NULL, func2, NULL);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}
