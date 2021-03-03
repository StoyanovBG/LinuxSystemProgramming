#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <reverse.h>

#define FIFO_NAME "./encrypted-chat"

int main(){
	char ch;
	mkfifo(FIFO_NAME, 0600);
	FILE * f = fopen(FIFO_NAME, "w");

	//error check
	if (f==NULL){
		printf("Failed to open FIFO\n");
		return EXIT_FAILURE; //-1
	}

	printf("Please enter string of maximum 100 characters\n");
	//read string from input
	char str[100];
	fgets(str, 100, stdin);
	//reverse the string using the reverse library
	reverse(str);
	//add the string to the file
	fputs(str,f);

	//close file and save
	fclose(f);
	//delete file
	unlink(FIFO_NAME);

	return EXIT_SUCCESS; //0
}
