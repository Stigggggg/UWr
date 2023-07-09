#include <stdio.h>

/* Wartości jakiej funkcji oblicza poniższy program?
 *      Autor: Marek Piotrów, Data: 1.10.2019
 */

int main(void)
{
    int n = 0;
    float x = 0.0, dx, eps;
    float y1, y2;
    printf("Podaj przyrost argumentu i dokladnosc obliczen:\n");
    scanf("%f %f", &dx, &eps);
    while (n <= 0 || x <= 0.0) {
        printf(u8"Podaj dwie liczby dodatnie: naturalna i rzeczywista:\n");
        scanf("%d %f", &n, &x);
        printf("%11c  %20s\n",'x',"f(x)");
    }
    for (int i = 0; i < n; i++) {
        y1 = x;
        y2 = y1 / 2;
        while (y1 - y2 > eps || y2 - y1 > eps) {
            y1 = y2;
            y2 = (y1 + x / y1) / 2;
        }
        printf("%11.8f  %20.8f\n", x, y2);
        x += dx;
    }
    return 0;
}
//zad 1: funkcja zwraca wartosc pierwiastka kwadratowego z czesci calkowitej z x, wartosc wzrasta o dx, wzrost nastepuje n-1 razy
//zad 2: dokladnosc zwracanych wartosci zmienila sie

