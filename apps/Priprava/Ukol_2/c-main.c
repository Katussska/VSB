#include <stdio.h>

void count_even(void);
void move_negative(void);
void printIntArray(int *arr, int arr_size, char *array_name);
void count_vowels(void);
void replace_vowels(void);
void count_ones(void);
void the_lowest(void);

int g_int_array[15] = {-3, -8, 80, 2710, 32, 439, 9099, 10, 77, -273, 2, 22222, 0, -23, 23};
int g_int_array2[15] = {-3, -8, 80, 2710, 32, 439, 9099, 10, 77, -273, 2, 22222, 0, -23, 23};
int g_int_array_lenght = 15;
int g_int_output;
char g_char_array[32] = "testovaci pole pro cv2";
int g_neg_val_array[15];
int g_int_data = 0b101010101010101010;
int g_int_count = 0;

int main(void)
{
    printIntArray(g_int_array, g_int_array_lenght, "g_int_array");
    count_even();
    printf("pocet sudych: %d\n", g_int_output);
    move_negative();
    printIntArray(g_neg_val_array, 15, "g_neg_val_array");
    printf("g_char_array: %s\n", g_char_array);
    count_vowels();
    printf("pocet samohlasek: %d\n", g_int_output);
    printf("vyjebat kazdou treti\n");
    replace_vowels();
    printf("g_char_array: %s\n", g_char_array);
    count_ones();
    printf("Number of ones: %d\n", g_int_count);
    the_lowest();
    printIntArray(g_int_array2, g_int_array_lenght, "NEW g_int_array");

    return 0;
}

void printIntArray(int *arr, int arr_size, char *array_name)
{
    printf("%s: {", array_name);
    for (int i = 0; i < arr_size; i++)
    {
        printf(" %d,", arr[i]);
    }
    printf(" }\n");
}
