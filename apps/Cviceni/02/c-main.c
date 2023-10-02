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
// void some_asm_function();
void is_palidrom();
void fibb();
void the_lowest();

// Variables
// type g_some_c_variable;
char g_char_array[20] = "kajak";
int g_int_result_num = 0;
int g_int_iterations = 6;
int g_int_array[15] = {-3, -8, 80, 2710, 32, 439, 9099, 10, 77, -273, 2, 22222, 0, -23, 23};
int g_int_array_lenght = 15;
int g_int_lowest = 0;

int main()
{
    is_palidrom();
    printf("%s\n", g_char_array);
    fibb();
    printf("7th fibbonaci: %d\n", g_int_result_num);
    the_lowest();
    printf("%d\n", g_int_lowest);
    for (int i = 0; i < g_int_array_lenght; i++)
    {
        printf("%d ", g_int_array[i]);
    }
    printf("\n");

    return 0;
}