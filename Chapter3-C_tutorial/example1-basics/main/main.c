
#include <stdio.h>
#include <string.h>


struct  Person
{
    // data regarding the struct should be placed here
    char firstName[20];
    char lastName[20];
    int age;      
};

typedef struct Person_struct{
    int age;
    char school[20];
    char firstName[20];
}Person;
    
void app_main(void)
{

    /*
    In this example we will learn more about C programming

    */
   struct Person p; // here we have to write the struct keyword as no alias is used for the Person

   strcpy(p.firstName, "fahad");
   strcpy(p.lastName, "ali");
   p.age=12;

   printf("%s %s is %d years old\n", p.firstName, p.lastName, p.age);
   
    Person p2;
    strcpy(p2.firstName, "fahad");
    strcpy(p2.school, "fauji");
    p2.age =12;

    printf("%s studied in  %s school for %d years\n", p2.firstName, p2.school, p2.age);


   
   
}