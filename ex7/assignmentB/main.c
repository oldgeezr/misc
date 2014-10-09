#include "io.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>

#include <rtdk.h>
#include <native/task.h>
#include <native/timer.h>
#include <native/sem.h>

#define SEM_INIT 0       /* Initial semaphore count */
#define SEM_MODE S_FIFO  /* Wait by FIFO order */

#define TIME_UNIT_MS (100UL)
#define TIME_UNIT_NS (TIME_UNIT_MS*1000UL*1000UL)

RT_SEM sem_desc;

void busy_wait_ms(unsigned long delay){
        unsigned long count = 0;
        while (count <= delay*10){
                rt_timer_spin(1000*100);
                count++;
        }
}


void task1_impl(void *arg)
{
        //rt_sem_p(&sem_desc,TM_INFINITE);
        rt_printf("Task1 started\n");
        for(;;) 
        {
                rt_sem_p(&sem_desc,TM_INFINITE);
                busy_wait_ms(3*TIME_UNIT_MS);
                rt_printf("Task1 did stuff\n");
                rt_sem_v(&sem_desc);
        }
}

void task2_impl(void *arg)
{
        //rt_sem_p(&sem_desc,TM_INFINITE);
        rt_printf("Task2 started\n");
        for(;;) 
        {
                rt_task_sleep(1*TIME_UNIT_NS);
                //busy_wait_ms(5*TIME_UNIT_MS);
                rt_printf("Task2 did stuff\n");
        }
}


void task3_impl(void *arg)
{
        //rt_sem_p(&sem_desc,TM_INFINITE);
        rt_printf("Task3 started\n");
        for(;;) 
        {
                rt_task_sleep(2*TIME_UNIT_NS);
                rt_sem_p(&sem_desc,TM_INFINITE);
                busy_wait_ms(2*TIME_UNIT_MS);
                rt_printf("Task3 did stuff\n");
                rt_sem_v(&sem_desc);
        }
}


void catch_signal(int sig)
{
}

int main() 
{
        signal(SIGTERM, catch_signal);
        signal(SIGINT, catch_signal);
        
        /* Avoids memory swapping for this program */
        mlockall(MCL_CURRENT|MCL_FUTURE);
        rt_print_auto_init(1);
        
        int res = io_init();
        if(res != 1) 
        {
        puts("Could not start io library.");
        }
        
        rt_sem_create(&sem_desc,"task_sem",SEM_INIT,SEM_MODE);
        
        RT_TASK task1,task2,task3;
        rt_task_create(&task1, "task1", 0, 10, 0);
        rt_task_create(&task2, "task2", 0, 20, 0);
        rt_task_create(&task3, "task3", 0, 50, 0);
        
        rt_task_start(&task1, &task1_impl, NULL);
        rt_task_start(&task2, &task2_impl, NULL);
        rt_task_start(&task3, &task3_impl, NULL);
        
        usleep(500);
        rt_sem_v(&sem_desc);
        
        pause();
        
        rt_task_join(&task3);
        rt_task_join(&task2);
        rt_task_join(&task1);
        
        rt_task_delete(&task1);
        rt_task_delete(&task2);
        rt_task_delete(&task3);
        
        rt_sem_delete(&sem_desc);
        
        return 1;
}