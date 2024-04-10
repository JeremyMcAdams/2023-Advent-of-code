#include <stdio.h>
#include <string.h>
#include "my_string.h"
#include "strnum.h"
#include <stdbool.h>

char colors[3][6] = {{"red"}, {"green"}, {"blue"}}; 

typedef struct Bag{
	int red;
	int green;
	int blue;
	int game;
} Bag;

Bag max_bag = {
	.red = 12,
	.green = 13,
	.blue = 14,
};
//clears a buffer for reuse
void clear_buffer(char string[], int len){
	for (int i = 0; i < len; i++){
		string[i] = '\0'; 
	}
}

// tokenizes a given string input and then stores them into dedicated string matrix
void string_tok(char* string, char* delimiters, int fragments, int buffer_size, char buffer_storage[fragments][buffer_size]){
	char* tokens = string;
	int fragment = 0;
	for (fragment; fragment < fragments; fragment++){
		
		tokens = strtok(fragment == 0 ? tokens : NULL, delimiters);
		if (tokens){
			strip_string(tokens, " \n");
			strncpy(buffer_storage[fragment], tokens, buffer_size);
		}
	}
}

bool check_color(char* string){
	int fragments = 3, buffer_size = 50;
	char color[3][50] = {{"\0"}, {"\0"}, {"\0"}};

	string_tok(string, ",", fragments, buffer_size, color);
	char current_number[4] = "\0\0\0\0";
	int number_value;
	char* pointer;
	bool real_game;
	for (int i = 0; i < 3; i++){
		if (color[i][0] == '\0'){
			break;
		}
		int counter = 0;
		
		while (color[i][counter] >= '0' && color[i][counter] <= '9'){
			counter++;
		}
		new_strncpy(current_number, color[i], counter);
		number_value = string_to_int(current_number);
		
		clear_buffer(current_number, sizeof(current_number));
		
		for (int j = 0; j < 3; j++){
			pointer = new_strstr(color[i], colors[j]);
			if (pointer){
				break;
			}
		}
		if (new_strcmp(pointer, "blue") == 0){
			real_game = max_bag.blue >= number_value;
		}
		else if (new_strcmp(pointer, "red") == 0){
			real_game = max_bag.red >= number_value;
		}
		else if (new_strcmp(pointer, "green") == 0){
			real_game = max_bag.green >= number_value;
		}
		//immediately breaks off the game if any number of cubes exceeds the limit
		if (real_game == false){
			return false;
		}
	}
	return true;
}

//skips over the word game and converts the character numbers into an integer 
int get_value(char* string){
	string += 4;
	return string_to_int(string);
}

//determines if a game's value should be added to the sum of values
int compare_outcomes(int fragments, int buffer_size, char game[fragments][buffer_size]){
	int game_value = get_value(game[0]);
	bool valid_game = true;
	
	//1 in the for loop is the first fragment of tokens that has the cubes
	for (int i = 1; i < fragments; i++){
		if (game[i][0] == '\0'){
			break;
		}
		
		valid_game = check_color(game[i]);
		
		if (!valid_game){
			printf("Game is invalid\n");
			return 0;
		}
	}
	return game_value;
}

int main(){
	FILE *file;
	file = fopen("Day2_input.txt", "r");
	if (!file){
		perror("Error: File not found");
		return 1;
	}	
	int counter = 0;
	char line[200];
	int fragments = 10, buffer_size = 100;
	char tokens[fragments][buffer_size];
	unsigned int sum = 0;
	//initialize all strings in the string matrix with a null byte to prevent undefined behavior
	for (int i = 0; i < fragments; i++){
		tokens[i][0] = '\0';
	}
	while (fgets(line, 200, file) != NULL){

		string_tok(line, ":;", fragments, buffer_size, tokens);
		sum += compare_outcomes(fragments, buffer_size, tokens);
	
		counter++;
		clear_buffer(line, sizeof(line));
		//clears all strings that were used in the last game to prevent carry over into the new game if previous game had more entries
		for (int i = 0; i < fragments; i++){
			if (tokens[i][0] == '\0'){
				break;
			}
			clear_buffer(tokens[i], buffer_size); 
		}
		
	}
	fclose(file);
	printf("sum of values: %d\n", sum);
	return 0;
}

