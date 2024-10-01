#include "headers/count_consonants.h"

void count_consonants(char *str)
{
    int i, count = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] != 'a' && str[i] != 'e' && str[i] != 'i' && str[i] != 'o' && str[i] != 'u' &&
             str[i] != 'A' && str[i] != 'E' && str[i] != 'I' && str[i] != 'O' && str[i] != 'U') &&
            ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)))
        {
            count++;
        }
    }
    printf("Number of consonants in the string: %d\n", count);
}