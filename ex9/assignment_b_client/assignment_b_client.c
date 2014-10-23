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
	struct data_buffer rx_buffer;

	memset(rx_buffer.str, 0, sizeof(rx_buffer.str));

	sprintf(msg.str, "Hei!");

	int file_descriptor;
	file_descriptor = shm_open("/sharepid", O_RDWR, S_IRWXU);
	data = mmap(0, sizeof(data), PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);


	int ch_id, rx_id, status;

	printf("%d\n", data->pid);

	ch_id = ConnectAttach(0, data->pid, 1, 0, 0);
	status = MsgSend(ch_id, msg.str, sizeof(msg.str), rx_buffer.str, sizeof(rx_buffer.str));

	ConnectDetach(ch_id);

	printf("Received message: %s\n", rx_buffer.str);
	return EXIT_SUCCESS;
}
