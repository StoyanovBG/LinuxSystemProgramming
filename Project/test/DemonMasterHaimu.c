#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h> //open
#include <unistd.h> //close
#include <pthread.h>
 

char client_message[2000];
char buff[1024];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *socketThread(void*arg)
{
 int newSocket = *((int *)arg);
 recv(newSocket , client_message , 2000 , 0);

 //Send msg to  student socket
 pthread_mutex_lock(&amp;lock);
 char*message = malloc(sizeof(client_message) + 20);
 strcpy(message,"Hello Student : ");
 strcat(message,client_message);
 strcat(message,"\n");
 strcat(buff,message);
 free(message);
 pthread_mutex_unlock(&amp;lock);
 sleep(1);
 send(newSocket,buff,13,0);
 printf("Exit socketThread \n");
 close(newSocket);
 pthread_exit(NULL);
}

int main()
{
int serverSocket,newSocket;
struct sockaddr_in serverAddr;
struct sockaddr_storage serverStorage;
socklen_t addr_size;
//create socket
serverSocket = socket(PF_INET , SOCK_STREAM , 0);
//addrfamily=internet
serverAddr.sin_family = AF_INET;
//port
serverAddr.sin_port = htons(7799);
//localhost 
serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//all bits to 0
memset(serverAddr.sin_zero, '\0' , sizeof(serverAddr.sin_zero));
//bind
bind(serverSocket, (struct sockaddr *)&amp;serverAddr, sizeof(serverAddr));

if(listen(serverSocket , 50)==0)
{
printf("Listening");
}
else
 printf("Error");
 pthread_t tid [60];
 int i =0;
 while(1)
 {
  //new socket for another student
 addr_size = sizeof serverStorage;
 newSocket = accept (serverSocket, (struct sockaddr *)&amp;serverStorage,&amp;addr_size);
 //new request to the tread
 if(pthread_create(&amp;tid[i++], NULL , socketTread , &amp;newSocket) != 0 )
 {
 printf("Failed to create tread");
 }
 if( i &gt; = 50)
 {
  i =0;
  while(i &lt;50)
 {
 pthread_join(tid [i++],NULL);
 }
 i =0;
 }
}
 return 0;
}
