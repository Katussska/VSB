#include "headers/count_words.h"

void count_words(char *str)
{
    int count = 0;
    int i = 0;
    int is_word = 0;

    while (str[i] != '\0')
    {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
            is_word = 0;
        else if (is_word == 0)
        {
            is_word = 1;
            count++;
        }
        i++;
    }

    printf("Number of words: %d\n", count);
}