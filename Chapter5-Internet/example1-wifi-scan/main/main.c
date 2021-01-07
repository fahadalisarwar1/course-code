
#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_err.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"

#define MAX_AP 20


void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
    // Initialize the underlying TCP/IP stack.
    printf("[+] Initialize the underlying TCP/IP stack \n");
    ESP_ERROR_CHECK(esp_netif_init());
    /*
        esp_err_t esp_netif_init(void)
        Initialize the underlying TCP/IP stack.

        Return
        ESP_OK on success

        ESP_FAIL if initializing failed

        Note
        This function should be called exactly once from application code, when the application starts up.
    */

   /*
    Next we will create event looops
    The default event loop is a special type of loop used for system events (WiFi events, for example).
    The handle for this loop is hidden from the user. The creation, deletion, 
    handler registration/unregistration and posting of events is done through a variant of the 
    APIs for user event loops. The table below enumerates those variants, and the user event loops 
    equivalent.
    
    esp_err_t esp_event_loop_create_default(void){

    }
        Create default event loop.

    Return
        ESP_OK: Success
        ESP_ERR_NO_MEM: Cannot allocate memory for event loops list
        ESP_FAIL: Failed to create task loop
        Others: Fail
   */
    ESP_ERROR_CHECK(esp_event_loop_create_default());

   
   esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    /*
        Creates default WIFI STA. In case of any init error this API aborts.
        Return
            pointer to esp-netif instance
    */

   wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
   /*
        WiFi stack configuration parameters passed to esp_wifi_init call.
   */

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Next we will define the mode to be used. for scanning we need the station mode.
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    printf("[+] Wifi Initialization complete.\n");
    ESP_ERROR_CHECK(esp_wifi_start()); // starting wifi
    

    // Configuring scanning
    
    printf("[+] Configuring items to scan.\n");
    wifi_scan_config_t scan_config = {
        .bssid = 0,     // =0 means we are not looking for anything specific i.e we are can search for a specific ssid etc. 
        .ssid = 0,
        .channel = 0,
        .show_hidden = true // also show hidden APs

    };
    ESP_ERROR_CHECK(
        esp_wifi_scan_start(
            &scan_config, 
            true // blocking =  true means we will block execution here.
            )
        ); //starting wifi scanning
    printf("[+] Wifi Scanning started.\n");


    printf("[+] Getting the scan results..\n");

    wifi_ap_record_t ap_records[MAX_AP];

    uint16_t max_records = MAX_AP;
    esp_err_t err = esp_wifi_scan_get_ap_records(
        &max_records,
        ap_records
    );
    ESP_ERROR_CHECK(err);

    printf("[+] Total number of records found %d\n", max_records);

    printf("[+] Displaying Records \n");

    for (int i =0; i< max_records; i++){
        printf("%32s | %7d | %4d \n", (char *) ap_records[i].ssid, ap_records[i].primary, ap_records[i].rssi );
    }






    

}