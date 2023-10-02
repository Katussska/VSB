#include <stdio.h>

void count_long_array(void);
void char_replace(void);
void do_mac(void);

void printBin(long n);

long g_long_array[5] = {1153, 76, 52, 44211, 582362};
long g_sum;

long g_num_of_bits = 0;

char g_char_array[99] = "asfhsdufgauifu7fhhvuhfighafoadf";
char g_to_replace;
char g_new;
int g_char_count;

long g_mac_address = 0x309c2323ab65;
int g_vendor_oui[5] = {4120, 3185699, 14448460, 3199042};
char g_vendor_name[5] = {'B', 'M', 'C', 'D', 'A'};
char g_vendor;

// volitelně
/*
  char g_vendor_oui [5][5] = {"BCM","MSI","Cisco","Dell","Asus"}
*/

int main(void)
{

    // 01

    /*
    count_long_array();
    printf("g_sum: %ld\n", g_sum);
    printf("g_sum (bin): ");
    printBin(g_sum);
    printf("num of 0s: %ld", g_num_of_bits);
    */

    // 02
    printf("before: %s\n", g_char_array);
    g_to_replace = 'a';
    g_new = 'x';
    char_replace();
    printf("after: %s\n", g_char_array);
    printf("num. of replaced chars: %d\n", g_char_count);

    // 03
    printf("mac addr: %lX\n", g_mac_address);
    do_mac();
    printf("vendor: %c\n", g_vendor);
    printf("mac addr: %lX\n", g_mac_address);

    return 0;
}

void printBin(long n)
{
    while (n)
    {
        if (n & 1)
            printf("1");
        else
            printf("0");

        n >>= 1;
    }
    printf("\n");
}