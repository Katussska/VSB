#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/string_manipulate.h"

int main()
{
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        string_manipulate(buffer);
        printf("%s\n", buffer);
    }
    return 0;
}