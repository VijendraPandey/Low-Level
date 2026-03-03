#include<stdio.h>
#include "entity1.h"

void (*mul_ptr)(int a, int b) = NULL;

static int a;
static int b;

void data_gen(void){
    a = 10;
    b = 20;
}

void multiply_wrapper(int a, int b){
    if(mul_ptr){
        mul_ptr(a, b);
    }else{
        printf("No function registered with mul_ptr function pointer");
    }
}

void compute(void){
    data_gen();
    multiply_wrapper(a, b);
}