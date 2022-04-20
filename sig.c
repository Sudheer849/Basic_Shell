#include "shell_extend.h"

void sig(char command[100][100], int count)
{
   if (command[count - 1][strlen(command[count - 1]) - 1] == '\n')
   {
      command[count - 1][strlen(command[count - 1]) - 1] = '\0';
   }
   int signal_number = atoi(command[2]);
   int job_number = atoi(command[1]);
   // printf("%d\n",signal_number);
   if (job_number < 2 && job_number > 32)
   {
      printf("Invalid job number\n");
      return;
   }
   if(statusofpids[job_number-1]==0)
   {
      printf("Process with that jobs number doesn't exist\n");
      return;
   }
   char *signame[33] = {"-1", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT", "SIGCHLD", "SIGCONT", "SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGPOLL", "SIGPWR", "SIGSYS", "NULL"};
   char name[100];
   strcpy(name, name_of_bgprocess[job_number - 1]);
   kill(child_pids[job_number - 1], signal_number);
   printf("# sends %s (signal number %d) to the process %s\n", signame[signal_number], signal_number, name);
}