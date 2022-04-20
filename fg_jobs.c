#include "shell_extend.h"

void fg(char command[100][100], int count)
{
    if (command[1][strlen(command[1]) - 1] == '\n')
    {
        command[1][strlen(command[1]) - 1] = '\0';
    }
    int jobnumber = atoi(command[1]);
    if (statusofpids[jobnumber - 1] == 0)
    {
        printf("Process with that jobs number doesn't exist\n");
        return;
    }
    statusofpids[jobnumber - 1] = 2;
    char name[100];
    strcpy(name, name_of_bgprocess[jobnumber - 1]);
    int pid = child_pids[jobnumber - 1];
    if (kill(pid, SIGCONT) < 0)
    {
        printf("Error occured in making the process continue\n");
    }
    statusofpids[jobnumber - 1] = 0;
    printf("# brings [%d] %s to the foreground\n", jobnumber, name);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    tcsetpgrp(0, pid);
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(0, shell_pid);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    fore_pid = -1;
    if (WIFSTOPPED(status))
    {
        statusofpids[jobnumber - 1] = 1;
    }
}
