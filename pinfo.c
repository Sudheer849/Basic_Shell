#include "shell_extend.h"

void pinfo(char command[100][100],int count)
{
        int process_id;
        process_id = getpid();
        printf("pid -- %d\n", process_id);
        char info[1000];
        sprintf(info, "/proc/%d/stat", process_id);
        FILE *info_file = fopen(info, "r");
        if (info_file == NULL)
        {
            printf("Process with this pid doesn't exists\n");
            return;
        }
        char *efile;
        efile = malloc(sizeof(char) * 100);
        char file_name[1000];
        char *information;
        information = malloc(sizeof(char) * 100);
        int c = 0;
       // printf("%s", efile);
        while (fgets(efile, sizeof(efile), (FILE *)info_file) != NULL)
        {
            strcat(information, efile);
        }
        char *str;
        char string[1000][1000];
        while ((str = strtok_r(information, " ", &information)))
        {
            strcpy(string[c], str);
           // printf("%s\n",string[c]);
            c++;
        }
        if (!strcmp(string[4],string[7]))
        {
            printf("Process Status --{%s+}\n", string[2]);
        }
        else
        {
            printf("Process Status --{%s}\n", string[2]);
        }
        printf("memory --%s{Virtual Memory}\n", string[22]);
        char execution_path[1000], exe[1000];
        sprintf(execution_path, "/proc/%d/exe", process_id);
        readlink(execution_path, exe, sizeof(exe));
        printf("Executable Path --%s\n", exe);
}

void pinfo2(char command[100][100],int count)
{
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
            printf("Process with this pid doesn't exists\n");
            return;
        }
        char *efile;
        efile = malloc(sizeof(char) * 100);
        char file_name[1000];
        char *information;
        information = malloc(sizeof(char) * 100);
        int c = 0;
        //printf("%s", efile);
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
        if (!strcmp(string[4],string[7]))
        {
            printf("Process Status --{%s+}\n", string[2]);
        }
        else
        {
            printf("Process Status --{%s}\n", string[2]);
        }
        printf("memory --%s{Virtual Memory}\n", string[22]);
        char execution_path[1000], exe[1000];
        sprintf(execution_path, "/proc/%s/exe", process_id);
        readlink(execution_path, exe, sizeof(exe));
        printf("Executable Path --%s\n", exe);
    
}