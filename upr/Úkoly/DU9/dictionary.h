#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef struct
{
    char cs[256];
    char en[256];
} Dictionary;

void parametersCheck(int argc);
int countWords(char *fileName);
Dictionary getWord(char *text);
char deleteN(char *text);
void fileCheck(FILE *fileName);
// int numberOfWords(char *text);
void makeDictionary(Dictionary *array, FILE *fileName);
void translate(FILE *fileName1, FILE *fileName2, int size, Dictionary *array);