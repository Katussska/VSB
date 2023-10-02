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

// Variables
// type g_some_c_variable;
int l_input_ints[] = {1,-2,3,-4,5,-6,7,-8,9,-10};
long l_tripled[10];
void triple_nums(int *input_array, long *output_array, int array_len);

void void_str2int(char *buff, int *num);

char * int2str ( unsigned long t_number , char * t_str );

long faktorialA(); // {if (n==0) return 1; return n * faktorial(n-1);}
long faktorialB(); // {if (n==0) return 1; return n * faktorial(n-1);}

int prvocislo();



int main()
{
    triple_nums(l_input_ints, l_tripled, 10);
    for(int i = 0; i < 10; i++) {
        printf("%ld ", l_tripled[i]);
    }
    printf("\n");

    int num;
    char buff[] = "8595255";
	void_str2int(buff,&num);
	printf("%d",num);
    printf("\n");

    unsigned long l_number = -6123;
    char str[4];
    int2str(l_number,str);
    printf("%s",str);
    printf("\n");

    printf("faktorialA (2): %ld\n", faktorialA(2));
    printf("faktorialA (4): %ld\n", faktorialA(4));
    printf("faktorialA (5): %ld\n", faktorialA(5));
    printf("faktorialA (8): %ld\n", faktorialA(8));
    printf("faktorialA (10):%ld\n\n", faktorialA(10));

    printf("faktorialB (2): %ld\n", faktorialB(2));
    printf("faktorialB (4): %ld\n", faktorialB(4));
    printf("faktorialB (5): %ld\n", faktorialB(5));
    printf("faktorialB (8): %ld\n", faktorialB(8));
    printf("faktorialB (10):%ld\n\n", faktorialB(10));

    //nefunguje spravne
    printf("je 7 prvocislo????????? %d\n", prvocislo(7));
    printf("je 22 prvocislo? %d\n", prvocislo(22));
    printf("je 29 prvocislo? %d\n", prvocislo(29));
    printf("je 44 prvocislo? %d\n", prvocislo(44));
    printf("je 71 prvocislo? %d\n\n", prvocislo(71));

    printf("int_str2int NEFUNGUJE (\"-55\"): %d\n", int_str2int("-55"));   // NEFUNGUJE???
    printf("int_str2int NEFUNGUJE (\"-88\"): %d\n", int_str2int("-88"));   // NEFUNGUJE???
    printf("int_str2int NEFUNGUJE (\"777\"): %d\n\n", int_str2int("777")); // NEFUNGUJE???
  
}
