#include "shell_extend.h"

void Handle_ctrlC(int signal)
{
    if (fore_pid != -1)
    {
        kill(fore_pid, SIGINT);
        printf("\n");
        fflush(stdout);
    }
    else
    {
        printf("\n");
        display_shell();
        fflush(stdout);
        return;
    }
}

void Handle_ctrlZ(int signal)
{
    for (int i = 0; i < pidno; i++)
    {
        if (statusofpids[i] == 2)
        {
            statusofpids[i] = 1;
        }
    }
    if (fore_pid != -1)
    {
        child_pids[pidno] = fore_pid;
        statusofpids[pidno] = 1;
        strcpy(name_of_bgprocess[count_bg], fore_name);
        count_bg++;
        pidno = pidno + 1;
        printf("\n");
        kill(fore_pid, SIGTSTP);
        fflush(stdout);   
    }
    else
    {
        printf("\n");
        display_shell();
        fflush(stdout);
    }
}