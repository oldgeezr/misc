#include "miniproject.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUF_LEN 		20
#define KP 				10.0
#define KI 				800.0
#define END 			500000UL // 500 ms
#define TICK 			2000UL // 6 ms
#define PERIOD 			((double)TICK/(1000*1000)) // 6 ms

#define WITH_SIGNAL 	1

pthread_mutex_t udp_mutex, y_mutex;
sem_t pi_sem;

#if WITH_SIGNAL
sem_t signal_sem;
#endif

double ref = 1.0;
double y = 0.0;

int run_listen = 1;
int run_pi = 1;

#if WITH_SIGNAL
int run_signal = 1;
#endif

struct udp_conn conn;

#if WITH_SIGNAL
void *signal_ack(void *arg)
{
	char msg[BUF_LEN];

	strcpy(msg, "SIGNAL_ACK");

	printf("Signal thread initialized\n");

	while(run_signal)
	{
		// Give signal acknowledgement
		sem_wait(&signal_sem);
		pthread_mutex_lock(&udp_mutex);
		udp_send(&conn, msg, strlen(msg)+1);
		pthread_mutex_unlock(&udp_mutex);
	}

	return 0;
}
#endif

void *udp_listen(void *arg)
{
	char buf[BUF_LEN];
	char *buf_number;
	int rx;

	printf("UDP listener thread initialized\n");

	while (run_listen) {

		// Receive system state
		rx = udp_receive(&conn, buf, BUF_LEN);

		if (rx > 0)
		{
			if(strstr(buf, "GET_ACK:") == buf)
			{
				// Get new y value
				buf_number = &buf[strlen("GET_ACK:")];
				pthread_mutex_lock(&y_mutex);
				y = atof(buf_number);
				pthread_mutex_unlock(&y_mutex);
				sem_post(&pi_sem);
			}
#if WITH_SIGNAL
			else if(strstr(buf, "SIGNAL") == buf)
			{
				// Run signal_handler
				sem_post(&signal_sem);
			}
#endif
		}
	}

	return 0;
}

void *pi_controller(void *arg)
{
	char msg[BUF_LEN];
	char output[BUF_LEN];
	double integral = 0.0;
	double u = 0.0;
	double error = 0.0;

	struct timespec sleep;

	printf("PI controller thread initialized\n");
	clock_gettime(CLOCK_REALTIME, &sleep);

	while (run_pi)
	{
		// Wait for new y value
		sem_wait(&pi_sem);
		// Calculate errortimespec_add_us(&sleep, TICK);
		pthread_mutex_lock(&y_mutex);
		error = ref - y;
		pthread_mutex_unlock(&y_mutex);

		// Calculate output
		integral = integral + (error*PERIOD);
		u = (KP*error) + (KI*integral);

		// Create output string
		snprintf(output,BUF_LEN,"%f",u);
		memset(msg, 0, BUF_LEN);
		strcat(msg, "SET:");
		strcat(msg, output);

		// Send calculated u value to server
		pthread_mutex_lock(&udp_mutex);
		udp_send(&conn, msg, strlen(msg)+1);
		pthread_mutex_unlock(&udp_mutex);

		timespec_add_us(&sleep, TICK);
		clock_nanosleep(&sleep);
	}

	return 0;
}

int main (void)
{
	int port = 9999;
	char *ip = "192.168.0.1";
	char msg[BUF_LEN];
	pthread_t pi, listener;

#if WITH_SIGNAL
	pthread_t signal_handler;
#endif

	struct timespec start, stop;

	// Init mutexes
	pthread_mutex_init(&y_mutex, NULL);
	pthread_mutex_init(&udp_mutex, NULL);

	sem_init(&pi_sem, 0 ,1);
#if WITH_SIGNAL
	sem_init(&signal_sem, 0, 1);
#endif

	// UDP init
	udp_init_client(&conn, port, ip);
	printf("UDP Client initialized\n");

	// Spawn  UDP listener
	pthread_create(&listener, NULL, udp_listen, NULL);

	// Send start command
	strcpy(msg, "START");
	pthread_mutex_lock(&udp_mutex);
	udp_send(&conn, msg, strlen(msg)+1);
	pthread_mutex_unlock(&udp_mutex);
	printf("START sent\n");

	// Spawn pi controller and signal acknowledger
	pthread_create(&pi, NULL, pi_controller, NULL);
#if WITH_SIGNAL
	pthread_create(&signal_handler, NULL, signal_ack, NULL);
#endif

	// Set get command
	strcpy(msg, "GET");

	// Init clocks
	clock_gettime(CLOCK_REALTIME, &start);
	clock_gettime(CLOCK_REALTIME, &stop);

	// Define run time
	timespec_add_us(&start, 0);
	timespec_add_us(&stop, END);

	while ((start.tv_sec <= stop.tv_sec) && (start.tv_nsec < stop.tv_nsec))
	{
		// Send get command
		pthread_mutex_lock(&udp_mutex);
		udp_send(&conn, msg, strlen(msg)+1);
		pthread_mutex_unlock(&udp_mutex);

		// Add timer TICK to start
		timespec_add_us(&start, TICK);
		// Wait for next tick
		clock_nanosleep(&start);
	}

	// Send stop command to server
	strcpy(msg, "STOP");
	udp_send(&conn, msg, strlen(msg)+1);
	printf("Stop sent\n");

	// Destroy mutexes
	pthread_mutex_destroy(&y_mutex);
	pthread_mutex_destroy(&udp_mutex);

	// Destroy semaphores
	sem_destroy(&pi_sem);
#if WITH_SIGNAL
	sem_destroy(&signal_sem);
#endif

	// Kill threads
	run_listen = 0;
	run_pi = 0;
#if WITH_SIGNAL
	run_signal = 0;
#endif

	// Join threads
	pthread_join(pi, NULL);
	pthread_join(listener, NULL);

#if WITH_SIGNAL
	pthread_join(signal_handler, NULL);
#endif

	// Close UDP
	udp_close(&conn);

	return 0;
}
