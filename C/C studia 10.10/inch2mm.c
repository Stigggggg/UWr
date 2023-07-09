#include <stdio.h>
#include <stdlib.h>

int main()
{
    double inch;
    printf("Podaj liczbe cali: ");
    scanf("%lf",&inch);
    inch*=25.4;
    printf("Liczba milimetrow: %.3lf",inch);
    return 0;
}

//Notatki:
//%d - int
//%c - char
//%s - string
//%lf - double
//%f - float
//%5d - 5 miejsc, przesuniecie w prawo
//%-5d - 5 miejsc, przesuniecie w lewo
//%.3lf - precyzja double - 3 miejsca po przecinku
