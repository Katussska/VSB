#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// v pameti slovnik (abcda)
// pouzit nacitani radku, dokud se to nepovede (scripta 3,12,2,2), pouzit while loop s if else ze sript, nacitani nevime kolik radku
// slovnik nacist do pameti a prochazet pole dvojic
// vyuziti dynamickeho pole jedna moznost
// druha moznost projit soubor, spocitat radky, zavrit, vytvorit pole na ten pocet a znovu pracovat se souborem

/*typedef struct {
    char cs[256];
    char en[256];
} Slovo;*/

int main(int argc, char **argv)
{
    int capacity = 5; // jak je pole velke
    int count = 0;    // kolik je prvku v poli
    int *array = malloc(sizeof(int) * capacity);

    for (int i = 0; i < 1000; i++) // tvorba dynamickeho pole (21-38)
    {
        if (count == capacity)
        {
            capacity == capacity * 2;
            // int *array2 = malloc(sizeof(int) * capacity);
            /*for (int j = 0; j < count; j++)
             {
                 array2[j] = array[j];
             }*/
            /*memcpy(array2, array, sizeof(int) * count); // nahrazuje for loop kopirovani (27-30)
            free(array);
            array = array2;*/
            array = realloc(array, sizeof(int) * capacity); // nahrazuje radky 26-33
        }
        array[count] = i;
        count = count + 1; // count +=1;
    }

    free(array);
    return 0;
}

// zkrácené řešení o useless veci

int main(int argc, char **argv)
{
    int capacity = 5;
    int count = 0;
    int *array = malloc(sizeof(int) * capacity);

    for (int i = 0; i < 1000; i++) // dynamicke pole
    {
        if (count == capacity)
        {
            capacity == capacity * 2;
            array = realloc(array, sizeof(int) * capacity);
        }
        array[count] = i;
        count = count + 1; // count++;
    }

    free(array);
    return 0;
}
