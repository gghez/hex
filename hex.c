#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void syntax()
{
	fprintf(stderr, "Syntax:\n");
	fprintf(stderr, "\thex [-snf] [<string>|<number>|<file>]\n\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "\t-s <string>  String based parsing.\n");
	fprintf(stderr, "\t-n <number>  Numeric based parsing.\n");
	fprintf(stderr, "\t-f <file>    File based parsing.\n\n");
	fprintf(stderr, "\tDefault parsing is string based on first parameter or standard input.\n");
}

#define MODE_NUMBER 	1
#define MODE_STRING 	2
#define MODE_INPUT		3
#define MODE_FILE		4

void display_hex(char* addr, int n, int offset)
{
	int i;
	for (i=0;i<n;i++)
	{
		if (i % 16 == 0)
		{
			printf("%08X  ", offset + i);
		}

		printf("%02X ", addr[i]);

		if ((i+1) % 16 == 0)
		{
			printf("\n");
		}
		else if ((i+1) % 8 == 0)
		{
			printf(" ");
		}
	}
	printf("\n");
}

int hex_num(char* base)
{
	int num = atoi(base);
	display_hex((char*)&num, 4, 0);
	return 0;
}

int hex_string(char* base)
{
	display_hex(base, strlen(base), 0);
	return 0;
}

int hex_file(FILE* fp)
{
	size_t n;
	char buf[4096];
	int offset = 0;
	while ((n = fread(buf, sizeof(char), 4096, fp)) > 0)
	{
		display_hex(buf, n, offset);
		offset += n;
	}
	return 0;
}

int hex_input()
{
	return hex_file(stdin);
}

int hex_file_path(char* file_path)
{
	FILE* fp = fopen(file_path, "rb");
	int ret = hex_file(fp);
	fclose(fp);
	return ret;
}

int hex(int mode, char* base)
{
	if (mode == MODE_NUMBER)
	{
		return hex_num(base);
	}
	else if (mode == MODE_STRING)
	{
		return hex_string(base);
	}
	else if (mode == MODE_INPUT)
	{
		return hex_input();
	}
	else if (mode == MODE_FILE)
	{
		return hex_file_path(base);
	}
	else
	{
		syntax();
		return 3;
	}
}

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		return hex(MODE_INPUT, NULL);
	}
	else if (argc == 2)
	{
		return hex(MODE_STRING, argv[1]);
	}
	else if (argc == 3)
	{
		if (strcmp("-n", argv[1]) == 0)
		{
			return hex(MODE_NUMBER, argv[2]);
		}
		else if (strcmp("-s", argv[1]) == 0)
		{
			return hex(MODE_STRING, argv[2]);
		}
		else if (strcmp("-f", argv[1]) == 0)
		{
			return hex(MODE_FILE, argv[2]);
		}
		else
		{
			syntax();
			return 2;
		}
	}
	else
	{
		syntax();
		return 1;
	}
}
