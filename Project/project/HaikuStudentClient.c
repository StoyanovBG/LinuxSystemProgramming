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





int  argc (char *argv[])
 {

  char buf[BUF_SIZE];
 if (argc < 0)
  {
    fprintf(stderr,"usage: %s <hostname> <port_number>\n", argv[0]);
    return EXIT_FAILURE; // -1
  }
  int port = atoi(argv[2]);
  int sock_client = socket(AF_INET, SOCK_STREAM, 0); 
  if (sock_client < 0)
  {
    printf("Error Socket Initialization! Err.No: %d", errno);
    return EXIT_FAILURE; // -1
  }
  struct hostent *server;
  server = gethostbyname(argv[1]);
  if (server == NULL)
  {
    printf("Error Host Not Found!\n");
    return EXIT_FAILURE; // -1
  }
  struct sockaddr_in serv_addr;
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  strncpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
  serv_addr.sin_port = htons(port);
  if (connect(sock_client, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("Error Socket Connet! Err.No: %d", errno);
    return EXIT_FAILURE; // -1
  }
  printf("Write the message and press [Enter] to send:\n");
  memset(buf, 0, BUF_SIZE);
  fgets(buf, BUF_SIZE-1, stdin);
  write(sock_client, buf, strlen(buf));
  memset(buf, 0, BUF_SIZE);
  read(sock_client, buf, BUF_SIZE-1);
  printf("Received: %s\n",buf);
  close(sock_client);
  return EXIT_SUCCESS; // 0
}
