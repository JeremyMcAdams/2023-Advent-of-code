#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINES 3

int main(){
    FILE *file;
    file = fopen ("Day1_input.txt", "r");
    if (!file){
        perror("File not found\n"); 
        return 0;
    }
    char coordinates[LINES];
    int number_array[2] = {0};
    int character;
    int counter = 0;
    int sum = 0;
    while ((character = fgetc(file)) != EOF){
        if (character >= '0' && character <= '9' && number_array[0] == 0){
            number_array[counter] = character - 48; //conversion of ASCII value to int value
            counter += 1;
        }
        else if (character >= '0' && character <= '9' && number_array[0] != 0){
            number_array[counter] = character - 48;
        }
        
        if (character == '\n'){
            if (number_array[1] == 0){
                number_array[1] = number_array[0];
            }
            sum += number_array[0] * 10 + number_array[1];
            counter = 0;
            number_array[0] = 0;
            number_array[1] = 0;
        }
    }
    if (ferror(file)){
        puts("I/O error when reading");
    }
    else if (feof(file)){
        puts("End of file reached successfully");
    }
    fclose(file);
    printf("%d\n", sum);
    return 0;
}
