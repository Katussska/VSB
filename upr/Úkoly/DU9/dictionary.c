#include "dictionary.h"

void parametersCheck(int argc)
{
    if (argc != 4)
    {
        printf("Wrong parameters");
        exit(EXIT_FAILURE);
    }
}
void fileCheck(FILE *fileName)
{
    if (fileName == NULL)
    {
        printf("Could not load dictionary\n");
        exit(EXIT_FAILURE);
    }
}

int countWords(char *fileName)
{
    int count = 0;

    FILE *dictionary = fopen(fileName, "r");
    fileCheck(dictionary);

    char tmp[256];
    while (fgets(tmp, sizeof tmp, dictionary))
    {
        count++;
    }

    fclose(dictionary);
    return count;
}

Dictionary getWord(char *text)
{
    char *english = strtok(text, ",");
    char *czech = strtok(NULL, ",");
    czech[strcspn(czech, "\n")] = 0;
    Dictionary x;
    strcpy(x.en, english);
    strcpy(x.cs, czech);
    return x;
}

char deleteN(char *text)
{
    for (int j = 0; j < sizeof(text) + 1; j++)
    {
        if (text[j] == '\n')
        {
            text[j] = '\0';
        }
    }
    return *text;
}

/*int numberOfWords(char *text)
{
    int i, words = 0;
    for (i = 0; text[i]; i++)
    {
        if (s[i] == 32)
            words++;
    }
    if (i > 0)
        words++;

    return words;
}*/

void makeDictionary(Dictionary *array, FILE *fileName)
{
    int x = 0;
    while (true)
    {

        char tmp[256];
        if (fgets(tmp, sizeof(tmp), fileName))
        {
            array[x] = getWord(tmp);
            x++;
        }
        else
        {
            fileCheck(fileName);
            break;
        }
    }
}

void translate(FILE *fileName1, FILE *fileName2, int size, Dictionary *array)
{
    while (true)
    {
        char inputArray[256];
        if (fgets(inputArray, sizeof(inputArray), fileName1))
        {
            char *word;
            inputArray[strcspn(inputArray, "\n")] = 0;
            for (word = strtok(inputArray, " "); word != NULL; word = strtok(NULL, " "))
            {
                for (int i = 0; i < size; i++)
                {
                    if (!strcmp(word, array[i].en))
                    {
                        fprintf(fileName2, "%s ", array[i].cs);
                        break;
                    }
                    else if (i == size - 1)
                    {

                        fprintf(fileName2, "<unknown>");
                    }
                }
            }
            fprintf(fileName2, "\n");
        }
        else
        {
            break;
        }
    }
}