
#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_err.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"


#define SSID "ALTICE-C02F"
#define PASS "474E32G0DDJ"



/*
    In this example we will learn how to connect to an Access point using ESP32
*/

xSemaphoreHandle OnConnectionHandler;

static esp_err_t event_handler(void *ctx, system_event_t *event){


    switch(event -> event_id){
        case SYSTEM_EVENT_STA_START:
            esp_wifi_connect();
            printf("[+] connecting to %s\n", SSID);
            break;
        case SYSTEM_EVENT_STA_CONNECTED:
            printf("[+] Connected to AP: %s\n", SSID);
            printf("Memory available on Stack: %d\n", uxTaskGetStackHighWaterMark(NULL));
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            printf("[+] Got IP Address from DHCP: %s\n", SSID);
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            printf("[+] Disconnected from AP\n");
            break;
        default:
            printf("[+] Exiting\n");
            break;

    };
    return ESP_OK;
}


void wifi_intilaization(){
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
    // Initialize the underlying TCP/IP stack.
    printf("[+] Initialize the underlying TCP/IP stack \n");
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t wifi_init_cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = SSID,
            .password = PASS
        }
    };

    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    esp_err_t err = esp_event_loop_init(event_handler, NULL);
    ESP_ERROR_CHECK(err);
    ESP_ERROR_CHECK(esp_wifi_start()); // starting wifi
    printf("[+] Wifi Initialization complete.\n");
    
}
void OnConnected(void * params){
    if (xSemaphoreTake(OnConnectionHandler, 10 * 1000/portTICK_PERIOD_MS)){
        printf("Connection Established\n");
        xSemaphoreTake(OnConnectionHandler, portMAX_DELAY);
        
    }else{
        esp_restart();
    }
}


void app_main(void)
{

    OnConnectionHandler = xSemaphoreCreateBinary();
    wifi_intilaization();
    xTaskCreate(
        &OnConnected,
        "On Connected",
        1024*10,
        NULL,
        5,
        NULL
    );
}