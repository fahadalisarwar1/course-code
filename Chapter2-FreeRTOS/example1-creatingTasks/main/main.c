
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void task1(){
    printf("This is exiting task 1\n");

    // This code will cause the controller to panic. 
}

void app_main(void)
{

   // In this example, we are going to see how we can run tasks in FREE RTOS.
   
    xTaskCreate(&task1, "Task 1", 2048, NULL, 2, NULL);
    /*
        TaskFunction_t pvTaskCode:          The function to be called for creating the task
        const char *const pcName:           Custom name of the task
        const uint32_t usStackDepth:        Memory to be used by the task
        void *const pvParameters:           Arguments to be passed to the task
        UBaseType_t uxPriority:             Task priority, if we have multiple tasks running we can give priority to tasks
        TaskHandle_t *const pvCreatedTask:  Handler for task function

        Example 1: Exiting Task - DONT DO THIS
                
                // Tasks shouldn't exit i.e the control shouldn't return from tasks otherwise it will put 
                // microcontroller in panic mode and it will keep resetting 
                // This an exiting task meaning that control goes out of the task when it finishes,
        Example 2: Exiting task with Delete - NOT RECOMMENDED
                void task1(){
                    printf("This is exiting task 1\n");
                    vTaskDelete(NULL);
                }
        Example 3: Proper task definition - RECOMMENDED
                void task1(){
                    while(1){
                        printf("This is proper task\n");
                    }
                }
    */
    

}