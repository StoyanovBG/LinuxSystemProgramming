#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <reverse.h>

int main(){
	//store the ends of the pipe
	int fd[2];
	//error check
	if (pipe(fd)==-1){
		printf("Pipe failed\n");
		return 1;
	}
	//get input from std input
	printf("please enter message\n");
	char input[100];
	scanf("%s", input);

	int pid = fork();
	//error check
	if (pid==-1){
		printf("Error forking a process\n");
		return EXIT_FAILURE;//-1
	}
	//parent process
	else if(pid>0){
		//close reading end of pipe
		close(fd[0]);
		//encrypt the message
		reverse(input);
		//write and close writing end of the pipe
		write(fd[1], input, strlen(input)+1);
		close(fd[1]);
	}
	//child process
	else if (!pid){
		//close writing end of the pipe
		close(fd[1]);
		//read string
		read(fd[0], input, 100);
		//print encrypted message to screen
		printf("%s", input);
		//decrypt message
		reverse(input);

		//save to file
		FILE * messages_file = fopen("./messages.log","w");
		if (messages_file==NULL){
			printf("Failed to open file\n");
			return EXIT_FAILURE;//-1
		}
		fputs(input,messages_file);
		fclose(messages_file);
	}
	return EXIT_SUCCESS;//0
}
