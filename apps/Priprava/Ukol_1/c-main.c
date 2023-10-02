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
void decode();
void extend_and_merge();
void swap_endiannes();
void replace();
void compose();
void extend();
// Variables

int enc_string = 0x50415053;
char slovo[4];
char testik = 0;
long spojene;

long spojene2 = 0;
uint8_t data[4] = {13, 2, 79, 4};
int result;

char data2[10] = "XXX0000";

int16_t key = -96;
int64_t extended;

int main()
{
    decode();
    extend_and_merge();
    printf("%c %c\n", slovo[0], slovo[3]);
    printf("%ld\n", spojene);
}
