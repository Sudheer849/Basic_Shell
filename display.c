#include "shell_extend.h"
void display_shell()
{
  // struct utsname sys_name;
  // if (uname(&sys_name) < 0)
  //{
  //    perror("uname");
  //}
  char *username;
  username = getenv("USER");
  char name[200];
  char host_name[200];
  int hostname = gethostname(name, sizeof(name));
  int i;
  for (i = 0; i < strlen(name); i++)
  {
    if (name[i] == '-')
    {
      break;
    }
    host_name[i] = name[i];
  }
  host_name[i] = '\0';
  char deviceName[100];
  gethostname(deviceName, sizeof(deviceName));
  if (input_redir == 1)
  {
    dup2(outputfile, STDOUT_FILENO);
  }
  if (output_redir == 1)
  {
    dup2(inputfile, STDIN_FILENO);
  }
  input_redir = 0;
  output_redir = 0;
  if (strstr(dir, "/home") == 0)
  {
    printf("<" YEL "%s@%s" RESET ":" BLU "~%s" RESET ">", username, deviceName, dir);
  }
  else
  {
    printf("<" YEL "%s@%s" RESET ":" BLU "%s" RESET ">", username, deviceName, dir);
  }
}