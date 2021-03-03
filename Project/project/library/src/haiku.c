#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/time.h>
#include <netdb.h>
#define BUF_SIZE  1000000
long getMicrotime(){
        struct timeval currentTime;
        gettimeofday(&currentTime, NULL);
        return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
int getSentence(char *buf) {
    sprintf(buf, "%ld> This is my first sentence.\n", getMicrotime());
    return strlen(buf);


    sprintf(buf, "%ld> This is my second sentence in here.\n", getMicrotime());
    return strlen(buf);
 sprintf(buf, "%ld> Here is the final sentence.\n", getMicrotime());
    return strlen(buf);
}
int main(int argc, char *argv[])
{
    int fd;
    fd = open("./dictionary", O_WRONLY);
  if (fd == -1)
    {
        printf("ERROR opening the file!\n");
        return -1;
    }
    char buf[BUF_SIZE];
    for (int i=0; i < 100; i++)
    {
        int text_len = getSentence(buf);
        ssize_t nr = write(fd, buf, text_len);
        if (nr == -1)
        {
 printf("ERROR writing to the file!\n");
            break;
        }
    }
    if (close(fd) == -1)
    {
        printf("ERROR closing the file!\n");
        return -2;
 }
    printf("SUCCESS!\n");
    return 0;

}
