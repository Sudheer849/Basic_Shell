#include "shell_extend.h"

void execute_backgroundprocess(char command[100][100], int count)
{
    //printf("%s\n",command[0]);
    int status;
    char **hi = malloc(sizeof(char *) * (1000));
    for (int i = 0; i < count; i++)
    {
        hi[i] = (char *)malloc(1000);
    }
    for (int i = 0; i < count; i++)
    {
        strcpy(hi[i], command[i]);
    }
    hi[count] = NULL;
    char *string = (char *)malloc(sizeof(char) * 100);
    strcpy(string, command[0]);
    pid_t process_id;
    process_id = fork();
    if (process_id == -1)
    {
        perror("Error");
    }
    if (process_id != 0)
    {
        char name_of_bg[1000];
        strcpy(name_of_bg,command[0]);
        for(int i=1;i<count;i++)
        {
        strcat(name_of_bg, " ");
        strcat(name_of_bg,command[i]);
        }
        strcpy(name_of_bgprocess[count_bg],name_of_bg);
        count_bg++;
        printf("%d\n", process_id);
        child_pids[pidno] = process_id;
        statusofpids[pidno] = 1;
        pidno = pidno + 1;
    }
    if (process_id == 0)
    {
        setpgid(0, 0);
        if (execvp(string, hi) < 0)
        {
            printf("Invalid Command\n");
        }
    }
    else
    {
       //waitpid(process_id, &status, WNOHANG);
       kill(process_id, SIGCONT);
    }
    return;
}