#include "shell_extend.h"

int count = 0, iteration = 0;
char store_previous[100];
char dir[100];
char directory_path[100];
char duplicate_dir[100];
char store_commands[100][100];
char string[10000][10000];
int statusofpids[1000] = {0};
char name_of_bgprocess[1000][1000];
int child_pids[1000];
int pidno = 0;
char history[100000];
int history_count = 0;
int In, Out;
int count_bg = 0;
int input_filediscriptor=1, output_filediscriptor=0;
const char *const sys_signame[100];
int input_redir=0,output_redir=0;
char pipe_commands[100][100];
int shell_pid;
char command_matrix[100][100];
int inputfile,outputfile;
int status=0;
int fore_pid=-1;
char fore_name[100];

int main()
{
    shell_pid = getpid();
    signal(SIGCHLD, check_for_terminated_child_proccess);
    signal(SIGINT,Handle_ctrlC);
    signal(SIGTSTP,Handle_ctrlZ);
    //dup2(In, STDIN_FILENO);
    //dup2(Out, STDOUT_FILENO);
    dir[0] = '\0';
    getcwd(directory_path, sizeof(directory_path));
    while (1)
    {
        fflush(stdout);
        strcpy(store_commands[iteration], dir);
        if (iteration > 0)
        {
            strcpy(store_previous, store_commands[iteration - 1]);
        }
        display_shell();
        char *input_command = NULL;
        size_t size = 0;

        //dup2(In, STDIN_FILENO);
        dup2(STDIN_FILENO,0);
        dup2(STDOUT_FILENO,1);
        if (getline(&input_command, &size, stdin) == -1)
        {
            printf("\n");
            exit(0);
            //fprintf(stderr, "Not able to read the command, Please try again\n");
        }
        if(strcmp(input_command,"\n")==0)
        {
             continue;
        }
        if (input_command != NULL)
        {
            break_input_command(input_command);
        }
        iteration++;
    }
}