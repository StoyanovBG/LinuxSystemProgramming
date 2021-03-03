#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

//Sharef file for wtiting names of "pid files"
#define IN_BOX /dev/shm/inbox.txt
//Shared directory for writing student's file mask hav to be 666
#define STUDENTS_DIR /haiku/students-files    
// Buffer up to 256
#define BUF_SIZE 256
//Helper methods
long int findSize(char file_name[]) //Calculate size of given file
{
    // opening the file in read mode 
    FILE* fp = fopen(file_name, "r");

    // checking if the file exist or not 
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file 
    long int res = ftell(fp);

    // closing the file 
    fclose(fp);

    return res;
}


// Main Program
int main(int argc, char ** argv)
{
  // Buffer up to 256
  char buf[BUF_SIZE];

  // Arguments check
  if (argc < 3)
  {
    fprintf(stderr,"usage: %s <hostname> <port_number>\n", argv[0]);
    return EXIT_FAILURE; // -1
  }

  //Create  file named by PID for each client.
  int pid = getpid();
  char filePath[] = STUDENTS_DIR;
  strcat(filePath,itoa(pid, buf, 10);
  FILE* fptr;
  fptr = fopen(filePath, "w");

  //Write name of file to /dev/shm/inbox.txt
  FILE* f;
  f = fopen(IN_BOX, "w");
  while (1)
  {
      long int res = findSize(file_name);
      if (res < 1 && res != -1)
      {
          fprintf(f, "%s\n", filePath);
          break;
      }
  }


  //Insert Date&Time at first row in file.
  time_t t = time(NULL);
  struct tm* tm = localtime(&t);
  fprintf(fptr, "%s\n", asctime(tm));

  // Socket Descriptor
  int port = atoi(argv[2]); // Не съм наясно как да конектна повече от един порт!
  int sock_client = socket(AF_INET, SOCK_STREAM, 0); // Network Socket using TCP protocol
  if (sock_client < 0)
  {
    printf("Error Socket Initialization! Err.No: %d", errno);
    return EXIT_FAILURE; // -1
  }

  // Server Address
  struct hostent *server;
  server = gethostbyname(argv[1]);
  if (server == NULL)
  {
    printf("Error Host Not Found!\n");
    return EXIT_FAILURE; // -1
  }

  // Initialize Socket Structure
  struct sockaddr_in serv_addr;
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  strncpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
  serv_addr.sin_port = htons(port);

  // Socket Connect
  if (connect(sock_client, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  //if (connect(sock_client, &serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("Error Socket Connet! Err.No: %d", errno);
    return EXIT_FAILURE; // -1
  }

  // Read text from the standart input in the buffer and send in the socket
  
  char *result = "";
  while (1)
  {
      // Haiku first row five words
      for (int i = 0; i < 5; i++)
      {
          memset(buf, 0, BUF_SIZE);
          read(sock_client, buf, BUF_SIZE - 1);
          strcat(buf, " ");
          strcat(result, buf);
      }
      printf("%s\n", result);
      fprintf(fptr, "%s\n", result);
      // Haiku second row seven words
      for (int i = 0; i < 7; i++)
      {
          memset(buf, 0, BUF_SIZE);
          read(sock_client, buf, BUF_SIZE - 1);
          strcat(buf, " ");
          strcat(result, buf);
      }
      printf("%s\n", result);
      fprintf(fptr, "%s\n", result);
      // Haiku third row five words
      for (int i = 0; i < 5; i++)
      {
          memset(buf, 0, BUF_SIZE);
          read(sock_client, buf, BUF_SIZE - 1);
          strcat(buf, " ");
          strcat(result, buf);
      }
      printf("%s\n", result);
      printf("\n");   // Print empty row
      fprintf(fptr, "%s\n", result);

  }
  fclose(fptr);
  close(sock_client);

  return EXIT_SUCCESS; // 0
}
