#include "shell_extend.h"

void ls_basic(char command[100][100],int count)
{
    struct dirent *directory_ptr;
        DIR *directory;
        char directory_name[100];
        int flag = 0;
        if (command[count - 1][strlen(command[count - 1]) - 1] == '\n')
        {
            command[count - 1][strlen(command[count - 1]) - 1] = '\0';
        }
        directory = opendir(".");
        while ((directory_ptr = readdir(directory)) != NULL)
        {
            printf("%s\n", directory_ptr->d_name);
        }
        printf("\n");
        return;
}