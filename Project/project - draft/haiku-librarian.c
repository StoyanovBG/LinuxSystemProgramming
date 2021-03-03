#include<stdio.h>
#include<stdlib.h>
#include <string.h>



// Main Functoin
int main(int argc, char* argv[])
{
    int result;
    char buf[50];
    char filePath[50] = "/haiku/students-files/";
    char c;
    FILE * fptrR, * fptrW;
    fptrW = fopen("./library.txt", "w");

    while (1)
    {
        //Get the name of students file 
        while (1)
        {
            FILE* fptr = fopen("/dev/shm/inbox.txt", "r");
            fscanf(fptr, "%[^\n]", buf);
            if (sizeof(buf) > 1)
            {
                fclose(fopen("/dev/shm/inbox.txt", "w")); // Clear inbox.txt
                break;
            }
        }
        strcat(filePath, buf);
        fptrR = fopen(filePath, "r");

        //Insert Date&Time before content.
        time_t t = time(NULL);
        struct tm* tm = localtime(&t);
        fprintf(fptrW, "%s\n", asctime(tm));
        //Copy content from student's file to Library
        c = fgetc(fptrR);
        while (c != EOF)
        {
            fputc(c, fptrW);
            c = fgetc(fptrR);
        }
        fclose(fopen(filePath, "w")); // Clear student's file.
        fclose(fptrR);
    }

    return EXIT_SUCCESS; // 0
}


