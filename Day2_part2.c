#include <stdio.h>
#include "strnum.h"
#include "my_string.h"
#include <string.h>

char colors[][6] = {{"red"},{"blue"},{"green"}}; 

typedef struct Bag {
	int red;
	int green;
	int blue;
} Bag;

Bag current_bag = {
	.red = 0,
	.green = 0,
	.blue = 0,
};

void clear_buffer(char string[], int len){
	for (int i = 0; i < len; i++){
		string[i] = '\0';
	}
}

//splits a string into component tokens based on input delimiters
void string_tok(char* string, char* delimiters, int fragments, int buffer_size, char buffer_storage[fragments][buffer_size]){
	char* tokens = string;
	int fragment = 0;
	for (fragment; fragment < fragments; fragment++){
		
		tokens = strtok(fragment == 0 ? tokens : NULL, delimiters);
		if (tokens){
			//strip_string removes all character given in the second arguments
			strip_string(tokens, " \n");
			strncpy(buffer_storage[fragment], tokens, buffer_size);
		}
	}
}

void check_max(char* string){
	char* pointer;
	char current_number[4] = {"\0\0\0\0"};
	int converted_number;
	int fragments = 3, buffer_size = 50;
	char color[fragments][buffer_size];
	//itiailiazing all the elements in the string matrix to null
	for (int i = 0; i < fragments; i++){
		clear_buffer(color[i], buffer_size);
	}
	
	string_tok(string, ",", fragments, buffer_size, color);
	
	for (int i = 0; i < fragments; i++){
		if (color[i][0] == '\0'){
			break;
		}
		int counter = 0;
		
		while (color[i][counter] >= '0' && color[i][counter] <= '9'){
			counter++;
		}
		strncpy(current_number, color[i], counter);
		//converts current_number characters to an integer
		converted_number = string_to_int(current_number);
	
		clear_buffer(current_number, sizeof(current_number));
		
		for (int j = 0; j < fragments; j++){
	
			pointer = new_strstr(color[i], colors[j]);
			if (pointer){
				break;
			}
		}
		if (new_strcmp(pointer, "red") == 0 && converted_number > current_bag.red ){
			current_bag.red = converted_number;
		}
		else if (new_strcmp(pointer, "green") == 0 && converted_number > current_bag.green){
			current_bag.green = converted_number;
		}
		else if (new_strcmp(pointer, "blue") == 0 && converted_number > current_bag.blue){
			current_bag.blue = converted_number;
		}
	}
}


void iterate_games(int fragments, int buffer_size, char tokens[fragments][buffer_size]){
	//iterates through all the tokens, skips the Game# token since it has no value in this situation
	for (int i = 1; i < fragments; i++){
		check_max(tokens[i]);
	}
}


int main(){
	char line[200] = ("\0");
	int fragments = 10, buffer_size = 100;
	char tokens[fragments][buffer_size];
	int sum = 0;
	//initialize all members of the string matrix to null bytes
	for (int i = 0; i < fragments; i++){
		clear_buffer(tokens[i], buffer_size);
	}
	
	FILE *file = fopen("Day2_input.txt", "r");
	while (fgets(line, sizeof(line), file) != NULL){
	
		string_tok(line, ":;", fragments, buffer_size, tokens);
		
		for (int i = 0; i < fragments; i++){
			if (tokens[i][0] == '\0'){
				break;
			}
			iterate_games(fragments, buffer_size, tokens);
			clear_buffer(tokens[i], buffer_size);
		}
		
		sum += current_bag.red * current_bag.green * current_bag.blue;

		current_bag.red = 0;
		current_bag.green = 0;
		current_bag.blue = 0;
	}
	fclose(file);
	printf("sum = %d\n", sum);
	return 0;
}


