#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <strings.h>

int main(int argc, char * argv[])
{
  int msgid;
  int i;
  struct msg_1_t message1;
  struct msg_2_t message2;
  char buf[MAXLEN];
  msgid = msgget(KEY, 0666);
  if (msgid == -1)
  {
     printf("Server is not running!\n");
     return EXIT_FAILURE;
  }
  i = 0;
  while ( (i < (MAXLEN - 1)) && ((message1.body[i++] = getchar()) !=  '\n') );
  message1.body[i] = '\0';
  message1.mtype = 1;
  message1.snd_pid = getpid ();
  msgsnd(msgid, &message1, sizeof(struct msg_1_t), 0);
  msgrcv(msgid, &message2, sizeof(struct msg_2_t), 2, 0);
  printf("Server (pid= %i) responded: %s\n", message2.snd_pid, message2.body);
  message1.mtype = 1;
  msgsnd(msgid, &message1, sizeof(struct msg_1_t), 0);
  return EXIT_SUCCESS;
}
