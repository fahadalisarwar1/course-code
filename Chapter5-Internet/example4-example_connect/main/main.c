#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_http_client.h"
#include "protocol_examples_common.h"

esp_err_t cb_event(esp_http_client_event_t * event){
    switch (event->event_id)
    {
    case HTTP_EVENT_ON_DATA:/* constant-expression */:
        /* code */
        printf("$/*s\n", event-> data_len, (char *)event -> data);
        break;
    }
    return ESP_OK;
}

void app_main(void)
{   /*
    to run this example, you need to use "protocol_example_common" component located in esp-idf/examples/common_components/protocol_examples_common
    Copy this component in the components folder in your project.
    This has a special function called example connect. 
    example_connect simplifies the connection procedures
    It uses the wifi configuration setup in menuconfig. 
*/
    printf("In this example we are going to learn how to connect to internet\n");
    esp_err_t err =  nvs_flash_init();
    ESP_ERROR_CHECK(err);

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    example_connect();

    // once connected, we should see the IP address .

    // Now we will request google.com and print the result. 
    esp_http_client_config_t clientConfig = {
        .url = "www.google.com",
        .event_handler = cb_event,

    };

    esp_http_client_handle_t ClientHandler = esp_http_client_init(&clientConfig);
    esp_http_client_perform(ClientHandler);
    esp_http_client_cleanup(ClientHandler);






}
