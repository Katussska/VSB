#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/encrypt.h"

int main()
{
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        encrypt(buffer);
        printf("%s\n", buffer);
    }
    return 0;
}