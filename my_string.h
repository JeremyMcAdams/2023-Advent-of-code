#ifndef MY_STRING_H
#define MY_STRING_H
void new_strncpy(register char* destination, register char* source, register int buffer_length);
int new_strlen(char* string);
void safe_gets(char* destination, int buffer_size);
char* new_strstr(char* string, char* substring);
int new_strcmp(register const char* string, register const char* comp_string);
int new_strncmp(register const char* string, register const char* comp_string, register const int len);
void strip_string(char* string, char* delimiters);
#endif
