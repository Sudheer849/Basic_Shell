#include "shell_extend.h"

void bg(char command[100][100], int count)
{
    if (command[1][strlen(command[1]) - 1] == '\n')
    {
        command[1][strlen(command[1]) - 1] = '\0';
    }
    int jobnumber = atoi(command[1]);
    if(statusofpids[jobnumber-1]==0)
   {
      printf("Process with that jobs number doesn't exist\n");
      return;
   }
    int pid = child_pids[jobnumber - 1];
    char name[100];
    strcpy(name,name_of_bgprocess[jobnumber-1]);
    if (kill(pid, SIGCONT) < 0)
    {
        printf("Not able to continue the process\n");
        return;
    }
    printf("# Changes the state of [%d] %s to running (in the # background).\n",jobnumber,name);
}