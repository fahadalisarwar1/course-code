
#include <stdio.h>
#include "esp_log.h"

void app_main(void)
{

/*
    In this example, we will learn how logging works for ESP-IDF

*/
    // you can set log levels d
    // esp_log_level_set("LOG", ESP_LOG_VERBOSE);
    ESP_LOGE("LOG", "This is an error log");  
    ESP_LOGW("LOG", "This is a warning log");
    ESP_LOGI("LOG", "This is info log");   
    ESP_LOGD("LOG", "This is debug log");
    ESP_LOGV("LOG", "this is verbose"); 

    ESP_LOGW("LOG2", "this is log 2");
    ESP_LOGD("LOG2", "debug");

    // TAGS are used for identifying different parts of the code. 
   

 

}