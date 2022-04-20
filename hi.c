#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#define clear() printf("\033[H\033[J")
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

int count = 0, iteration = 0;
char store_previous[100];
char dir[100];
char directory_path[100];
char duplicate_dir[100];
char store_commands[100][100];
char string[10000][10000];
int statusofpids[1000] = {0};
int child_pids[1000];
int pidno = 0;
char history[100000];
int history_count = 0;

void display_shell()
{
    struct utsname sys_name;
    if (uname(&sys_name) < 0)
    {
        perror("uname");
    }
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
    printf("<" YEL "%s@%s" RESET ":" BLU "~%s" RESET "> ", host_name, deviceName, dir);
}
void check_for_terminated_child_proccess()
{
    for (int i = 0; i < pidno; i++)
    {
        if (statusofpids[i] == 1)
        {
            int status;
            pid_t pid = waitpid(child_pids[i], &status, WNOHANG);
            if (pid > 0)
            {
                if (!status)
                {
                    fprintf(stderr, "\npid %d exited normally\n", pid);
                }
                else
                {
                    fprintf(stderr, "\npid %d exited abnormally\n", pid);
                }
                statusofpids[i] = 0;
            }
        }
    }
}
void execute_forwardprocess(char command[100][100], int count)
{
    char **hi = malloc(sizeof(char *) * (1000));
    for (int i = 0; i < count; i++)
    {
        hi[i] = (char *)malloc(1000);
    }
    for (int i = 0; i < count; i++)
    {
        strcpy(hi[i], command[i]);
    }
    hi[count] = NULL;
    char *string = command[0];
    int status;
    pid_t process_id;
    process_id = fork();
    if (process_id == -1)
    {
        perror("Error");
        return;
    }
    else if (process_id == 0)
    {
        if (execvp(string, hi) < 0)
        {
            perror("Error");
        }
    }
    else if (process_id > 0)
    {
        waitpid(process_id, NULL, 0);
    }
}
void execute_backgroundprocess(char command[100][100], int count)
{
    int status;
    char **hi = malloc(sizeof(char *) * (1000));
    for (int i = 0; i < count; i++)
    {
        hi[i] = (char *)malloc(1000);
    }
    for (int i = 0; i < count; i++)
    {
        strcpy(hi[i], command[i]);
    }
    hi[count] = NULL;
    char *string = (char *)malloc(sizeof(char) * 100);
    strcpy(string, command[0]);
    pid_t process_id;
    process_id = fork();
    if (process_id == -1)
    {
        perror("Error");
    }
    if (process_id != 0)
    {
        printf("%d", process_id);
        child_pids[pidno] = process_id;
        statusofpids[pidno] = 1;
        pidno = pidno + 1;
    }
    if (process_id == 0)
    {
        if (execvp(string, hi) < 0)
        {
            perror("Error");
        }
    }
    else
    {
        waitpid(process_id, &status, WNOHANG);
    }
    return;
}
void execute_command(char command[100][100], int count)
{

    if (strcmp("cd", command[0]) == 0)
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
    else if (strcmp("cd\n", command[0]) == 0)
    {
        dir[0] = '\0';
    }
    else if (strcmp("echo", command[0]) == 0)
    {
        for (int i = 1; i < count; i++)
        {
            printf(" %s", command[i]);
        }
    }
    else if (strcmp("pwd\n", command[0]) == 0)
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
    else if (strcmp("ls\n", command[0]) == 0)
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
            printf("%s ", directory_ptr->d_name);
        }
        printf("\n");
        return;
    }
    else if (strcmp("ls", command[0]) == 0)
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
    else if (strcmp("pinfo\n", command[0]) == 0)
    {
        int process_id;
        process_id = getpid();
        printf("pid -- %d\n", process_id);
        char info[1000];
        sprintf(info, "/proc/%d/stat", process_id);
        FILE *info_file = fopen(info, "r");
        if (info_file == NULL)
        {
            perror("Error");
            return;
        }
        char *efile;
        efile = malloc(sizeof(char) * 100);
        char file_name[1000];
        char *information;
        information = malloc(sizeof(char) * 100);
        int c = 0;
        printf("%s", efile);
        while (fgets(efile, sizeof(efile), (FILE *)info_file) != NULL)
        {
            strcat(information, efile);
        }
        char *str;
        char string[1000][1000];
        while ((str = strtok_r(information, " ", &information)))
        {
            strcpy(string[c], str);
            c++;
        }
        if (getpgrp() == tcgetpgrp(STDOUT_FILENO))
        {
            printf("Process Status --%s+\n", string[2]);
        }
        else
        {
            printf("Process Status --%s\n", string[2]);
        }
        printf("memory --%s{Virtual Memory}\n", string[22]);
        char execution_path[1000], exe[1000];
        sprintf(execution_path, "/proc/%d/exe", process_id);
        readlink(execution_path, exe, sizeof(exe));
        printf("Executable Path --%s\n", exe);
    }
    else if (strcmp("pinfo", command[0]) == 0)
    {
        // pid_t process_id;
        char process_id[100];
        strcpy(process_id, command[1]);
        if (process_id[strlen(process_id) - 1] == '\n')
        {
            process_id[strlen(process_id) - 1] = '\0';
        }
        printf("pid -- %s\n", process_id);
        char info[1000];
        int pid = atoi(process_id);
        sprintf(info, "/proc/%d/stat", pid);
        FILE *info_file = fopen(info, "r");
        if (info_file == NULL)
        {
            perror("Error");
            return;
        }
        char *efile;
        efile = malloc(sizeof(char) * 100);
        char file_name[1000];
        char *information;
        information = malloc(sizeof(char) * 100);
        int c = 0;
        printf("%s", efile);
        while (fgets(efile, sizeof(efile), (FILE *)info_file) != NULL)
        {
            strcat(information, efile);
        }
        char *str;
        char string[100][100];
        while ((str = strtok_r(information, " ", &information)))
        {
            strcpy(string[c], str);
            c++;
        }
        if (strcmp(string[4], string[7]) == 0)
        {
            printf("Process Status --%s\n", string[2]);
        }
        printf("memory --%s{Virtual Memory}\n", string[22]);
        char execution_path[1000], exe[1000];
        sprintf(execution_path, "/proc/%s/exe", process_id);
        readlink(execution_path, exe, sizeof(exe));
        printf("Executable Path --%s\n", exe);
    }
    else if (strcmp(command[0], "sleep") == 0)
    {
        if (command[count - 1][strlen(command[count - 1]) - 1] == '\n')
        {
            command[count - 1][strlen(command[count - 1]) - 1] = '\0';
        }
        for (int i = 0; i < atoi(command[count - 1]); i++)
        {
            sleep(1);
        }
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
    else
    {
        if (count == 1)
        {
            command[0][strlen(command[0]) - 1] = '\0';
        }
        if (strcmp(command[count - 1], "&\n") == 0)
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
}
void break_input_command(char *input_command)
{
    char *command;
    char *duplicate_string = input_command;
    while ((command = strtok_r(duplicate_string, ";", &duplicate_string)))
    {
        char *duplicate_command = command;
        char *str;
        char command_including_flags[100][100];
        int count = 0;
        while ((str = strtok_r(duplicate_command, " ", &duplicate_command)))
        {
            strcpy(command_including_flags[count], str);
            count++;
        }
        execute_command(command_including_flags, count);
    }
}

int main()
{
    dir[0] = '\0';
    getcwd(directory_path, sizeof(directory_path));
    while (1)
    {
        strcpy(store_commands[iteration], dir);
        if (iteration > 0)
        {
            strcpy(store_previous, store_commands[iteration - 1]);
        }
        check_for_terminated_child_proccess();
        display_shell();
        check_for_terminated_child_proccess();
        char *input_command = NULL;
        ssize_t size = 0;
        if (getline(&input_command, &size, stdin) == -1)
        {
            printf("Not able to read the command, Please try again");
            main();
        }
        break_input_command(input_command);
        iteration++;
    }
}