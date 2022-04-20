#include "shell_extend.h"

void check_for_terminated_child_proccess(int signal)
{
    int count=0;
    for (int i = 0; i < pidno; i++)
    {
        if (statusofpids[i] == 1)
        {
            int status;
            pid_t pid = waitpid(child_pids[i], &status, WNOHANG);
            if (pid > 0)
            {
                count++;
                if (!status)
                {
                    printf("\npid %d exited normally\n", pid);
                }
                else
                {
                    printf("\npid %d exited abnormally\n", pid);
                }
                statusofpids[i] = 0;
            }
        }
    }
    if(count!=0){
    display_shell();
    fflush(stdout);
    }
}