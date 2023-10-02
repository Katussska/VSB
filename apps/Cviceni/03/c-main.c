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
int my_strchr(char *str, char to_find, int *count);
void str2int(char *buff, int *num);
void my_strcpy(char *buff, char *string, int size);

// Variables
// type g_some_c_variable;
char string[] = "Ahoj svete! EeEe";
char to_find = 'e';
int count;
char buff[255] = "55";
int num = 0;
char string2[] = "Ahoj svete";
char buff2[255];
int size = 5;

int main()
{

    int first = my_strchr(string, to_find, &count);
    printf("Count je: %d\n", count);
    printf("First byl: %d.\n", first);
    str2int(buff, &num);
    printf("%s\n", buff);
    printf("%d\n", num);
    my_strcpy(buff2, string2, size);
    printf("%s\n", buff2);

    return 0;
}