#include <stdio.h>
#include <stdlib.h>
#include "strnum.h"
long int power_10(int num, int exponent){
    int base = 10;
    long long int number = 1;
    for (int i = 0; i < exponent; i++){
        number *= base;
    }
    number *= num;
    return number;
}

int chrtoint(char string[]){
    int str_len;
    char* ptr;
    for(ptr = string; *ptr; ++ptr);
    str_len = ptr - string;
    int sign = 0;
    int iter = 0;
    int buffer_size = 1;
    int *num_array = malloc(sizeof(int));
    if (!num_array){
        free(num_array);
        printf("Errno -1: Memory allocation failed");
        return -1;
    }
    for (int i = 0; i < str_len; i++){
        if (string[i] == '\0'){
            break;
        }
        
        if (i == buffer_size){
            buffer_size += 1;
            num_array = realloc(num_array, buffer_size * sizeof(int));
            if (!num_array){
                free(num_array);
                printf("Errno -1: Memory reallocation failure\n");
                return -1;
            }
        }
        if (string[i] == '-'){
            sign = 1;
        }
        else if (string[i] >='0' && string[i] <= '9'){
            num_array[i] = string[i] - 48;
        }
        else {
            num_array[i] = -1;
        }
        
        if (num_array[i] == -1){
            printf("Errno -2: Non-number dectected\n");
            free(num_array);
            return -2;
        }
    }
    //num_storage[buffer_size];
    int number = 0;
    for (int i = buffer_size -1 ; i >= 0; i--){
        number += power_10(num_array[iter], i); 
        iter++;
    }
    if (sign){
        number *= -1;
    }
    free(num_array);
    return number;
}

int main(){
    char test[] = "-1324";
    printf("%d\n", chrtoint(test));
}
