#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#define BUF_SIZE 256
int main(int argc, char ** argv)
{
  char buf[BUF_SIZE];
  if (argc < 2)
  {
    fprintf(stderr,"usage: %s <port_number>\n", argv[0]);
    return EXIT_FAILURE;
  }
  int sock_server = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_server < 0)
{
    printf("Error creating socket! Err.No: %d\n", errno);
    return EXIT_FAILURE; // -1
  }
  struct sockaddr_in serv_addr, cli_addr;
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  int port = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);
  if (bind(sock_server, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("Eror binding socket! Err.No: %d\n", errno);
    return EXIT_FAILURE; // -1
  }
  listen(sock_server, 1); // Single Client
  int clen = sizeof(cli_addr);
  int sock_client = accept(sock_server, (struct sockaddr *) &cli_addr, &clen);
  if (sock_client < 0)
  {
printf("Error accepting the client! Err.No: %d\n", errno);
    return EXIT_FAILURE; // -1
  }
  memset(buf, 0, BUF_SIZE);
  read(sock_client, buf, BUF_SIZE-1);
  buf[BUF_SIZE] = 0;
  printf("Received message: %s\n", buf);
  write(sock_client, "OK", 2);
  close(sock_client);
  close(sock_server);
  return EXIT_SUCCESS; // 1
}

void print_vect(int *v, int n)
{
  int i;
  for(i=0; i<n; i++) printf("%i", v[i]);
  printf("\n");
}
void swap(int *i, int *j)
{
  int t;
  t = *i;
  *i = *j;
  *j = t;
}
void reverse(int * v, int n)
{
  int i;
  for(i = 0; i < (n/2); i++)
  swap(&v[i], &v[n-1-i]);
}
int next_permutation(int *v, int n)
{
  int i, j;
  i = n - 1;
  while ((i > 1) && (v[i] < v[i-1])) i--;
  if (v[i] > v[i-1])
{
    j = n - 1;
    while (v[j] < v[i-1]) j--;
    swap(&v[j], &v[i-1]);
    reverse(&v[i], n-i);
    return 1;
  }
  return 0;
}
void * thread_func(void *arg)
{
  int i;
  int n =*(int *)arg;
  int *v = malloc(sizeof(int)*n);
  for(i=0; i<n; i++) v[i] = i+1;
  print_vect(v,n);
  while(next_permutation(v,n) != 0)
  {
    print_vect(v, n);
    sync();
}
  free(v);
  pthread_exit(arg);


{
  void * ret;
  int result;
  pthread_t thread1, thread2;
  int size1 = 4;
  result = pthread_create(&thread1, NULL, thread_func, &size1);
  if(result != 0)
  {
    printf("Error creating thread one!\n");
    return EXIT_FAILURE; // -1
  }
  int size2 = 3;
  result = pthread_create(&thread2, NULL, thread_func, &size2);
  if(result != 0)
  {
printf("Error creating thread two!\n");
    return EXIT_FAILURE; // -1
  }
  result = pthread_join(thread1, &ret);
  if(result != 0)
  {
    printf("Error joining thread one!\n");
    return EXIT_FAILURE; // -1
  }
 else printf("Thread one finished with result: %i\n", *(int *)ret);
  result = pthread_join(thread2, &ret);
  if(result != 0)
  {
    printf("Error joining thread two!\n");
    return EXIT_FAILURE; // -1
  }
 else printf("Thread two finished with result: %i\n", *(int *)ret);
  printf("Job Done!\n");
  }

int chmod (p);
{
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
}


return EXIT_SUCCESS;
} 
