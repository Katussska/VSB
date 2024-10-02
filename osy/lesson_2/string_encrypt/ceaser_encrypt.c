#include "headers/ceaser_encrypt.h"

void ceaser_encrypt(char *str)
{
    size_t i;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = 'a' + (str[i] - 'a' + 1) % 26;
        else if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = 'A' + (str[i] - 'A' + 1) % 26;
    }
}