#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/text_process.h"

int main()
{
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        text_process(buffer);
    }
    return 0;
}