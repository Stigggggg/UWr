package obliczenia;

public class Liczba extends Wyrazenie
{
    private double wartosc;
    public Liczba(double wartosc)
    {
        this.wartosc=wartosc;
    }
    @Override
    public double oblicz()
    {
        return wartosc;
    }
    @Override 
    public String toString()
    {
        return Double.toString(wartosc);
    }
    @Override
    public boolean equals(Object o)
    {
        if(o==this)
        {
            return true;
        }
        if(!(o instanceof Liczba))
        {
            return false;
        }
        Liczba l=(Liczba) o;
        return Double.compare(l.wartosc,wartosc)==0;
    }
}
