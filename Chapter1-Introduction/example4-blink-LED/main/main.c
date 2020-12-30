
#include <stdio.h>
#include "driver/gpio.h" // this will help us to access the GPIO.
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*
    In this example we are going to blink an led,
    you can either select the internal LED or attach an external one. 
     
*/
#define LED_PIN 2
void app_main(void)
{
    // GPIO can be either ADC, DAC, touch, etc. Here we enable the GPIO mode. 
    gpio_pad_select_gpio(LED_PIN); // This sets the pin as GPIO, note that pins are multiplexed and they have different modees. 


    // Next we will set the direction of GPIO, GPIO can be either input or output, 
    // We want the LED to blink so it will be output in our case.
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);   

    
    int state = 1; // ON state
    while (1)
    {

        gpio_set_level(LED_PIN, state); // simply passing the state level to LED_PIN
        printf("LED is %d\n", state);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        
        // Now we simply toggle the pin after a delay
        state = !state; // Toggle the LED
        /* code */
    }
    
    
}