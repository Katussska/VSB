#include <stdio.h>
#include <string.h>

// Functions
// void some_asm_function();
int strcat2(char* str, char to_find, int* count);
int count = 0;
char string[] = "Ahoj svete! EeEe";
char to_find = 'e';

void str2int(char*, int*);
char buff[255] = "45999998";
int num = 0;

void my_strcpy(char* to, char* from, int howmuch);
char buff2[255];
int sizeofcopy = 5;

int main()
{
    int first = strcat2(string, to_find, &count);
    printf("Count je: %d\n", count);
    printf("První byl : %d\n", first);
    str2int(buff, &num);
    printf("Číslo je : %d\n", num);
    my_strcpy(buff2, string, sizeofcopy);
    printf("%s\n", buff2);
    return 0;
}
