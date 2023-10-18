//1 kropka
var a={};
//tu odwolujemy sie do skladowej obiektu, konkretnie do pola, nastepnie ja wypisujemy
a.foo=1;
console.log(a.foo);
//tu odwolujemy sie do pola za pomoca operatora [] poprzez forme literalna, nazwa pola to argument
a["foo"]=2;
console.log(a.foo);
//generalnie te 2 odwolania sa rownowazne

//2 kropka
var b={
    name: "Mikołaj",
    age: 20
};
b[4]=5;
console.log(b[1]);
console.log(b);
//na poczatek obiektu zostanie dodane nowe pole o kluczu bedacym liczba i wartosci przypisanej
b[a]=0;
console.log(b[a]);
console.log(b);
//na koniec obiektu zostanie dodane nowe pole o kluczu bedacym obiektem i wartoscia przypisana

//3 kropka
var tab=[1,2,3];
console.log(tab["1"]);
//nastepuje konwersja "1" na 1, dziala jak normalny indeks
tab["x"]=10;
console.log(tab["x"]);
//tworzy sie obiekt x z przypisana wyzej wartoscia 10
console.log(tab);
//w liczbie elementow tablicy nie jest on uwzgledniany
tab[a]=50;
console.log(tab[a]);
console.log(tab);
//tworzy nam sie nowy element o kluczu typu [object Object] i przypisanej wartosci 50
//zawartosc tablicy zmienia sie, na jej koncu laduje element z kluczem i wartoscia, do ktorego mozna sie odwolywac poprzez klucz
console.log(tab.length);
tab.length=4;
console.log(tab);
//przy ustawieniu wartosci wiekszej, zostanie dodany element "...", bedacy pustym miejscem tablicy
tab.length=2;
console.log(tab);
//przy ustawieniu wartosci mniejszej, elementy o indeksach wiekszych niz length znikna