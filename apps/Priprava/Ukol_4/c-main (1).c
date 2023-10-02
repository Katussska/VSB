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

// Variables
// type g_some_c_variable;
long faktorial();

int pole_cisel[] = {1,2,3,4,5,6,7,8,9};

void nulovani_cisel();

int prvocislo();

int main()
{

    printf("faktorial: %ld\n", faktorial(5));

    nulovani_cisel(pole_cisel, 9, 3);

    for(int i = 0; i < 9; i++)
    {
        printf("%d", pole_cisel[i]);
    }
    printf("\n");

    printf("%d\n", prvocislo(22));


    return 0;

}
