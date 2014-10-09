#include "io.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>

#include <rtdk.h>
#include <native/task.h>
#include <native/timer.h>
#include <native/sem.h>

#define SEM_INIT 1       /* Initial semaphore count */
#define SEM_MODE S_FIFO  /* Wait by FIFO order */

RT_SEM sem_desc;

void task1_impl(void *arg)
{
        for(;;) 
        {
                /* Now, wait for a semaphore unit... */
                rt_sem_p(&sem_desc,TM_INFINITE);
                rt_printf("Task1 did stuff\n");
        }
}

void task2_impl(void *arg)
{
        for(;;) 
        {
                /* Now, wait for a semaphore unit... */
                rt_sem_p(&sem_desc,TM_INFINITE);
                rt_printf("Task2 did stuff\n");
        }
}


void task3_impl(void *arg)
{
        RTIME now, previous;

        /*
         * Arguments: &task (NULL=self),
         *            start time,
         *            period (here: 1 s)
         */
        rt_task_set_periodic(NULL, TM_NOW, 1000000000);
        previous = rt_timer_read();

        while (1) {
                rt_task_wait_period(NULL);
                now = rt_timer_read();
                rt_sem_broadcast(&sem_desc);
                
                rt_printf("Time since last turn: %ld.%06ld ms\n",
                       (long)(now - previous) / 1000000,
                       (long)(now - previous) % 1000000);
                       previous = now;
		
        }
}


int main() 
{
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