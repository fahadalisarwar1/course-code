
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle mutexBus;

#define delayPeriod  (1000 / portTICK_PERIOD_MS)

void task1();
void task2();

void accessingMemory(char *str){
    printf("accesing memory by task :%s\n",str);
}

void app_main(void)
{

   // In this example, we are going to see how we can run tasks in FREE RTOS.
   

    xTaskCreate(&task1, "Task 1", 2048, NULL, 2, NULL);
    xTaskCreate(&task2, "Task 2", 2048, NULL, 2, NULL);

    /*
        if you remember, that individual tasks are running concurrently, 
        somtimes a situation arises when different tasks try to access the same resource, this can cause problems, 
        for example if task1 is writing to a pin, task2 should write to the same pin at the same time. 
        This can cause data corruption and other issues,
        Mutexes helps us avoid this situation by using some kind of locking mechanism, so before writing/accessing a certain resource,
        they put a lock on the resource, so as long as the lock is present, the other task is not able to modify/aceess the same resources.

        SEMAPHORE:
        a signalling mechanism.

    */
    

}

void task1(){
    mutexBus = xSemaphoreCreateMutex();

    while(1){
       

        if (xSemaphoreTake(mutexBus, delayPeriod)){
            printf("This is task 1\n");
            accessingMemory("task1");
            xSemaphoreGive(mutexBus);
       
        }else
        {
            printf("lock is present on the bus, can't access for task1\n");
        }
        
        vTaskDelay(delayPeriod);
    }
}

void task2(){
    mutexBus = xSemaphoreCreateMutex();
    while(1){
        
        
        if (xSemaphoreTake(mutexBus, delayPeriod)){
            printf("This is task 2\n");
            accessingMemory("task2");
            xSemaphoreGive(mutexBus);
       
        }else
        {
            printf("lock is present on the bus, cant access for task 2\n");
        }
      
        vTaskDelay(2*delayPeriod);
    }
}