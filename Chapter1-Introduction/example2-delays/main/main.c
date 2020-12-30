
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void app_main(void)
{

    int i =0;
    while (1)
        {
        printf("[+] This is a loop number %d\n", i++);
        vTaskDelay(1000/ portTICK_PERIOD_MS); // portTICK_PERIOD_MS translates clock frequency to MS , portTICK_PERIOD_MS = 1000;
        // vTaskDelay comes from FREERTOS. v means that the function returns void. 
        /* code */
    }
    

}