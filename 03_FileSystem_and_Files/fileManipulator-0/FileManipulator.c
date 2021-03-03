#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
//Sentance
int getSentence(char *buf) {
    sprintf(buf, "war \n");
    return strlen(buf);
}
//Main
int main(int argc, char *argv[])
{
	int words_count = atoi(argv[1]);
	int min_length = atoi(argv[2]);
	int max_length = atoi(argv[3]);

	if(argc != 4)
  {
    printf("Syntax error, please enter 3 arguments");
    return -1;
  }
      //File Descriptor
    int fd = open("./words.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        //Error open
    if (fd == -1)
    {
        printf("ERROR opening the file!\n");
        return -1;
    }
        // Write in file
    char buf[words_count];
    for (int i=0; i < words_count; i++)
    {
        int buf_len = getSentence(buf);
        ssize_t nr = write(fd, buf, buf_len);
        //Error in write
        if (nr == -1)
        {
            printf("ERROR writing to the file!\n");
            break;
        }
    }
        //Error in close
    if (close(fd) == -1)
    {
        printf("ERROR closing the file!\n");
        return -2;
    }
    return 0;

}

