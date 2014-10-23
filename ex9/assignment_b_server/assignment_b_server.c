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

struct data_buffer{
	char str[255];
};

int main(int argc, char *argv[]) {

	struct pid_data *data;
	struct data_buffer msg;

	memset(msg.str, 0, sizeof(msg.str));

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
	ch_id = ChannelCreate(0);
	rx_id = MsgReceive(ch_id, msg.str, sizeof(msg.str),NULL);
	//Performing job for client
	printf("Working... \n");
	MsgReply(rx_id,EOK,msg.str,sizeof(msg.str));

	printf("msg received: %s\n", msg.str);
	return EXIT_SUCCESS;
}
