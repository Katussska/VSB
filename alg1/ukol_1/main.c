#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    int capacity;
    int size;
} Array;

void array_init(Array *self);
void array_push(Array *self, int value);
int array_get(Array *self, int pos);
void array_free(Array *self);

void print_res(Array *v)
{
    int s = v->size;
    int i = 0;
    if (s >= 1)
        printf("%d", array_get(v, i));
    for (i = 1; i < s; i++)
    {
        printf(" %d", array_get(v, i));
    }
    printf("\n");
}

/*
Doplnte telo funkce tak, aby do v postupne pridala cisla z prvociselneho
rozkladu cisla n od nejmensiho po nejvetsi. Pridani jednoho cisla provedete
pomoci
array_push(v, <dalsi delitel>);
kde <dalsi delitel> nahradite vyrazem vyhodnocenym na dalsi cislo rozkladu.
(napr. array_push(v, y); pokud by to cislo z rozkladu bylo ulozeno v promenne y.)
*/
void factorization(int n, Array *v)
{
    for (int j = 2; j <= n; j++)
    {
        while (n % j == 0)
        {
            if (n % j == 0)
            {
                array_push(v, j);
                n = n / j;
            }
        }
    }
}

int main()
{
    int count;
    scanf("%d", &count);
    for (int i = 0; i < count; i++)
    {
        int x;
        scanf("%d", &x);
        Array result;
        array_init(&result);
        factorization(x, &result);
        print_res(&result);
        array_free(&result);
    }
    return 0;
}

#define INIT_CAPACITY 16

void array_init(Array *self)
{
    self->data = (int *)malloc(INIT_CAPACITY * sizeof(int));
    self->capacity = INIT_CAPACITY;
    self->size = 0;
}

void array_push(Array *self, int value)
{
    if (self->size == self->capacity)
    {
        self->capacity = self->capacity * 2;
        self->data = (int *)realloc(self->data, sizeof(int) * self->capacity);
    }

    self->data[self->size] = value;
    self->size += 1;
}

int array_get(Array *self, int pos)
{
    return self->data[pos];
}

void array_free(Array *self)
{
    free(self->data);
}
