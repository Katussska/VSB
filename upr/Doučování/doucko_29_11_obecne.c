#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int capacity = 5;
    int count = 0;
    void **array = malloc(sizeof(void *) * capacity); // nemuzeme napsat void *array[]!!!

    for (int i = 0; i < 1000; i++) // dynamicke pole
    {
        if (count == capacity)
        {
            capacity == capacity * 2;
            array = realloc(array, sizeof(void *) * capacity);
        }
        int *p = malloc(sizeof(int));
        *p = i; // p[0] = i == *(p + 0)
        array[count] = p;
        count = count + 1; // count +=1;
    }

    for (int i = 0; i < count; i++)
    {
        int *ptr = /*(int *)*/ array[i]; // void * ptr = array[i];
        int x = *ptr;
        printf("%d\n", x);
    }

    for (int i = 0; i < count; i++)
    {
        free(array[i]);
    }

    free(array);
    return 0;
}