#include "shell_extend.h"

void break_input_command(char *input_command)
{
    char *command;
    char *duplicate_string = input_command;
    while ((command = strtok_r(duplicate_string, ";", &duplicate_string)))
    {
        char *duplicate_command = command;
        char *str;
        char command_including_flags[100][100];
         count = 0;
        while ((str = strtok_r(duplicate_command, " ", &duplicate_command)))
        {
            strcpy(command_including_flags[count], str);
            count++;
        }
        for(int i=0;i<count;i++)
        {
            if(strstr(command_including_flags[i],"|"))
            {
                execute_pipe(command_including_flags,count);
                return;
            }
        }
        execute_command(command_including_flags, count);
    }
}