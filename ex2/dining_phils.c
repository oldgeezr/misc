#include <pthread.h>
#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <semaphore.h>

#define N 3

static sem_t forks[N];

void *dine(void *arg) {

	int phil = (int) arg;
	int left = phil;
	int right = ((phil-1)+N)%N;

	while (1) {
		sem_wait(&forks[left]);
		printf("Phil[%d] picking up %d\n", phil, left);
		sleep(1);
		sem_wait(&forks[right]);
		printf("Phil[%d] picking up %d\n", phil, right);
		printf("Dining...\n");
		sleep(0.5);
		sem_post(&forks[right]);
		printf("Phil[%d] putting down %d\n", phil, right);
		sleep(1);
		sem_post(&forks[left]);
		printf("Phil[%d] putting down %d\n\n", phil, left);
		sleep(5);
	}
	return 0;
}

void *dine_corr(void *arg) {

	int phil = (int) arg;
	int left = phil;
	int right = ((phil-1)+N)%N;

	while (1) {
		sem_wait(&forks[right]);
		printf("Phil[%d] picking up %d\n", phil, right);
		sleep(0.5);
		sem_wait(&forks[left]);
		printf("Phil[%d] picking up %d\n", phil, left);
		printf("Dining...\n");
		sleep(1);
		sem_post(&forks[left]);
		printf("Phil[%d] putting down %d\n\n", phil, left);
		sleep(0.5);
		sem_post(&forks[right]);
		printf("Phil[%d] putting down %d\n", phil, right);
		sleep(5);
	}
	return 0;
}

int main(void) {

	int deadlock = 0;

	pthread_t phils[N];

	int i;

	for (i = 0; i < N; i++) {

		sem_init(&forks[i], 0, 1);
	}

	for (i = 0; i < N; i++) {
		
		if (!deadlock && i == N-1) { 
			pthread_create(&phils[i], NULL, dine_corr, (void *)i);
		} else {
			pthread_create(&phils[i], NULL, dine, (void *) i);
		}
	}

	for (i = 0; i < N; i++) {
		
		pthread_join(phils[i], NULL);
	}
	return 0;
}
