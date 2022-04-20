#include "shell_extend.h"

void execute_forwardprocess(char command[100][100], int count)
{
    pid_t process_id;
    int status;
    process_id = fork();
    fore_pid = process_id;
    //pid_t process_id;
    if (process_id == -1)
    {
        printf("Not able to create a child process\n");
        return;
    }
    else if (process_id == 0)
    {
        if (command[count - 1][strlen(command[count - 1]) - 1] == '\n')
        {
            command[count - 1][strlen(command[count - 1]) - 1] = '\0';
        }
        char *hi[1000];
        for (int i = 0; i < count; i++)
        {
            hi[i] = (char *)malloc(sizeof(char) * 1000);
            //if (strcmp(command[i], ""))
            //{
            strcpy(hi[i], command[i]);
            // }
        }
        //hi[count] = NULL;

        char *string;
        string = (char *)malloc(sizeof(char) * 1000);
        strcpy(string, command[0]);
        setpgid(0, 0);
        if (execvp(hi[0], hi) < 0)
        {
            printf("No such command exists\n");
        }
        close(input_filediscriptor);
        exit(0);
    }
    else if (process_id > 0)
    {
        int status;
        //kill(process_id,WUNTRACED);
        strcpy(fore_name, command[0]);
        for (int i = 1; i < count; i++)
        {
            strcat(fore_name, " ");
            strcat(fore_name, command[i]);
        }
        if(fore_name[strlen(fore_name)-1]=='\n')
        {
            fore_name[strlen(fore_name)-1]='\0';
        }
     

        waitpid(process_id, &status, WUNTRACED);
        fore_pid = -1;
        fore_name[0]='\0';
    }
}