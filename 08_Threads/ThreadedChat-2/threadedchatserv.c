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

//initialize
int clientCount = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//client structure
struct client{
	int index;
	int sockID;
	struct sockaddr_in clientAddr;
	int len;
};

struct client Client[1024];
pthread_t thread[1024];

//method that the threads use
void * doNetworking(void * ClientDetail){
	//initialize
	struct client* clientDetail = (struct client*) ClientDetail;
	int index = clientDetail -> index;
	int clientSocket = clientDetail -> sockID;

	//print message to indicate which client has connected to the server
	printf("Client %d connected.\n",index + 1);

	//inifinite loop
	while(1){
		//read message from the socket
		char buf[1024];
		int read = recv(clientSocket,buf,1024,0);
		buf[read] = '\0';

		char output[1024];
		// if client has input LIST, list all the connections to the server
		if(strcmp(buf,"LIST") == 0){
			int l = 0;
			for(int i = 0 ; i < clientCount ; i ++){
				if(i != index)
					l += snprintf(output + l,1024,"Client %d is at socket %d.\n",i + 1,Client[i].sockID);
			}
			//and send it through the socket
			send(clientSocket,output,1024,0);
			continue;
		}
		//if the client has input SEND, send a message
		if(strcmp(buf,"SEND") == 0){
			//read the message and send it 
			read = recv(clientSocket,buf,1024,0);
			buf[read] = '\0';
			int id = atoi(buf) - 1;
			read = recv(clientSocket,buf,1024,0);
			buf[read] = '\0';
			send(Client[id].sockID,buf,1024,0);
		}
	}
	//return NULL because method is void
	return NULL;
}

//main program
int main(int argc, char** argv){
	//arguments check
	if (argc<2){
		printf("please enter %s <port>",argv[0]);
		return EXIT_FAILURE;//-1
	}
	//socket descriptor
	int port = atoi(argv[1]);
	int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	//server address
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htons(INADDR_ANY);

	//error check for bind
	if(bind(serverSocket,(struct sockaddr *) &serverAddr , sizeof(serverAddr)) == -1) {
		printf("error binding\n");
		return EXIT_FAILURE;//-1
	}
	//errro check for listen
	if(listen(serverSocket,1024) == -1){ //up to 1024 clients
		printf("error listening\n");
		return 0;
	}
	//if successful bind and listen, display message
	printf("Server started listenting on port %i\n",port);

	//infinite loop
	while(1){
		//accept clients
		Client[clientCount].sockID = accept(serverSocket, (struct sockaddr*) &Client[clientCount].clientAddr, &Client[clientCount].len);
		Client[clientCount].index = clientCount;
		//create as many threads as clients that use doNetworking
		pthread_create(&thread[clientCount], NULL, doNetworking, (void *) &Client[clientCount]);
		clientCount ++;
	}

	//join all threads
	for(int i = 0 ; i < clientCount ; i ++)
		pthread_join(thread[i],NULL);

	return EXIT_SUCCESS;
}
