#include "shell_extend.h"

void jobs(char command[100][100], int num)
{
    typedef struct
    {
        int job_no;
        char job_name[100];
        char process_status[100];
        int job_pid;
    } jobs_info;
    jobs_info jobs[100];
    int count = 0;
    for (int i = 0; i < pidno; i++)
    {
        if (statusofpids[i] == 1)
        {
            //  printf("[%d] ", i + 1);
            char info[1000];
            sprintf(info, "/proc/%d/stat", child_pids[i]);
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
                // printf("%s\n",string[c]);
                c++;
            }
            char status[100];
            if (!strcmp(string[2], "S") || !strcmp(string[2], "D") || !strcmp(string[2], "R"))
            {
                strcpy(status, "Running");
            }
            else
            {
                strcpy(status, "Stopped");
            }
            char name[100];
            strcpy(name, name_of_bgprocess[i]);
            // printf("%s %s [%d]\n", status, name, child_pids[i]);
            jobs[count].job_no = i + 1;
            strcpy(jobs[count].job_name, name_of_bgprocess[i]);
            strcpy(jobs[count].process_status, status);
            jobs[count].job_pid = child_pids[i];
            count++;
            //  qsort(jobs, 1000, sizeof(struct jobs_info), comperator_function);
        }
    }
    for (int i = 1; i < count; i++)
    {
        for (int j = 0; j < count - i; j++)
        {
            if (strcmp(jobs[j].job_name, jobs[j + 1].job_name) > 0)
            {
                jobs_info temp;
                temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }
    if (num == 1)
    {
        for (int i = 0; i < count; i++)
        {
            printf("[%d] %s %s [%d]\n", jobs[i].job_no, jobs[i].process_status, jobs[i].job_name, jobs[i].job_pid);
        }
    }
    else
    {
        if (strcmp(command[1], "-r\n") == 0 || strcmp(command[1], "-r") == 0)
        {
            for (int i = 0; i < count; i++)
            {
                if(strcmp(jobs[i].process_status,"Running")==0){
                printf("[%d] %s %s [%d]\n", jobs[i].job_no, jobs[i].process_status, jobs[i].job_name, jobs[i].job_pid);
                }
            }
        }
        else if (strcmp(command[1], "-s") == 0 || strcmp(command[1], "-s\n") == 0)
        {
            for (int i = 0; i < count; i++)
            {
                if(strcmp(jobs[i].process_status,"Stopped")==0){
                printf("[%d] %s %s [%d]\n", jobs[i].job_no, jobs[i].process_status, jobs[i].job_name, jobs[i].job_pid);
                }
            }
        }
    }
}