#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void setZero(char *str, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
        }
    }
}

int strCheckPodminka(char *strInput, char *strPodminka)
{
    int j = strlen(strPodminka) - 1;
    for (int i = strlen(strInput) - 1; strPodminka[j] != strPodminka[0]; i--)
    {
        if (strInput[i] != strPodminka[j])
        {
            return 0;
        }
        j--;
    }

    return 1;
}

int malypismena(char *input) // pojistka
{
    for (int i = 0; input[i + 1] != '\0'; i++)
    {
        if (input[i] < 'a' || input[i] > 'z')
        {
            return 0;
        }
    }
    return 1;
}

void checkWord(char *strInput, char *strPodminka, char *output)
{
    if (strCheckPodminka(strInput, strPodminka) && malypismena(strInput))
    {
        if (strlen(strInput) > strlen(output))
        {
            strcpy(output, strInput);
        }
    }
}

int main()
{
    char podminka[22];
    memset(podminka, '\0', 22);

    if (fgets(podminka, sizeof(podminka), stdin) == NULL)
        exit(EXIT_FAILURE);

    podminka[12] = '\0';

    if (strcmp(podminka, "longest-ends")) // pojistka
        exit(EXIT_FAILURE);

    setZero((podminka + 13), 5);

    char set[12];
    fgets(set, sizeof(set), stdin);

    int n = atoi(set);
    char slovo[51];
    char output[51];
    memset(output, '\0', 51);

    for (int i = 0; i < n; i++)
    {
        fgets(slovo, sizeof(slovo), stdin);
        setZero(slovo, sizeof(slovo));
        checkWord(slovo, (podminka + 13), output);
    }

    printf("%s", output);

    return 0;
}