#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char* argv[])
{
	FILE *ptr;

	int files_count = atoi(argv[1]);
	char name[FILENAME_MAX];
	int i = 0;

	for (i=0; i<files_count; i++)
	{

		char* str;
		pid_t pid = fork();
		if (pid > 0)
		{
			snprintf(name, sizeof(name), "temp0%d.tmp", i);
                	int u = 0;
		  ptr = fopen(name, "w");
			for (u=0; u<1000; u++)
				{
					pid_t process = getpid();
					fprintf(ptr, "Pid number %d\n", process);
 				}

			fclose(ptr);
			printf("I created a temp file.\n");
			return -1;
		}
	}
	return 0;
}
