
#include <stdio.h>
#include <string.h>


void add_exclaimation(char * message){
    strcat(message, "!");

}
    
void app_main(void)
{

    /*
    In this example we will learn more about C programming pointers


    */


   char message[20] = {"Hello world"};

   // we will add exclamation point to the array
    add_exclaimation(message);

    printf("after exclamation: %s\n", message);


   
}