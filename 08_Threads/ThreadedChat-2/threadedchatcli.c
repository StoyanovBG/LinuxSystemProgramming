#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

//receive messages, read and print to screen
void * doRecieving(void * sockID){
	int clientSocket = *((int *) sockID);

	while(1){
		char buf[BUF_SIZE];
		int read = recv(clientSocket,buf,BUF_SIZE,0);
		buf[read] = '\0';
		printf("%s\n",buf);
	}
}

//main program
int main(int argc, char ** argv){
	//arguments check
	if (argc<2){
		printf("please enter %s <port>\n",argv[0]);
		return EXIT_FAILURE;//-1
	}

	//socket descriptor
	int port = atoi(argv[1]);
	int clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	//server address
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//error check for connect
	if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) {
		printf("error connecting\n");
		return EXIT_FAILURE;//-1
	}

	//if connect has worked
	printf("Connection established\n");

	//initialize thread that uses doReceiving
	pthread_t thread;
	pthread_create(&thread, NULL, doRecieving, (void *) &clientSocket );

	//infinite loop
	while(1){
		char buf[BUF_SIZE];
		//read input from std input
		scanf("%s",buf);
		if(strcmp(buf,"LIST") == 0){
			send(clientSocket,buf, BUF_SIZE,0);
		}
		//if client sends SEND, send message through socket
		if(strcmp(buf,"SEND") == 0){
			send(clientSocket,buf,BUF_SIZE,0);
			scanf("%s",buf);
			send(clientSocket,buf,BUF_SIZE,0);
			scanf("%[^\n]s",buf);
			send(clientSocket,buf,BUF_SIZE,0);
		}
		//if the client sends !quitserver, break and exit loop
		if (strcmp(buf,"!quitserver")==0){
			printf("server has quit\n");
			break;
		}
	}
	return EXIT_SUCCESS;//0
}
