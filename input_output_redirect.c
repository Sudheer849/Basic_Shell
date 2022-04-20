#include "shell_extend.h"

int input_output_redirect(char command[100][100], char whole_command[1000], int count)
{
    int x=0;
    if (strstr(whole_command, "<"))
    {
        for (int i = 0; i < count; i++)
        {
            if (!strcmp(command[i], "<"))
            {
                if (command[i + 1][strlen(command[i + 1]) - 1] == '\n')
                {
                    command[i + 1][strlen(command[i + 1]) - 1] = '\0';
                }
                input_filediscriptor = open(command[i + 1], O_RDONLY);

                if (input_filediscriptor < 0)
                {
                    printf("No Such file exists in the Current Directory\n");
                    return -1;
                }
                else
                {
                    inputfile=dup(STDIN_FILENO);
                    dup2(input_filediscriptor, STDIN_FILENO);
                   // close(input_filediscriptor);
                   x=x+2;
                }
                break;
            }
        }
    }
    if (strstr(whole_command, ">"))
    {
        for (int i = 0; i < count; i++)
        {
            if (command[i + 1][strlen(command[i + 1]) - 1] == '\n')
            {
                command[i + 1][strlen(command[i + 1]) - 1] = '\0';
            }
            if (!strcmp(command[i], ">") || !strcmp(command[i], ">>"))
            {
                if (!strcmp(command[i], ">>"))
                {
                    output_filediscriptor = open(command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                }
                else
                {
                    output_filediscriptor = open(command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }

                if (output_filediscriptor < 0)
                {
                    printf("Error opening output file\n");
                }
                else
                {
                    if(status==0){
                    outputfile=dup(STDOUT_FILENO);
                    dup2(output_filediscriptor, STDOUT_FILENO);
                    close(output_filediscriptor);
                    x=x+2;
                    }
                }
                break;
            }
        }
    }
    return x;
}