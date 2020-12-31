
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void task1();
void task2();

static TaskHandle_t handler = NULL;


void app_main(void)
{
   // In this example, we are going to see how we can send notifications from task 1 to task 2.
   // Task notifications require that we define a handler on the tasks.
   // In our case, we will define a handler on task2(receiver) which the task 1 will utilize.
   

    xTaskCreate(&task2, "Task 2", 2048, NULL, 2, &handler);   
    xTaskCreate(&task1, "Task 1", 2048, NULL, 2, NULL); 

}

void task1(void * params){

    while(1){
        // printf("sending notification\n");
        xTaskNotifyGive(handler);
        xTaskNotifyGive(handler);
        xTaskNotifyGive(handler);
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }
}

void task2(void * params){

    while(1){
        int count = ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // This is a blocking function, i.e execution will stop here until the notification is
        //   received. 
        printf("Received Notification count %d\n", count);
    }
}