#include <stdio.h>
int i;
void * thread_func(void * arg)
{
  pthread_setcanceltype(NULL);
  pthread_setcancelstate(NULL);
  for(i=0; i<4; i++)
  {
     sleep(1);
     printf("I am running verry important process %i ...\n", i+1);
  }
  
  pthread_testcancel();
  printf("YOU WILL NOT STOP ME!!!\n");
}
int main(int argc, char * argv[])
{
  
  
  while(i < 1) sleep(1);
  thread_func(fread);
  printf("Requsted to cancel the thread!\n");
  pthread_join(fread);
  printf("The thread is stopped!\n");
  return 0;
}
