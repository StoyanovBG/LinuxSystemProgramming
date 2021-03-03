#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#define BUF_SIZE 1000000
#include <time.h>
char * rndword(char *buf, int min_length, int max_length){
	srand(time(0));
	//generate random number between min and max length
	int length = rand()% (max_length - min_length+1)+min_length;
	//generate num with length generated above
	int num = (rand() % (10^(length+1) - 10^length)) + 10^length;
	char * word;
	//convert the random number to a string
	sprintf(word, "%d", num);
	sprintf(buf, "%s \n", word);
	return word;
}

int main(int argc, char *argv[]) {
	//check if the correct arguments are input
	if(argc != 4){
		printf("Syntax: fmanipulation [word count] [min length] [max length]\n");
	}
	//open file
	int fd = open("./words.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	//display if any error when opening file
	if (fd==-1){
		printf("Error opening the file!\n");
	}
	//lock the first 100bytes of the file
	char str[64];
	memset(str,32,64);
	struct flock fi;
	sprintf(str, "stored by process %i", getpid());
	fi.l_type = F_WRLCK;
	fi.l_whence = SEEK_SET;
	fi.l_start = 0;
	fi.l_len=100;
	int off =0;
	while(fcntl(fd, F_SETLK, &fi)==-1){
		fcntl(fd, F_GETLK, &fi);
		printf("bytes %i to %i blocked ny process %i\n", off, off+100, fi.l_pid);
		fi.l_start=off;
	}
	lseek(fd,off,SEEK_SET);
	write(fd,str,strlen(str));
	getchar();
	fi.l_type=F_UNLCK;
	//display if any error when blocking
	if (fcntl(fd,F_SETLK,&fi)==-1)printf("Error while blocking\n");


	//input the random words
	int words_count = atoi(argv[1]);
	int min_length = atoi(argv[2]);
	int max_length = atoi(argv[3]);
	char buf[BUF_SIZE];
	for (int i=0; i<words_count; i++){
		char* word = rndword(buf, min_length,max_length);
		sprintf(buf,"%s",word);
		int text_len = strlen(word);
		ssize_t nr = write(fd, buf, text_len);
		//display if any error when writing to file
		if (nr == -1){
			printf("Error writing to file\n");
			break;
		}
	}
	//print the contents on words.txt to the screen
	ssize_t len;
	char buff[BUF_SIZE];
	while((len = read(fd, buff, BUF_SIZE-1))!=0){
		if (len==-1){
			if (errno == EINTR) continue;
			printf("Error reading file\n");
			break;
		}
		printf("%s",buff);
	}
	//display if any error when closing the file
	if (close(fd)==-1){
		printf("Error closing the file\n");
		return -2;
	}
	printf("Success\n");
	return 0;
 }
