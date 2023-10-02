#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char z;
    z = getchar();
    printf("Zadal jsi. %c\n", z);
    printf("ASCII hodnota je: %d\n", z);

    char t1[] = "Ahoj";
    char t2[] = {'A', 'h', 'o', 'j', '\0'};
    const char *t3 = "Ahoj";
    char *t4 = "Ahoj";

    printf("1: %s\n", t1);
    printf("2: %s\n", t2);
    printf("3: %s\n", t3);
    printf("4: %s\n", t4);

    printf("1: %c\n", t1[0]);
    printf("2: %c\n", t2[0]);
    printf("3: %c\n", t3[0]);
    printf("4: %c\n", t4[0]);

    char z;

    if (z >= 'a' && z <= 'z')
    {
        z - 'a' + 'A'; // z maleho znaku velky znak
    }

    int delka = strlen(retezec);
    for (int i = 0; i < delka; i++)
    {
        ...
    }

    int strTok()
    {
        char str[80] = "This is - www.tutorialspoint.com - website";
        const char s[2] = "-";
        char *token;

        /* get the first token */
        token = strtok(str, s);

        /* walk through other tokens */
        while (token != NULL)
        {
            printf(" %s\n", token);

            token = strtok(NULL, s);
        }

        return (0);
    }

    int main()
    {
        char str[] = {'a', 'b', 'c', '\0'};
        printf("%d\n", strlen(str)); // 3

        return 0;
    }

    return 0;
}