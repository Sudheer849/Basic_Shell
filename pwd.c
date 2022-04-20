#include "shell_extend.h"

void pwd(char command[100][100], int count)
{
    char current_dir[100];
    char home[6] = "/home";
    int flag = 0;
    for (int i = 0; i < 5; i++)
    {
        if (dir[i] != home[i])
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("%s\n", dir);
    }
    else
    {
        char strt[100];
        strcpy(strt, directory_path);
        strcat(strt, dir);
        printf("%s\n", strt);
    }
}