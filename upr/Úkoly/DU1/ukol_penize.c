#include <stdio.h>

int main()
{

    printf("Kolik chcete rozměnit?\n");
    int vklad = 0;
    scanf("%d", &vklad);

    if (vklad < 100)
    {
        printf("Částká je moc malá.\nČástka musí být alespoň 100.\n");
        return main();
    }
    printf("Pětitisícovek: %d\n", vklad / 5000);
    vklad = vklad % 5000;
    printf("Dvoutisícovek: %d\n", vklad / 2000);
    vklad = vklad % 2000;
    printf("Tisícovek: %d\n", vklad / 1000);
    vklad = vklad % 1000;
    printf("Pětistovek: %d\n", vklad / 500);
    vklad = vklad % 500;
    printf("Dvoustovek: %d\n", vklad / 200);
    vklad = vklad % 200;
    printf("Stovek: %d\n", vklad / 100);
    vklad = vklad % 100;
    int vydavek = vklad;
    printf("Váš výdavek je: %d.\n", vydavek);

    return 0;
}