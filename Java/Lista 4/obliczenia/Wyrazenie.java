package obliczenia;

public abstract class Wyrazenie implements Obliczalny
{
    public static double suma(Wyrazenie... wyr)
    {
        double wynik=0;
        for(int i=0; i<wyr.length; i++)
        {
            wynik+=wyr[i].oblicz();
        }
        return wynik;
    }
    public static double iloczyn(Wyrazenie... wyr)
    {
        double wynik=1;
        for(int i=0; i<wyr.length; i++)
        {
            wynik*=wyr[i].oblicz();
        }
        return wynik;
    }
}
