#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/dispatch.h>
#include <sys/mman.h>


struct pid_data{
	pthread_mutex_t pid_mutex;
	pid_t pid;
};

int main(int argc, char *argv[]) {

	struct pid_data *data;

	int file_descriptor;
	file_descriptor = shm_open("/sharepid", O_RDWR, S_IRWXU);
	data = mmap(0,sizeof(data), PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);

	pthread_mutexattr_t myattr;

	pthread_mutexattr_init(&myattr);
	pthread_mutexattr_setpshared(&myattr, PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&data->pid_mutex, &myattr);

	printf("Program A 2: %d", data->pid);
	return EXIT_SUCCESS;
}
