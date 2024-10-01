#include "headers/reverse_string.h"

void reverse_string(char *str)
{
    char temp;
    int i, j;
    for (i = 0, j = strlen(str) - 1; i < j; i++, j--)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}
