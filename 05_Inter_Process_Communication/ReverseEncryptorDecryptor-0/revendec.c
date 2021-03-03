#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include "reverse/src/reverselib/reverse.h"


int main()
{
	int pp[2];
	char str[100];
	printf("\n Enter string: ");
	scanf("%s", str);
	
	int pid = fork();
	if(!pid)
	{
		close(pp[1]);
		read(pp[0], str, 100);
		reverse(str);
		printf("\n Reversed: %s", str);
		printf("\n");

		FILE * mfile = fopen("./messages.log", "w");
		
		if(mfile == NULL)
		{
			printf("\n Error in opening the file!");
			return EXIT_FAILURE;
		}
		
		fputs(str, mfile);
		fclose(mfile);
	}
	else if(pid > 0)
	{
		close(pp[0]);
		reverse(str);
		write(pp[1], str, strlen(str) + 1);
		close(pp[1]);
	}
	else if(pid == 1)
	{
		printf("\n Forking error!");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
