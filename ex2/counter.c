#include <stdio.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>

int global_var = 0;

int main(void) {

	// pid_t err;

	fork();
	// vfork();

	int local_var = 0;
	while(local_var < 10) {
		
		printf("Global: %d, Local: %d\n", global_var, local_var);
		global_var++;
		local_var++;
		sleep(0.1);
	}
	return 0;
}
