
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void task1();
void task2();

static TaskHandle_t handler = NULL;


void app_main(void)
{

   /*  
        In this example, we are going to see how we can send basic data to the task using notifications. 
        The data will be very basic.
        In our previous example, we sent multiple notifications, however we only got the count at the receiver,
        What if we want to know which notification was actually triggered. 

   */

   

    xTaskCreate(&task2, "Task 2", 2048, NULL, 2, &handler);   
    xTaskCreate(&task1, "Task 1", 2048, NULL, 2, NULL); 

}

void task1(void * params){

    while(1){
        // printf("sending notification\n");
        // we can send a 32 bit value using this notification
        // 1 2 and 4 are different states, which could indicate some meaningful values.
        xTaskNotify(handler, 1, eSetValueWithOverwrite);

        // eSetNotificationOVerwrite sets the task's notification value to a specific value even if the previous values
        // hasn't been read by the task. 
        vTaskDelay(5000/portTICK_PERIOD_MS);
        xTaskNotify(handler, 2, eSetValueWithOverwrite);
        vTaskDelay(5000/portTICK_PERIOD_MS);
        xTaskNotify(handler, 4, eSetValueWithOverwrite);
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }
}

void task2(void * params){

    while(1){
        uint32_t state;
        xTaskNotifyWait(0, 0, &state, portMAX_DELAY);

        printf("Received State %d\n", state);
    }
}