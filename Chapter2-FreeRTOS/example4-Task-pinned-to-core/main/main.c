
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void task1(void * params);

void app_main(void)
{

   // In this example, we are going to see how we can run tasks in FREE RTOS.
    // ESP-32 has two cores. Core 0 is usually used for user defined logic.
    // Core 1 is used for background tasks like WIFI, Communication etc. 
    // Last argument lets us set core 
    // Cores start at 0 index, by default xTaskCreate() uses core 0, so xTaskCreate() and xTaskCreatePinnedToCore(0) are equal.

    xTaskCreatePinnedToCore(&task1, "Task 1", 2048, "core 2", 2, NULL, 1);
    
}

void task1(void * params){

    while(1){
        
        printf("This is task running on : %s\n", (char *)params);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}