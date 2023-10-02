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

// Functions
// void some_asm_function();
void swap_endiannes();
void compose();
void replace();
void extend();

// Variables
// type g_some_c_variable;
uint8_t data[4] = {1, 2, 3, 4};
uint8_t data2[4] = {0xAF, 0xBE, 0xAD, 0xDE};
int result;
char data3[10] = "XXX0000";
int16_t key = -96;
int64_t extended;

int main()
{
    swap_endiannes();
    printf("Array %d, %d, %d, %d\n", data[0], data[1], data[2], data[3]);

    compose();
    printf("result %u \n", result);

    replace();
    printf("login %s \n", data3);

    extend();
    printf("extended %ld \n", extended);
}