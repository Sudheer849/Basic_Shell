#include "shell_extend.h"

void ls(char command[100][100],int count)
{
    struct dirent *directory_ptr;
        DIR *directory;
        char directory_name[100];
        int flag = 0;
        if (command[count - 1][strlen(command[count - 1]) - 1] == '\n')
        {
            command[count - 1][strlen(command[count - 1]) - 1] = '\0';
        }
        if (strcmp(command[count - 1], ".") == 0)
        {
            directory = opendir(".");
            while ((directory_ptr = readdir(directory)) != NULL)
            {
                printf("%s ", directory_ptr->d_name);
            }
            printf("\n");
            return;
        }
        else if (strcmp(command[count - 1], "..") == 0 || strcmp(command[count - 1], "~") == 0)
        {
            directory = opendir("..");
            while ((directory_ptr = readdir(directory)) != NULL)
            {
                printf("%s\n", directory_ptr->d_name);
            }
            return;
        }
        char alldirectories[1000][1000];
        int count_a = 0, count_l = 0, num = 0;
        for (int i = 0; i < count; i++)
        {
            if (strcmp(command[i], "-l") == 0 || strcmp(command[i], "-l\n") == 0)
            {
                count_l++;
            }
            else if (strcmp(command[i], "-a") == 0 || strcmp(command[i], "-a\n") == 0)
            {
                count_a++;
            }
            else if (strcmp(command[i], "-la") == 0 || strcmp(command[i], "-al") == 0 || strcmp(command[i], "-la\n") == 0 || strcmp(command[i], "-al\n") == 0)
            {
                count_a++;
                count_l++;
            }
            else
            {
                if (command[i][strlen(command[i]) - 1] == '\n')
                {
                    command[i][strlen(command[i]) - 1] == '\0';
                }
                strcpy(alldirectories[num], command[i]);
                num++;
            }
        }
        if (num == 1)
        {
            directory = opendir(".");
            if (directory == NULL)
            {
                printf("Not able to open the directory\n");
            }
            else
            {

                if (count_l == 0 && count_a != 0)
                {
                    while ((directory_ptr = readdir(directory)) != NULL)
                    {
                        printf("%s ", directory_ptr->d_name);
                    }
                    printf("\n");
                }
                else if (count_a == 0 && count_l != 0)
                {
                    struct passwd *pwd;
                    int size_inbytes = 0;
                    while ((directory_ptr = readdir(directory)) != NULL)
                    {
                        if (directory_ptr->d_name[0] != '.')
                        {
                            char str[100];
                            strcpy(str, directory_ptr->d_name);
                            struct stat f_name;
                            if (stat(str, &f_name) == -1)
                            {
                                perror("ERROR");
                            }
                            printf((S_ISDIR(f_name.st_mode)) ? "d" : "-");
                            printf((f_name.st_mode & S_IRUSR) ? "r" : "-");
                            printf((f_name.st_mode & S_IWUSR) ? "w" : "-");
                            printf((f_name.st_mode & S_IXUSR) ? "x" : "-");
                            printf((f_name.st_mode & S_IRGRP) ? "r" : "-");
                            printf((f_name.st_mode & S_IWGRP) ? "w" : "-");
                            printf((f_name.st_mode & S_IXGRP) ? "x" : "-");
                            printf((f_name.st_mode & S_IROTH) ? "r" : "-");
                            printf((f_name.st_mode & S_IWOTH) ? "w" : "-");
                            printf((f_name.st_mode & S_IXOTH) ? "x" : "-");
                            printf(" %ld ", f_name.st_nlink);
                            if ((pwd = getpwuid(f_name.st_uid)) != NULL)
                            {
                                printf(" %-8.8s", pwd->pw_name);
                                printf(" %-8.8s", pwd->pw_name);
                            }
                            printf(" %8ld ", f_name.st_size);
                            char last_modified_date[100];
                            strftime(last_modified_date, 20, "%b %d %H:%M ", localtime(&(f_name.st_mtime)));
                            printf(" %s ", last_modified_date);
                            size_inbytes = size_inbytes + f_name.st_blocks;
                            printf("%s\n", directory_ptr->d_name);
                        }
                    }
                    printf("total: %d\n", size_inbytes);
                }
                else if (count_a != 0 && count_l != 0)
                {
                    struct passwd *pwd;
                    int size_inbytes = 0;
                    while ((directory_ptr = readdir(directory)) != NULL)
                    {
                        char str[100];
                        strcpy(str, directory_ptr->d_name);
                        struct stat f_name;
                        if (stat(str, &f_name) == -1)
                        {
                            perror("ERROR");
                        }
                        printf((S_ISDIR(f_name.st_mode)) ? "d" : "-");
                        printf((f_name.st_mode & S_IRUSR) ? "r" : "-");
                        printf((f_name.st_mode & S_IWUSR) ? "w" : "-");
                        printf((f_name.st_mode & S_IXUSR) ? "x" : "-");
                        printf((f_name.st_mode & S_IRGRP) ? "r" : "-");
                        printf((f_name.st_mode & S_IWGRP) ? "w" : "-");
                        printf((f_name.st_mode & S_IXGRP) ? "x" : "-");
                        printf((f_name.st_mode & S_IROTH) ? "r" : "-");
                        printf((f_name.st_mode & S_IWOTH) ? "w" : "-");
                        printf((f_name.st_mode & S_IXOTH) ? "x" : "-");
                        printf(" %ld ", f_name.st_nlink);
                        if ((pwd = getpwuid(f_name.st_uid)) != NULL)
                        {
                            printf(" %-8.8s", pwd->pw_name);
                            printf(" %-8.8s", pwd->pw_name);
                        }
                        printf(" %8ld ", f_name.st_size);
                        char last_modified_date[100];
                        strftime(last_modified_date, 20, "%b %d %H:%M ", localtime(&(f_name.st_mtime)));
                        printf(" %s ", last_modified_date);
                        size_inbytes = size_inbytes + f_name.st_blocks;
                        printf("%s\n", directory_ptr->d_name);
                    }
                    printf("total: %d\n", size_inbytes);
                }
            }
        }
        for (int i = 1; i < num; i++)
        {
            directory = opendir(alldirectories[i]);
            chdir(alldirectories[i]);
            if (directory == NULL)
            {
                printf("%s directory path do not exists\n", alldirectories[i]);
            }
            else
            {
                printf("%s:\n", alldirectories[i]);

                if (count_l == 0 && count_a != 0)
                {
                    while ((directory_ptr = readdir(directory)) != NULL)
                    {
                        printf("%s ", directory_ptr->d_name);
                    }
                    printf("\n");
                }
                else if (count_a == 0 && count_l != 0)
                {
                    struct passwd *pwd;
                    int size_inbytes = 0;
                    while ((directory_ptr = readdir(directory)) != NULL)
                    {
                        if (directory_ptr->d_name[0] != '.')
                        {
                            char str[100];
                            strcpy(str, directory_ptr->d_name);
                            struct stat f_name;
                            if (stat(str, &f_name) == -1)
                            {
                                perror("ERROR");
                            }
                            // printf("%s ",str);
                            printf((S_ISDIR(f_name.st_mode)) ? "d" : "-");
                            printf((f_name.st_mode & S_IRUSR) ? "r" : "-");
                            printf((f_name.st_mode & S_IWUSR) ? "w" : "-");
                            printf((f_name.st_mode & S_IXUSR) ? "x" : "-");
                            printf((f_name.st_mode & S_IRGRP) ? "r" : "-");
                            printf((f_name.st_mode & S_IWGRP) ? "w" : "-");
                            printf((f_name.st_mode & S_IXGRP) ? "x" : "-");
                            printf((f_name.st_mode & S_IROTH) ? "r" : "-");
                            printf((f_name.st_mode & S_IWOTH) ? "w" : "-");
                            printf((f_name.st_mode & S_IXOTH) ? "x" : "-");
                            printf(" %ld ", f_name.st_nlink);
                            if ((pwd = getpwuid(f_name.st_uid)) != NULL)
                            {
                                printf(" %-8.8s", pwd->pw_name);
                                printf(" %-8.8s", pwd->pw_name);
                            }
                            printf(" %8ld ", f_name.st_size);
                            char last_modified_date[100];
                            strftime(last_modified_date, 20, "%b %d %H:%M ", localtime(&(f_name.st_mtime)));
                            printf(" %s ", last_modified_date);
                            size_inbytes = size_inbytes + f_name.st_blocks;
                            printf("%s\n", directory_ptr->d_name);
                        }
                    }
                    printf("total: %d\n", size_inbytes);
                }
                else if (count_a != 0 && count_l != 0)
                {
                    struct passwd *pwd;
                    int size_inbytes = 0;
                    while ((directory_ptr = readdir(directory)) != NULL)
                    {
                        char str[100];
                        strcpy(str, directory_ptr->d_name);
                        struct stat f_name;
                        if (stat(str, &f_name) == -1)
                        {
                            perror("ERROR");
                        }
                        // printf("%s ",str);
                        printf((S_ISDIR(f_name.st_mode)) ? "d" : "-");
                        printf((f_name.st_mode & S_IRUSR) ? "r" : "-");
                        printf((f_name.st_mode & S_IWUSR) ? "w" : "-");
                        printf((f_name.st_mode & S_IXUSR) ? "x" : "-");
                        printf((f_name.st_mode & S_IRGRP) ? "r" : "-");
                        printf((f_name.st_mode & S_IWGRP) ? "w" : "-");
                        printf((f_name.st_mode & S_IXGRP) ? "x" : "-");
                        printf((f_name.st_mode & S_IROTH) ? "r" : "-");
                        printf((f_name.st_mode & S_IWOTH) ? "w" : "-");
                        printf((f_name.st_mode & S_IXOTH) ? "x" : "-");
                        printf(" %ld ", f_name.st_nlink);
                        if ((pwd = getpwuid(f_name.st_uid)) != NULL)
                        {
                            printf(" %-8.8s", pwd->pw_name);
                            printf(" %-8.8s", pwd->pw_name);
                        }
                        printf(" %8ld ", f_name.st_size);
                        char last_modified_date[100];
                        strftime(last_modified_date, 20, "%b %d %H:%M ", localtime(&(f_name.st_mtime)));
                        printf(" %s ", last_modified_date);
                        size_inbytes = size_inbytes + f_name.st_blocks;
                        printf("%s\n", directory_ptr->d_name);
                    }
                    printf("total: %d\n", size_inbytes);
                }
            }
        }
}