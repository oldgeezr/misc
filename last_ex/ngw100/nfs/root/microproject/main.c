#include "miniproject.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUF_LEN 50
#define KP 10.0
#define KI 800.0
#define END 500000UL // 500 ms
#define TICK 1000UL // 1 us
#define PERIOD 0.001

pthread_mutex_t udp_mutex, y_mutex;
double ref = 1.0;
double y = 0.0;

int run_listen = 1;
int run_pi = 1;

struct udp_conn conn;

void *udp_listen(void *arg) {

	char buf[BUF_LEN];
	char *buf_number;
	int rx;

	while (run_listen) {

		// Receive system state
		rx = udp_receive(&conn, buf, BUF_LEN);
		printf("System state received, rx = %d, buf = %s\n", rx, buf);

		if (rx > 0) {
			if(strstr(buf, "GET_ACK:") == buf) {
				printf("GOT ACK\n");
				buf_number = &buf[strlen("GET_ACK:")];
				pthread_mutex_lock(&y_mutex);
				printf("Listener acquired y_mutex\n");
				y = atof(buf_number);
				pthread_mutex_unlock(&y_mutex);
				printf("Listener released y_mutex\n");
				printf("Y stored\n");
				// printf("Buffer contents %s, length %d, masked: %f \n", buf, rx, number);
			}
		}
	}

	return 0;
}

void *pi_controller(void *arg) {

	char msg[BUF_LEN];
	char output[BUF_LEN];
	double integral = 0.0;
	double u = 0.0;
	double error = 0.0;

	struct timespec sleep;

	while (run_pi) {

		clock_gettime(CLOCK_REALTIME, &sleep);
		timespec_add_us(&sleep, TICK);

		// Calculate error
		pthread_mutex_lock(&y_mutex);
		printf("Pi acquired y_mutex\n");
		error = ref - y;
		pthread_mutex_unlock(&y_mutex);
		printf("Pi released y_mutex\n");
		printf("Error calculated, error = %f\n", error);

		// Calculate output
		integral = integral + (error*PERIOD);
		u = (KP*error) + (KI*integral);
		printf("Output calculated, u = %f\n", u);

		// Create output string
		snprintf(output,BUF_LEN,"%f",u);
		memset(msg, 0, BUF_LEN);
		strcat(msg, "SET:");
		strcat(msg, output);
		printf("Output concatenated, msg = %s\n", msg);

		// Send back to system
		pthread_mutex_lock(&udp_mutex);
		printf("Pi acquired udp_mutex\n");
		udp_send(&conn, msg, strlen(msg)+1);
		pthread_mutex_unlock(&udp_mutex);
		printf("Pi released udp_mutex\n");
		printf("Output sent\n");

		clock_nanosleep(&sleep);
	}

	return 0;
}

int main (void) {

	int port = 9999;
	char *ip = "192.168.0.1";
	char msg[BUF_LEN];
	pthread_t pi, listener;
	struct timespec start, stop;

	// Init mutexes
	pthread_mutex_init(&y_mutex, NULL);
	pthread_mutex_init(&udp_mutex, NULL);

	// UDP init
	udp_init_client(&conn, port, ip);
	printf("Initialized\n");

	// Spawn  udp listener
	pthread_create(&listener, NULL, udp_listen, NULL);

	// Send start command
	strcpy(msg, "START");
	pthread_mutex_lock(&udp_mutex);
	printf("Main acquired udp_mutex\n");
	udp_send(&conn, msg, strlen(msg)+1);
	pthread_mutex_unlock(&udp_mutex);
	printf("Main released udp_mutex\n");
	printf("Start sent\n");

	// Spawn pi controller and udp listener
	pthread_create(&pi, NULL, pi_controller, NULL);
	printf("Threads created\n");

	// Define run time
	clock_gettime(CLOCK_REALTIME, &stop);
	timespec_add_us(&stop, END);

	// Init start clock
	// clock_gettime(CLOCK_REALTIME, &start);
	// timespec_add_us(&stop, 0);

	// Set get command
	strcpy(msg, "GET");

	printf("Stop time: %lu\n", stop.tv_nsec);
	// printf("Start time: %lu\n", start.tv_nsec);

	do {

		printf("Start time: %lu\n", start.tv_nsec);

		// Define get period
		clock_gettime(CLOCK_REALTIME, &start);
		timespec_add_us(&start, TICK);
		printf("Ready to get some more\n");

		// Send get command
		pthread_mutex_lock(&udp_mutex);
		printf("Main acquired udp_mutex\n");
		udp_send(&conn, msg, strlen(msg)+1);
		pthread_mutex_unlock(&udp_mutex);
		printf("Main released udp_mutex\n");
		printf("Get sent\n");

		// Wait for next tick
		clock_nanosleep(&start);
	} while (start.tv_sec <= stop.tv_sec && start.tv_nsec < stop.tv_nsec);

	run_listen = 0;
	run_pi = 0;

	// Send stop command
	strcpy(msg, "STOP");
	udp_send(&conn, msg, strlen(msg)+1);
	printf("Stop sent\n");

	// Close UDP
	udp_close(&conn);

	pthread_join(pi, NULL);
	pthread_join(listener, NULL);

	pthread_mutex_destroy(&y_mutex);
	pthread_mutex_destroy(&udp_mutex);

	return 0;
}
