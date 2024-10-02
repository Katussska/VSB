#include "headers/xor_encrypt.h"

void xor_encrypt(char *str)
{
    size_t i;
    for (i = 0; i < strlen(str); i++)
        str[i] ^= 0x1;
}