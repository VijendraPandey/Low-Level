#include<stdio.h>
#include "entity1.h"
#include "entity2.h"

void multiply(int a, int b){
    int c = a*b;
    printf("The result is: %d", c);
}

void callback_registration(void){
    mul_ptr = multiply;
}