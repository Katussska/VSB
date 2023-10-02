#include "dictionary.h"

int main(int argc, char **argv)
{
    parametersCheck(argc);
    char *dict = argv[1];
    char *input = argv[2];
    char *output = argv[3];

    int dictSize = countWords(dict);

    FILE *FDictionary = fopen(dict, "rt");
    fileCheck(FDictionary);

    Dictionary *dictArray = (Dictionary *)malloc(sizeof(Dictionary) * dictSize);

    makeDictionary(dictArray, FDictionary);

    fclose(FDictionary);

    FILE *FInput = fopen(input, "rt");
    if (FInput == NULL)
    {
        printf("Could not open input file\n");
        exit(EXIT_FAILURE);
    }
    FILE *FOutput = fopen(output, "wt");
    if (FOutput == NULL)
    {
        printf("Could not open output file\n");
        exit(EXIT_FAILURE);
    }

    translate(FInput, FOutput, dictSize, dictArray);

    fclose(FInput);
    fclose(FOutput);
    free(dictArray);
    return 0;
}