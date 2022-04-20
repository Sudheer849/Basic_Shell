#include "shell_extend.h"

void echo(char command[100][100], int count)
{
    for (int i = 1; i < count; i++)
    {
        printf("%s ", command[i]);
    }
    printf("\n");
}