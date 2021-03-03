#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define BUF_SIZE 1000000

int pids (char* buf, int pid){
	sprintf(buf,"%i", pid);
	return strlen(buf);
}

int main(int argc, char*argv[])
{
	if (argc!=2)
	{
		printf("Syntax: tempgen [files_count]\n");
		return EXIT_FAILURE; 
	}

	int files_count = atoi(argv[1]);
	for (int i=0;i<files_count;i++)
	{
		int pid = fork();
		if (pid==-1)
		{
			printf("Error\n");
			return EXIT_FAILURE;
		}
		else if(pid>0)
		{
			if (i<=9)
			{
				printf("file temp%i%i.tmp created\n", 0,i);
			}
			else
			{
				printf("file temp%i.tmp created\n", i);
			}
		}
		else if (!pid)
		{
		char buffer[files_count];
			if (i<=9)
			{
				sprintf(buffer, "./temp%i%i.tmp",0,i);
			}
			else
			{
				sprintf(buffer, "./temp%i.tmp",i);
			}
			int fd = open(buffer, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd==-1)
			{
				printf("Error opening file\n");
				return EXIT_FAILURE;
			}
			char buf[BUF_SIZE];
			for (int i=0;i<1000;i++)
			{
				int buf_len = pids(buf,pid);
				ssize_t nr = write(fd, buf, buf_len);
				
				if (nr == -1)
				{
					printf("Error writing to the file\n");
					return -2;
				}
			}
			if (close(fd)== -1)\
			{
				printf("Error closing the file\n");
			}
		}
	}
	return EXIT_SUCCESS; 
}
