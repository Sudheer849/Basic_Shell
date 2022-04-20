#include "shell_extend.h"

int parse_pipe(char command[100])
{
    char *duplicate_command = command;
    char *str;
    count = 0;
    while ((str = strtok_r(duplicate_command, "|", &duplicate_command)))
    {
        strcpy(pipe_commands[count], str);
        count++;
    }
    return count;
}
int parse_with_spaces(char command[100])
{
    char *duplicate_command = command;
    char *str;
    count = 0;
    while ((str = strtok_r(duplicate_command, " ", &duplicate_command)))
    {
        strcpy(command_matrix[count], str);
        count++;
    }
    return count;
}

void execute_pipe(char commands[100][100], int count)
{
    char command[1000];
    strcpy(command, commands[0]);
    strcat(command, " ");
    for (int i = 1; i < count; i++)
    {
        strcat(command, commands[i]);
        strcat(command, " ");
    }
    int count_pipe = 0;
    //printf("%s\n", command);
    count_pipe = parse_pipe(command);
    int fds[count_pipe - 1][2];
    for (int i = 0; i < count_pipe; i++)
    {
        if (pipe(fds[i]) < 0)
        {
            printf("Error executing pipe command\n");
        }
        if (i == 0)
        {
            int duplicate_outputfile = dup(STDOUT_FILENO);
            dup2(fds[i][1], STDOUT_FILENO);
            close(fds[i][1]);
            int count_commands = parse_with_spaces(pipe_commands[i]);
            status = 1;
            execute_command(command_matrix, count_commands);
            status = 0;
            dup2(duplicate_outputfile, STDOUT_FILENO);
            close(duplicate_outputfile);
        }
        else if (i != count_pipe - 1)
        {
            int duplicate_inputfile = dup(STDIN_FILENO);
            int duplicate_outputfile = dup(STDOUT_FILENO);
            dup2(fds[i][1], STDOUT_FILENO);
            dup2(fds[i - 1][0], STDIN_FILENO);
            close(fds[i][1]);
            close(fds[i - 1][0]);
            int count_commands = parse_with_spaces(pipe_commands[i]);
            status = 1;
            execute_command(command_matrix, count_commands);
            status = 0;
            dup2(duplicate_inputfile, STDIN_FILENO);
            dup2(duplicate_outputfile, STDOUT_FILENO);
            close(duplicate_inputfile);
            close(duplicate_outputfile);
        }
        else
        {
            int duplicate_inputfile = dup(STDIN_FILENO);
            dup2(fds[count_pipe - 2][0], STDIN_FILENO);
            close(fds[count_pipe - 2][0]);
            int count_commands = parse_with_spaces(pipe_commands[i]);
            //status=1;
            execute_command(command_matrix, count_commands);
            // printf("Hi\n");
            dup2(duplicate_inputfile, STDIN_FILENO);
            close(duplicate_inputfile);
        }
    }
}