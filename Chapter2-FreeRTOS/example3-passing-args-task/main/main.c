
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void task1(void * params);

void app_main(void)
{

   // In this example, we are going to see how we can run tasks in FREE RTOS.
   
    xTaskCreate(&task1, "Task 1", 2048, "This is the passed argument", 2, NULL);
    /*
        TaskFunction_t pvTaskCode:          The function to be called for creating the task
        const char *const pcName:           Custom name of the task
        const uint32_t usStackDepth:        Memory to be used by the task
        void *const pvParameters:           Arguments to be passed to the task
        UBaseType_t uxPriority:             Task priority, if we have multiple tasks running we can give priority to tasks
        TaskHandle_t *const pvCreatedTask:  Handler for task function
    */


}

void task1(void * params){

    while(1){
        
        printf("This is task 1 with argument : %s\n", (char *)params);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}