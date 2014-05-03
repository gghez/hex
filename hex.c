#include <stdio.h>
#include <string.h>
#include <math.h>

void syntax()
{
	fprintf(stderr, "Syntax error.\n");
	fprintf(stderr, "\thex [-sn] <decimal_or_string>\n\n");
	fprintf(stderr, "\tDefault parsing is string based.\n");
}

#define MODE_NUMBER 1
#define MODE_STRING 2

int hex(int mode, char* base)
{
	if (mode == MODE_NUMBER)
	{
		int num = atoi(base);
		printf("%02X %02X %02X %02X\n", (0xFF000000 & num) >> 24, (0xFF0000 & num) >> 16, (0xFF00 & num) >> 8, (0xFF & num));
	}
	else if (mode == MODE_STRING)
	{
		int i;
		for (i=0;i<strlen(base);i++)
		{
			printf("%02X ", base[i]);
		}
		printf("\n");
	}
	else
	{
		syntax();
		return 3;
	}
}

int main(int argc, char** argv)
{
	if (argc == 2)
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
