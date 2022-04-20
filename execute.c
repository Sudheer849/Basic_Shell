#include "shell_extend.h"
void execute_command(char command[100][100], int count)
{
    //printf("%ld\n%s",strlen(command[0]),command[0]);
    if(strcmp(command[count-1],"\n")==0)
    {
        count--;
    }
    char whole_command[1000];
    strcpy(whole_command, command[0]);
    for (int i = 1; i < count; i++)
    {
        strcat(whole_command, command[i]);
    }
    if (whole_command[strlen(whole_command) - 1] == '\n')
    {
        whole_command[strlen(whole_command) - 1] = '\0';
    }
    // if (command[count - 1][strlen(command[count-1])-1]=='\n')
    // {
    //     command[count - 1][strlen(command[count-1])-1]='\0';
    // }
    if (strstr(whole_command, ">") || strstr(whole_command, "<"))
    {
        int count_1 = input_output_redirect(command, whole_command, count);
        if(count_1<0)
        {
            return;
        }
        if (strstr(whole_command, ">") )
        {
            input_redir=1;
        }
        if (strstr(whole_command, "<"))
        {
            //strcpy(command[count_1],"");
            //strcpy(command[count_1+1],"");
            output_redir=1;
        }
        count=count-count_1;
        // printf("%s HIBBB\n",command[0]);
    }
    if (strcmp("cd", command[0]) == 0||strcmp("cd\n", command[0]) == 0)
    {
        if (count == 1)
        {
            dir[0] = '\0';
            return;
        }
        cd(command, count);
    }
    else if (strcmp("echo", command[0]) == 0)
    {
        for (int i = 1; i < count; i++)
        {
            printf(" %s", command[i]);
        }
        printf("\n");
    }
    else if (strcmp("pwd\n", command[0]) == 0 || strcmp("pwd", command[0]) == 0)
    {
        pwd(command, count);
    }
    else if (strcmp("ls\n", command[0]) == 0 || (strcmp("ls", command[0]) == 0 && count==1))
    {
        ls_basic(command, count);
    }
    else if (strcmp("ls", command[0]) == 0)
    {
        ls(command, count);
    }
    else if  (strcmp("pinfo\n", command[0]) == 0 || (strcmp("pinfo", command[0]) == 0 && count==1))
    {
        pinfo(command, count);
    }
    else if (strcmp("pinfo", command[0]) == 0&&count!=1)
    {
        pinfo2(command, count);
    }
    else if (strcmp(command[0], "exit\n") == 0)
    {
        exit(0);
    }
    else if (strcmp(command[0], "repeat") == 0)
    {
        int no_of_times;
        no_of_times = atoi(command[1]);
        char execommands[100][100];
        
        for (int i = 2; i < count; i++)
        {
            strcpy(execommands[i - 2], command[i]);
        }
        for (int i = 0; i < no_of_times; i++)
        {
            execute_command(execommands, count - 2);
        }
    }
    else if (strcmp(command[0], "jobs") == 0 || strcmp(command[0], "jobs\n") == 0)
    {
        jobs(command, count);  
    }
    else if (strcmp(command[0], "sig") == 0)
    {
        sig(command, count);
    }
    else if(strcmp(command[0],"bg")==0)
    {
        bg(command,count);
    }
    else if(strcmp(command[0],"fg")==0)
    {
        fg(command,count);
    }
    else
    {
        if (strcmp(command[count - 1], "&\n") == 0 || strcmp(command[count - 1], "&") == 0)
        {
            strcpy(command[count - 1], "NULL");
            count = count - 1;
            execute_backgroundprocess(command, count);
        }
        else
        {
            execute_forwardprocess(command, count);
        }
    }
  /*  if(input_redir==1)
    {
        dup2(outputfile,STDOUT_FILENO);
    }
    if(output_redir==1)
    {
          dup2(inputfile,STDIN_FILENO);
    }
    input_redir=0;
    output_redir=0;*/

     //dup2(STDIN_FILENO, input_filediscriptor);
     //dup2(STDOUT_FILENO, output_filediscriptor);
    // dup2(Out, STDOUT_FILENO);
}