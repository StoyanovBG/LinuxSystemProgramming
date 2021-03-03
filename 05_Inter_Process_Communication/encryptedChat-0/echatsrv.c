#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define FIFO_NAME "./encrypted"

int main()
{
	char pos, str[100];
	mkfifo(FIFO_NAME, 0600);
	FILE * f = fopen(FIFO_NAME, "w");

	if (f == NULL)
	{
		printf("\n Error in file!");
		return EXIT_FAILURE;
	}
	printf("\n Enter string: ");
	fgets(str, 100, stdin);
	fputs(str,f);
	fclose(f);

	return EXIT_SUCCESS; 
}
