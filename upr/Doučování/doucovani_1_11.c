#include <stdio.h>
#include <string.h>

int main()
{
    char buf[51] = {}; // vytvor mi na zasobniku pamet s promennou buf o mozne velikosti 51 znaku s nazvem buf
    fgets(buf, sizeof(buf), stdin);
    int delka = strlen(buf);
    buf[delka - 1] = '\0';

    char buf2[51] = {};
    fgets(buf2, sizeof(buf2), stdin);
    int delka2 = strlen(buf2);
    buf2[delka2 - 1] = '\0';

    int max = 0;
    if (delka >= delka2)
    {
        max = delka;
    }
    else
    {
        max = delka2;
    }

    for (int i = 0; i < max - 1; i++)
    {
        printf("%c", buf[i]);
        printf("%c", buf2[i]);
    }

    printf("\n");
    return 0;
}

// zobecnit zigzag aby fungoval pro ruzne dlouhe retezce (napr ahojjjjj, cau => achaoujjjjj)