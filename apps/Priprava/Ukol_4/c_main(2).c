//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>

// Functions
void fill_pyramid_numbers(long * numbers, int size);
int factorial(int * numbers, int size);
long multiples(long * numbers, int size, long factor);
void change_array_by_avg(long* array, int N);

// Variables


int main(void)
{
    system("clear");
    printf("\n");

    // 1
    printf(" 1. Čtvercová pyramidová čísla\n\n ");

    int size = 10;
    long array[10];

    fill_pyramid_numbers(array, size);
    
    for (int i = 0; i < size; i++)
    {
        printf("%ld ", array[i]);
    }
    printf("\n\n\n");

    // 2
    printf(" 2. Násobky - long\n\n");

    long factor = 5;
    int factor_size = 8;
    long numbers[8] = {3, 8, 0, 5, 7, 9, 500, 96};

    printf(" array before:\t");
    for (int i = 0; i < factor_size; i++)
    {
        printf("%ld\t", numbers[i]);
    }
    printf("\n");
    long multi_num = multiples(numbers, factor_size, factor);

    printf(" array after:\t");
    for (int i = 0; i < factor_size; i++)
    {
        printf("%ld\t", numbers[i]);
    }
    printf("\n number of multiples: %ld\n", multi_num);
    printf("\n\n");

    // 3
    printf(" 3. Faktoriály - 32 bit\n\n");

    int size2 = 11;
    int fac_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30};
    int over_count;

    printf(" array before:\t");
    for (int i = 0; i < size2; i++)
    {
        printf("%d\t", fac_arr[i]);
    }
    printf("\n");
    over_count = factorial(fac_arr, size2);

    printf(" array after:\t");
    for (int i = 0; i < size2; i++)
    {
        printf("%d\t", fac_arr[i]);
    }
    printf("\n overflow count: %d\n", over_count);
    printf("\n\n");

    // 4
    printf(" 4. Průměry 64 bit\n\n");

    int arr_len = 9;
    long arr[9] = {7,5,9,3,2,8,4,1,6};

    printf(" array before:\t");
    for (int i = 0; i < arr_len; i++)
    {
        printf("%ld\t", arr[i]);
    }
    printf("\n");
    change_array_by_avg(arr, arr_len);

    printf(" array after:\t");
    for (int i = 0; i < arr_len; i++)
    {
        printf("%ld\t", arr[i]);
    }
    printf("\n\n");

    return 0;
}