#include "headers/to_lowercase.h"

void to_lowercase(char *str)
{
    size_t i;
    for (i = 0; i < strlen(str); i++)
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
}