#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/dispatch.h>
#include <sys/mman.h>
#include <pthread.h>

#define NUMBER_OF_THREADS 4

struct pid_data{
	pthread_mutex_t pid_mutex;
	pid_t pid;
};

struct data_buffer{
	char str[255];
};

int set_priority(int priority) {
	int policy;
	struct sched_param param;
	if (priority < 1 || priority > 63) return -1;
	pthread_getschedparam(pthread_self(), &policy, &param);
	param.sched_priority = priority;
	return pthread_setschedparam(pthread_self(), policy, &param);
}

int get_priority() {
	int policy;
	struct sched_param param;
	pthread_getschedparam(pthread_self(), &policy, &param);
	return param.sched_curpriority;
}

void *send_msg(void *arg) {
	struct pid_data *data;
	struct data_buffer msg;
	struct data_buffer rx_buffer;
	int priority = (int)arg + 1;

	printf("pri: %d\n", priority);

	set_priority(priority);

	memset(rx_buffer.str, 0, sizeof(rx_buffer.str));

	sprintf(msg.str, "Hei from client: %d \n", priority);

	int file_descriptor = shm_open("/sharepid", O_RDWR, S_IRWXU);
	data = mmap(0, sizeof(data), PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);

	int ch_id, status;

	printf("%d\n", data->pid);

	ch_id = ConnectAttach(0, data->pid, 1, 0, 0);
	status = MsgSend(ch_id, msg.str, sizeof(msg.str), rx_buffer.str, sizeof(rx_buffer.str));

	ConnectDetach(ch_id);

	printf("Received message: %s\n", rx_buffer.str);

	return 0;
}

int main(int argc, char *argv[]) {

	set_priority(10);

	int i;
	pthread_t threads[NUMBER_OF_THREADS];

	//Create threads
	for(i = 0; i < NUMBER_OF_THREADS; i++) {
		printf("Creating thread %d\n", i);
		pthread_create(&threads[i], NULL, send_msg, (void *)i);
	}

	void *status;

	//Join threads
	for(i = 0; i < NUMBER_OF_THREADS; i++) {
		pthread_join(threads[i], &status);
	}

	printf("I'm done\n");
	return EXIT_SUCCESS;
}
