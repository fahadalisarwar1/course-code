
#include <stdio.h>
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_err.h"
#include "esp_event.h"



void app_main(void)
{
    // Initialize the underlying TCP/IP stack.
    printf("[+] Initialize the underlying TCP/IP stack \n");
    ESP_ERROR_CHECK(esp_netif_init());
    /*
        esp_err_tesp_netif_init(void)
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
   */


    

   
   
}