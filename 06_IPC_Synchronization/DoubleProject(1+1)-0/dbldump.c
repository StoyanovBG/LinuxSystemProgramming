#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shmemtypes.h"
int main(int argc, char* argv[])
{
    struct  memory_block* mblock;


    // Shared Memory Key
    key_t key = ftok(FTOK_FILE, 1);
    if (key == -1)
    {
        printf("Failed to generate unique key. Server compiler with a wrong name?\n");
        return EXIT_FAILURE; // -1
    }

    // Shared Memory Identificator
    int shmid = shmget(key, sizeof(struct memory_block), 0666);
    if (shmid == -1)
    {
        printf("Server is not running!\n");
        return EXIT_FAILURE; // -1
    }

    // Memory Block
    mblock = (struct memory_block*)shmat(shmid, 0, 0);
    while (mblock->complete != 1) {
        printf("segment contains : \n\"%f\"\n", mblock);
        if (mblock->cnt == -1) {
            perror("read");
            return 1;
        }
        printf("Reading Process: Shared Memory: Read %d bytes\n", mblock->cnt);
        sleep(3);
    }
    printf("Reading Process: Reading Done, Detaching Shared Memory\n");
    if (shmdt(mblock) == -1) {
        perror("shmdt");
        return 1;
    }
    printf("Reading Process: Complete\n");
    return 0;
}
