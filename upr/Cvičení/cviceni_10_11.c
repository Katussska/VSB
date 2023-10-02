// html prikazy resit pres retezce (3, podle rozdeleni
// z retezce cisel udelat int a vypocitat rozdil
// musi se nacitat do pameti a pote vypsat naopak, musi se pouzit malloc
// VLA je ZAKAZANO (int a[n]) hrozí 0 bodu
// nemelo by byt vsechno v mainu!!! vyuzivat funkce
// vyuziti atof na prevod ??stringu na cisla??

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*int main(int argc, char **argv) // argc- argument counts, argv- argument values
{

    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    // int n = atoi(argv[2])

    return 0;
}*/

/*int main(int argc, char **argv)
{
    float x = 5.55;
    float y = 1 / 3;        // vypise se 0.00, prekladac vidi cele cislo, a proto udela 1:3 = 0, jak toto opravit?
    float z = (float)1 / 3; // uz vi, ze jedno cislo neni cele a proto neprovede celociselne deleni
    float a = 1.0 / 3;      // dalsi moznosti reseni
    float b = 1 / 3.0;
    printf("%.2f\n%f\n%f\n%.4f\n%.2f\n\n", x, y, z, a, b); //%f je jak pro float, tak pro double, vždy vypisuje na 6 desetinných mist, takze musime urcit pocet des mist

    // x = 1. / 0; // vypise 'inf' = infinity, take se muzeme setkat s '-inf' nebo 'nan' = not a number
    // printf("%f\n", x);

    x = 0;
    scanf("%f", &x);
    printf("%.2f\n", x);

    return 0;
}*/

typedef struct
{
    char jmeno[15];
    char prijmeni[15];
    int rok_narozeni;
    float vsp;
} Student;

void student_vypis(Student s)
{
    printf("%s %s se narodil v roce %d a má prumer %.2f\n",
           s.jmeno, s.prijmeni, s.rok_narozeni, s.vsp);
}

Student student_nacti()
{
    char buffer[50];
    fgets(buffer, 50, stdin);
    char *jmeno = strtok(buffer, "/*podle ceho rozdeli*/");
    char *prijmeni = strtok(NULL, ",");
    int rok = atoi(strtok(NULL, ","));
    float vsp = atof(strtok(NULL, "\n"));
    Student s; // = {.jmeno = strdup(strtok(NULL, ","))} strcpy(s.jmeno, jmeno)
    strcpy(s.prijmeni, prijmeni);
    s.rok_narozeni = rok;
    s.vsp = vsp;
    return s;
}

int main()
{
    Student s = student_nacti();
    Student p = s;
    s.rok_narozeni = 1999;
    // s.jmeno = "Pavel"; // nefunguje, pouze pri inicializaci. jakmil je pamet vytvorena, nejde prepsat
    strcpy(s.jmeno, "Honza"); // mozne reseni problemu o radek vys
    s.jmeno[0] = 'X';
    s.jmeno[2] = 'X'; // takto vsak take muzeme menit jmeno, ale pouze po znacich

    student_vypis(s);
    student_vypis(p);
    return 0;
}