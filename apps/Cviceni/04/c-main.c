//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>
#include <stdint.h>

void fill_pyramid_numbers(long *numbers, int size);
long multiples(long *numbers, long size, long factor);
void change_array_by_avg(long *array, long size);

int size = 10;
long array[10];
long factor = 5;
int size2 = 8;
long numbers[8] = {153, 8, 0, 5, 1, 9, 500, 96};
int size3 = 9;
long array2[9] = {7, 5, 9, 3, 2, 8, 4, 1, 6};

int main()
{
    // UKOL_1
    printf("Array = { ");
    fill_pyramid_numbers(array, size);
    for (int i = 0; i < size; i++)
    {
        printf("%ld ", array[i]);
    }
    printf("}\n");

    // UKOL_2
    printf("Original array: ");
    for (int j = 0; j < size2; j++)
        printf("%ld ", numbers[j]);

    printf("\n");

    long multiple = multiples(numbers, size2, factor);
    printf("New array: ");
    for (int k = 0; k < size2; k++)
        printf("%ld ", numbers[k]);

    printf("\nNumber of multiples: %ld", multiple);

    printf("\n");

    // UKOL_4
    printf("Original array: ");
    for (int i = 0; i < size3; i++)
        printf("%ld ", array2[i]);
    printf("\n");
    change_array_by_avg(array2, size3);
    printf("New array: ");
    for (int i = 0; i < size3; i++)
        printf("%ld ", array2[i]);

    printf("\n");

    return 0;
}
