#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <reverse.h>
#define FIFO_NAME "./encrypted-chat"

int main(){
	char message[100];
	FILE * f = fopen(FIFO_NAME, "r");

	//get input and print it to screen
	fgets(message,60,f);
	printf("%s",message);

	//decode message
	reverse(message);

	FILE * messages_file = fopen("./messages.log", "w");

	//check for errors
	if (messages_file==NULL){
		printf("Failed to open file\n");
		return EXIT_FAILURE;//-1
	}

	//add message to  messages.log
	fputs(message,messages_file);

	//close file
	fclose(messages_file);

	return EXIT_SUCCESS;//0
}

