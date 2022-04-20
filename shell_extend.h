#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <signal.h>
#define clear() printf("\033[H\033[J")
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"


void display_shell();
//int open(const char* Path, int flags,int mode); 
void check_for_terminated_child_proccess(int signal);
void Handle_ctrlC(int signal);
void Handle_ctrlZ(int signal);
void execute_forwardprocess(char command[100][100], int count);
void execute_backgroundprocess(char command[100][100], int count);
void execute_command(char command[100][100], int count);
void break_input_command(char *input_command);
void cd(char command[100][100],int count);
void echo(char command[100][100], int count);
void ls_basic(char command[100][100],int count);
void ls(char command[100][100],int count);
void pinfo(char command[100][100],int count);
void pinfo2(char command[100][100],int count);
void pwd(char command[100][100], int count);
int input_output_redirect(char command[100][100], char whole_command[1000], int count);
void jobs();
void jobs_with_flags(char command[100][100],int count);
void sig(char command[100][100],int count);
void execute_pipe(char commands[100][100],int count);
int parse_pipe(char command[100]);
void bg(char command[100][100],int count);
void fg(char command[100][100],int count);

extern char command_matrix[100][100];
extern int parse_with_spaces(char command[100]);
extern int inputfile,outputfile;
extern int status;
extern char name_of_bgprocess[1000][1000];
extern int count, iteration;
extern char store_previous[100];
extern char dir[100];
extern char directory_path[100];
extern char duplicate_dir[100];
extern char store_commands[100][100];
extern int statusofpids[1000];
extern int child_pids[1000];
extern int pidno ;
extern char history[100000];
extern int history_count;
extern char string[10000][10000];
extern int In,Out;
extern int count_bg;
extern int input_filediscriptor;
extern const char * const sys_signame[];
extern int output_filediscriptor;
extern int input_redir,output_redir;
extern char pipe_commands[100][100];
extern int shell_pid;
extern int fore_pid;
extern char fore_name[100];

#endif