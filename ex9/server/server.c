#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/dispatch.h>
#include <sys/mman.h>
#include <sys/neutrino.h>


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

int main(int argc, char *argv[]) {

	set_priority(2);

	struct pid_data *data;
	struct data_buffer msg;


	int file_descriptor;
	file_descriptor = shm_open("/sharepid", O_RDWR | O_CREAT, S_IRWXU);
	ftruncate(file_descriptor, sizeof(data));
	data = mmap(0,sizeof(data), PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);

	pthread_mutexattr_t myattr;

	data->pid = getpid();

	printf("%d\n", getpid());

	pthread_mutexattr_init(&myattr);
	pthread_mutexattr_setpshared(&myattr, PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&data->pid_mutex, &myattr);

	int ch_id, rx_id;
	struct _msg_info msgInfo;
	ch_id = ChannelCreate(0);

	while(1) {
		memset(msg.str, 0, sizeof(msg.str));
		rx_id = MsgReceive(ch_id, msg.str, sizeof(msg.str), &msgInfo);
		printf("Server pri: %d, Client pri: %d\n", get_priority(), msgInfo.priority);
		printf("msg received: %s\n", msg.str);
		//Performing job for client
		printf("Working... \n");
		MsgReply(rx_id,EOK,msg.str,sizeof(msg.str));
	}

	return EXIT_SUCCESS;
}
