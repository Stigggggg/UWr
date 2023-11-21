package obliczenia;

public class Stala extends Wyrazenie
{
    private final String nazwa;
    private final double wartosc;
    public Stala(String nazwa, double wartosc)
    {
        this.nazwa=nazwa;
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
        return nazwa;
    }
    public boolean equals(Object o)
    {
        if(o==this)
        {
            return true;
        }
        if(!(o instanceof Stala))
        {
            return false;
        }
        Stala s=(Stala) o;
        return nazwa.equals(s.nazwa);
    }
}
