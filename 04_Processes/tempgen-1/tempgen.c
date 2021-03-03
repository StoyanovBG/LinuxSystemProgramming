#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
int main(int argc , char * argv[])
{
 if(argc != 2)
{
printf("Syntax misstake! Please enter 1 argument!/n");
}
int file_count = atoi(argv[1]);
char *ch  = argv[1];
size_t len = strlen(ch);
for(int i =0 ; i<file_count ; i++)
{
  if(len == 2)
 {
 strcpy(ch,"temp");
   if(i < 10)
   {
     strncat(ch,"0");
   }
  strncat(ch,i);
  strncat(ch,".tmp");
 
 }
if(len == 3)
 {
 strcpy(ch,"temp");
 if(i < 10)
 {
  strncat(ch,"00");
 }
  if (i < 100)
 {
  strncat(ch,"0");
 }
 strncat(ch,i);
 strncat(ch,".tmp");
 }
}
printf("%s",ch);
return 0;
}
