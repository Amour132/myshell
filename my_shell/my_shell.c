#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int argc = 0;
char *argv[8];

void do_prase(char *buf)
{
  int i = 0;
  int status = 0;
  for(argc=i=0; buf[i]; i++)
  {
    if(!isspace(buf[i]) && status==0)
    {
      argv[argc++] = buf+i;
      status = 1;
    }
    else if(isspace(buf[i]))
    {
      status = 0;
      buf[i] = 0;
    }
  }
  argv[argc] = NULL;
}

void do_execute()
{
  pid_t id = fork();
  if(id < 0)
  {
    printf("fork error\n");
    exit(1);
  }
  else if(id == 0)
  {
    execvp(argv[0],argv);
  }
  else{
    int st;
    while(wait(&st) != id)
    {
      ;
    }
  }

}

int main()
{
  char buf[2] = {0};
  while(1)
  {
    printf("[djh@localhost myshell]# ");
    int i = scanf("%[^\n]%*c",buf);
    if(i ==0)
    {
      printf("scanf error %d\n",i);
      exit(1);
    }
    do_prase(buf);
    do_execute();
  }

  return 0;
}
