#include <stdio.h>
#include <pthread.h>
#include <sys/times.h>

int global_var = 7;

void *decrementor(void *var) {
	
	int *local_var = (int *)var;

	while(*local_var > 0) {
		
		// sleep(0.5);
		global_var--;
		(*local_var)--;
	}
	return 0;
}

int main(void) {

	int local_var_1 = 2;
	int local_var_2 = 5;

	pthread_t tid[2];

	pthread_create(&tid[0], NULL, decrementor, &local_var_1);
	pthread_create(&tid[1], NULL, decrementor, &local_var_2);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	printf("Global: %d, Local1: %d, Local2: %d\n", global_var, local_var_1, local_var_2);	

	return 0;
}
