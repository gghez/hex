#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define MODE_NUMBER 	1
#define MODE_STRING 	2
#define MODE_INPUT		3
#define MODE_FILE		4

void syntax();
void display_hex(char*,int,int);
int hex_file(FILE*);
int hex_string(char*);
int hex_num(char* num);
int hex_file_path(char*);
int hex_input();
int hex(int,char*);
