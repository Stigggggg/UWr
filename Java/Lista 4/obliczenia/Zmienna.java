package obliczenia;

import struktury.*;

public class Zmienna extends Wyrazenie
{
    public static final ZbiorTablicowy zbior_t=new ZbiorTablicowy(10);
    private final String klucz;
    public Zmienna(String klucz)
    {
        this.klucz=klucz;
    }
    public static void dodaj_zmienna(String klucz, double wartosc)
    {
        Para z=new Para(klucz,wartosc);
        zbior_t.wstaw(z);
    }
    @Override
    public double oblicz()
    {
        Para z=zbior_t.szukaj(klucz);
        if(z!=null)
        {
            return z.get_wartosc();
        }
        else
        {
            throw new IllegalArgumentException("Nie ma zmiennej o podanym kluczu");
        }
    }
    @Override 
    public String toString()
    {
        return klucz;
    }
    @Override
    public boolean equals(Object o)
    {
        if(o==this)
        {
            return true;
        }
        if(!(o instanceof Zmienna))
        {
            return false;
        }
        Zmienna z=(Zmienna) o;
        return klucz.equals(z.klucz);
    }
}
