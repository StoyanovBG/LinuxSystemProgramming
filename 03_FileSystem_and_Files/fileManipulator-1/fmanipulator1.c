#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char * argv[])
{
char str[64];
memset(str, 32, 64);
struct flock fi;
sprintf(str, "Stored by process %i", getpid());
int fd = open("testlo1.txt", O_RDWR|O_CREAT);
fi.l_type = F_WRLCK;
fi.l_whence = SEEK_SET;
fi.l_start = 0;
fi.l_len = 64;
int off = 0;
while (fcntl(fd, F_SETLK, &fi) == -1)
{
fcntl(fd, F_GETLK, &fi);
printf("bytes %i - %i blocked by process %i\n", off, off+64, fi.l_pid
off += 64;
fi.l_start = off;
}
lseek(fd, off, SEEK_SET);
write(fd, str, strlen(str));
getchar();
fi.l_type = F_UNLCK;
if (fcntl(fd, F_SETLK, &fi) == -1) printf("ERROR while blocking!\n");
close(fd);

  FILE * fptr;
  int i,n;
  char str[100];
  char fname[20]="testlo1.txt";
  char str1;
  
    printf("\n\n Write multiple lines in a text file and read the file :\n");
	printf("------------------------------------------------------------\n");   
	printf(" Input the number of lines to be written : ");
	scanf("%d", &n);
	printf("\n :: The lines are ::\n");
	fptr = fopen (fname,"w"); 
	for(i = 0; i < n+1;i++)
		{
		fgets(str, sizeof str, stdin);
		fputs(str, fptr);
		}
  fclose (fptr);
/*-------------- read the file -------------------------------------*/
	fptr = fopen (fname, "r");  
	printf("\n The content of the file %s is  :\n",fname);
	str1 = fgetc(fptr);
	while (str1 != EOF)
		{
			printf ("%c", str1);
			str1 = fgetc(fptr);
		}
    printf("\n\n");
    fclose (fptr);
    return 0;
}
