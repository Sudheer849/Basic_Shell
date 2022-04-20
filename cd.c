#include "shell_extend.h"

void cd(char command[100][100],int count)
{
    if (command[1][strlen(command[1]) - 1] == '\n')
        {
            command[1][strlen(command[1]) - 1] = '\0';
        }
        if (strcmp(command[1], "~") == 0)
        {
            dir[0] = '\0';
        }
        else if (strcmp(command[1], "..") == 0)
        {

            int index = -1;
            for (int i = strlen(dir) - 1; i >= 0; i--)
            {
                if (dir[i] == '/')
                {
                    index = i;
                    break;
                }
            }
            if (index != -1)
            {
                dir[index] = '\0';
            }
            return;
        }
        else if (strcmp(command[1], ".") == 0)
        {
            return;
        }
        else if (strcmp(command[1], "-") == 0)
        {
            strcpy(dir, store_commands[iteration - 1]);
            return;
        }
        else
        {
            char home_directory[1000];
            getcwd(home_directory, sizeof(home_directory));
            char home[6] = "/home";
            int flag = 0;
            for (int i = 0; i < 5; i++)
            {
                if (command[1][i] != home[i])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                if (chdir(command[1]) < 0)
                {
                    printf("%s doesn't exists", command[1]);
                    return;
                }
                strcpy(dir, command[1]);
                chdir(directory_path);
            }
            else
            {
                char d_dir[100], check[100], direc[100], dd_dir[100], first_check[100];
                strcpy(first_check, dir);
                strcat(first_check, "/");
                strcat(first_check, command[1]);
                if (chdir(first_check) < 0)
                {
                    strcpy(d_dir, dir);
                    strcpy(dd_dir, dir);
                    strcpy(check, directory_path);
                    strcat(check, "/");
                    strcpy(d_dir, check);
                    strcat(d_dir, dir);
                    strcat(check, command[1]);
                    strcpy(direc, command[1]);

                    if (chdir(check) < 0)
                    {
                        strcat(d_dir, "/");
                        strcat(d_dir, command[1]);
                        if (chdir(d_dir) < 0)
                        {
                            printf("%s doesn't exists", command[1]);
                        }
                        else
                        {
                            chdir(home_directory);
                            strcpy(dir, dd_dir);
                            strcat(dir, "/");
                            strcat(dir, command[1]);
                        }
                    }
                    else
                    {
                        chdir(directory_path);
                        char with_slash[100];
                        strcpy(with_slash, "/");
                        strcat(with_slash, command[1]);
                        strcpy(dir, with_slash);
                    }
                }
                else
                {
                    strcpy(dir, first_check);
                }
            }
        }
}