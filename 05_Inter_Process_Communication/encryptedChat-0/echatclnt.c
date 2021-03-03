#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>

#define FIFO_NAME "./encrypted"

int main()
{
	char str[100];
	FILE * f = fopen(FIFO_NAME, "r");

	fgets(str,100,f);
	printf("\n %s",str);

	FILE * mfile = fopen("./messages.log", "w");

	if (mfile==NULL)
	{
		printf("\n Error in file!");
		return EXIT_FAILURE;
	}

	fputs(str,mfile);
	fclose(mfile);

	return EXIT_SUCCESS;
}

