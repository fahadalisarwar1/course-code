#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_system.h"
#include "string.h"

/*
    In this example we will send data from pin number 4 to pin number 5

*/

#define TXD_PIN 4 // sending pin
 
#define RXD_PIN 5 // Receiving PIN

// next we will define a buffer amount we want to read.
#define BUFFER_SIZE 1024  // we will read 1 kb of memory at a time

void app_main(void)
{


    // the first thing we need to do in order to enable serial communication is to enable the serial port,
    // 
    uart_config_t uart_configuration = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .stop_bits = UART_STOP_BITS_1,
        .parity = UART_PARITY_DISABLE,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    }; // now the structure is setup, these settings will be used for serial communication.


    /*
    There are 3 UARTS available on ESP32 board. UART0 is not recommended to user so we will user UART_NUM_1

    */
    uart_param_config(
        UART_NUM_1, // select the second UART module
        &uart_configuration  // the configuration define above.
    );

    /*
    Next we need to define which pins will be used for serial communication
    */

   uart_set_pin(
       UART_NUM_1, // UART numberr to be used
       TXD_PIN, // pin for sending data
       RXD_PIN, // pin for receiving data
       UART_PIN_NO_CHANGE,
       UART_PIN_NO_CHANGE // since we are not using CTS/RTS signalling, these pins will be unchanged. 
   );

    // Next we need to install the UART driver.
    uart_driver_install(
        UART_NUM_1,
        BUFFER_SIZE,    // Receive buffer size
        0,          // TX buffer size
        0,
        NULL,   // queue handler to NULL
        0 // since we are not using intterupts
    );


    // now our initialization is complete the next step is to send a message. 
    char message[] = "ping";

    while (1){
    printf("message being sent: %s\n", message);


    // to send the message

    uart_write_bytes(
        UART_NUM_1, // uart to be used
        message,   // the message to be sent 
        sizeof(message)  // message bytes size
    );

    // the sending part is complete now.
    // now we havfe to receive this message on the RX pin


    char received_data[BUFFER_SIZE];
    // next, clean the buffer
    memset(received_data, 0, sizeof(received_data));

    uart_read_bytes(UART_NUM_1, (uint8_t *) received_data, BUFFER_SIZE, pdMS_TO_TICKS(500));
    printf("received data %s\n", received_data);

    vTaskDelay(2000/portTICK_PERIOD_MS);

}



}
