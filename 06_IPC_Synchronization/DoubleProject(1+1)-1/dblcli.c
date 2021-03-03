#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbldump.h"

int main(int argc, char * argv[])
{
  key_t key;
  int shmid;
  struct memory_block * mblock;
  key = ftok(FTOK_FILE, 1); 
  if (key == -1)
  {
     printf("Failed to generate unique key. Server compiler with a wrong name?\n");
     return EXIT_FAILURE;
  }

  shmid = shmget(key, sizeof(struct memory_block), 0666);
  if (shmid == -1)
  {
     printf("Server is not running!\n");
     return EXIT_FAILURE;
  }

  mblock = (struct memory_block *) shmat(shmid, 0, 0);
  while (strcmp("q\n", mblock->string) != 0)
  {
     int i = 0;
     mblock->client_lock = BUSY;
     mblock->turn = SERVER;
     while ((mblock->server_lock == BUSY) && (mblock->turn == SERVER));
     if (mblock->readlast == SERVER)
     {
        mblock->readlast = CLIENT;
        printf("Server sends %s\n", mblock->string);
        while ((i < (MAXLEN - 1)) && ((mblock->string[i++] = getchar()) !=  '\n') );
        mblock->string[i] = 0;
        mblock->client_lock = FREE;
     }
  }
  printf("Client exits\n");
  shmdt((void *) mblock);
  return EXIT_SUCCESS;
}
