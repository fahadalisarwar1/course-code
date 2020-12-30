
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h" // this file will help us to generate random number.
#include "esp_log.h"

void app_main(void)
{

    // 


    while(1){
        int random = esp_random();
        ESP_LOGI("RANDOM", "%d", random);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }

}