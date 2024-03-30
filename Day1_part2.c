#include <stdio.h>
#include <string.h>
char numbers[9][6] = {{"one"}, {"two"}, {"three"}, {"four"}, {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};
void clear_buffer(char string[]){
    for (string; *string; string++){
        *string = '\0';
    }
}

int number_check_left(char string[]){
    char* ptr_array[9] = {0};
    int tracker = 0;
    for (int i = 0; i < 9; i++){
        char* pointer = strstr(string, numbers[i]);
        if (pointer){
            ptr_array[tracker] = pointer;
            tracker++;
        }
    }
    if (ptr_array[1] != 0){
        for (int i = 1; i < sizeof(ptr_array)/sizeof(ptr_array[0]); i++){
            if (ptr_array[0] > ptr_array[i] && ptr_array[i] != 0){
                ptr_array[0] = ptr_array[i];
            }
        }
    }
    if (ptr_array[0] != 0){
        for (int i = 0; i < 9; i++){
            if (strncmp(ptr_array[0], numbers[i], strlen(numbers[i])) == 0){
                return i+1;
            }
        }
    }
    return 0;
}

int number_check_right(char string[]){
    char* ptr_array[9] = {0};
    int tracker = 0;
    for (int i = 0; i < 9; i++){
        char* pointer = strstr(string, numbers[i]);
        if (pointer){
            ptr_array[tracker] = pointer;
            tracker++;
        }
    }
    if (ptr_array[1] != 0){
        for (int i = 1; i < sizeof(ptr_array)/sizeof(ptr_array[0]); i++){
            if (ptr_array[0] < ptr_array[i] && ptr_array[i] != 0){
                ptr_array[0] = ptr_array[i];
            }
        }
    }
    if (ptr_array[0] != 0){
        for (int i = 0; i < 9; i++){
            if (strncmp(ptr_array[0], numbers[i], strlen(numbers[i])) == 0){
                return i+1;
                //strncpy(str_number, ptr_array[0], strlen(numbers[i]));
            }
        }
    }
    return 0;
}

int main(){
    FILE *file;
    file = fopen("Day1_input.txt", "r");
    if (!file){
        perror("Error. File not found");
    }
    char line[100];
    int index = 0;
    char left_most[80];
    left_most[0] = '\0';
    char right_most[80];
    right_most[0] = '\0';
    int number_array[2] = {0};
    int sum = 0;
    int number1 = 0;
    int number2 = 0;
    while (fgets(line, 100, file) != NULL){
        for (char* string_ptr = line; *string_ptr; string_ptr++){
            /*if (line[0] >= '0' && line[0] <= '9'){
                left_most[0] = '-';
            }*/
            if (left_most[0] == '\0' && (*string_ptr >= '0' && *string_ptr <= '9')){
                strncpy(left_most, line, index);
                //printf("left_most: %s\n", left_most);
            }
          //  if (left_most[0] != '\0' && (*string_ptr))

            if (left_most[0] == '\0'){
                index++;
            }
        }
        if (left_most[0] != '\0' && strlen(left_most) > 2){
            number1 = number_check_left(left_most);
            number_array[0] = number1;
            
        }
        /*if (right_most[0] != '\0' && strlen(right_most) > 2){
            number2 = number_check_right(right_most);
            number_array[1] = number2;
        }*/

        for (char* character = line; *character; character++){      
            if (*character >= '0' && *character <= '9' && number_array[0] == 0 && number1 == 0){
                number_array[0] = *character - 48; //conversion of ASCII value to int value
            }
            else if (*character >= '0' && *character <= '9' && number_array[0] != 0 && number2 == 0){
                number_array[1] = *character - 48;
            }
            
            if (*character == '\n'){
                if (number_array[1] == 0){
                    number_array[1] = number_array[0];
                }
                //printf("number 1: %d number2: %d number_array[0]: %d number_array[1]: %d\n", number1, number2, number_array[0], number_array[1]);
                sum += number_array[0] * 10 + number_array[1];
                number_array[0] = 0;
                number_array[1] = 0;
            }
        }
        clear_buffer(left_most);
        clear_buffer(right_most);
        index = 0;
    }
    fclose(file);
    printf("%d\n", sum);
    return 0;
}
