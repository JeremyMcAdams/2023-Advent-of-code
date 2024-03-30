#include <stdio.h>
#include <string.h>
char numbers[9][6] = {{"one"}, {"two"}, {"three"}, {"four"}, {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

void clear_buffer(char string[]){
    for (char* ptr = string; *ptr; ++ptr){
        *ptr = '\0';
    }
}

int left_number_check(char string[]){
    char* pointer_array[9] = {0};
    int tracker = 0;
    for (int i = 0; i < 9; ++i){
        char* pointer = strstr(string, numbers[i]);
        if (pointer){
            pointer_array[tracker] = pointer;
            tracker++;
        }
    }
    if (pointer_array[1] != 0){
        for (int i = 0; i < 9; ++i){
            if (pointer_array[0] > pointer_array[i] && pointer_array[i] != 0){
                pointer_array[0] = pointer_array[i];
            }
        }
    }
    if (pointer_array[0] != 0){
        for (int i = 0; i < 9; ++i){
            if (strncmp(pointer_array[0], numbers[i], strlen(numbers[i])) == 0){
                return i+1;
            }
        }
    }
    return 0;
}

int right_number_check(char string[]){
    char* pointer_array[9] = {0};
    int tracker = 0;
    char* pointer_check = string;
    for (pointer_check = string + strlen(string) - 1; *pointer_check; pointer_check--){
        for (int i = 0; i < 9; ++i){
            char* pointer = strstr(pointer_check, numbers[i]);
            if (pointer){
                pointer_array[tracker] = pointer;
                break;
            }
        }
        if (pointer_array[0] != 0){
            break;
        }
    }
    if (pointer_array[1] != 0){
        for (int i = 0; i < 9; ++i){
            if (pointer_array[0] < pointer_array[i]){
                pointer_array[0] = pointer_array[i];
            }
        }
    }
    
    if (pointer_array[0] != 0){
        for (int i = 0; i < 9; ++i){
            if (strncmp(pointer_array[0], numbers[i], strlen(numbers[i])) == 0){
                return i+1;
            }
        }
    }
    return 0;
}

int main(){
    char line[100];
    char left_most[80];
    char right_most[80];
    int count = 0;
    int number1 = 0;
    int number2 = 0;
    int coordinates[2] = {0};
    int sum = 0;
    FILE *file;
    int line_count = 1;
    left_most[0] = '\0';
    right_most[0] = '\0';
    file = fopen("Day1_input.txt", "r");
    
    if (!file){
        perror("Error File not Found\n");
        return 1;
    }
    
    while (fgets(line, 100, file) != NULL){
        for (char* str_ptr = line; *str_ptr; ++str_ptr){
            if (left_most[0] == '\0' && (*str_ptr >= '0' && *str_ptr <= '9')){
                strncpy(left_most, line, count);
                count = 0;
                break;
            }
            count++;
        }    
       for (char* str_ptr = line; *str_ptr; ++str_ptr){
            if (*str_ptr >= '0' && *str_ptr <= '9'){
                strncpy(right_most, (str_ptr+1), 80);
            }
        }
        number1 = left_number_check(left_most);
        number2 = right_number_check(right_most); 
        coordinates[0] = number1;
        coordinates[1] = number2;
        
        for (char* character = line; *character; character++){      
            if (*character >= '0' && *character <= '9' && coordinates[0] == 0 && number1 == 0){
                coordinates[0] = *character - 48; //conversion of ASCII value to int value
            }
            else if (*character >= '0' && *character <= '9' && coordinates[0] != 0 && number2 == 0){
                coordinates[1] = *character - 48;
            }
            
            if (*character == '\n'){
                if (coordinates[1] == 0){
                    coordinates[1] = coordinates[0];
                }
                printf("Line %d,  number 1: %d number2: %d coordinates[0]: %d coordinates[1]: %d\n", line_count, number1, number2, coordinates[0], coordinates[1]);
                sum += ((coordinates[0] * 10) + coordinates[1]);
                coordinates[0] = 0;
                coordinates[1] = 0;
            }
        }
        clear_buffer(left_most);
        line_count++;
    }
    fclose(file);
    printf("sum: %d\n", sum);
    return 0;
}
