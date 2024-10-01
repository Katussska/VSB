#include "headers/to_uppercase.h"

void to_uppercase(char *str)
{
    size_t i;
    for (i = 0; i < strlen(str); i++)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
}