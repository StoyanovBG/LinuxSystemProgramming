#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[])
{
    
    
    // pid
    int pid = fork();
    switch (pid)
    {
    case -1: // error
    {
        printf("Error fork the process.\n");
        exit(EXIT_FAILURE);
    }
    case  0: // child process
        break;
    default: // parent process
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0)
    {
        printf("Error changing the session ID.\n");
        exit(EXIT_FAILURE);
    }

    if (chdir("/") < 0)
    {
        printf("Error changing the process folder.\n");
        exit(EXIT_FAILURE);
    }

    do {
        char string[100];
        gets(string);
        printf("Poluchih String:%s\n", string);
    }while(1);

}
