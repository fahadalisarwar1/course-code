
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void app_main(void)
{

    printf("[+] This is a initialization\n");
    int i = 0;
    while (1)
        {
        printf("[+] This is a loop number %d\n", i++);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
        
        /* code */
    }
    

}