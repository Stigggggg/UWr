package obliczenia;

import java.text.DecimalFormat;

public class Wymierna implements Comparable<Wymierna>
{
    private int licznik,mianownik;
    public Wymierna(int l, int m)
    {
        if(m==0)
        {
            throw new IllegalArgumentException("Dzielenie przez 0!");
        }
        int gcd=nwd(Math.abs(l),Math.abs(m));
        this.licznik=l/gcd;
        this.mianownik=m/gcd;
        if(this.mianownik<0)
        {
            this.mianownik*=-1;
            this.licznik*=-1;
        }
    }
    public Wymierna()
    {
        this(0,1);
    }
    public Wymierna(int n)
    {
        this(n,1);
    }
    private int nwd(int a, int b)
    {
        if(b==0)
        {
            return a;
        }
        else return nwd(b,a%b);
    }
    public int get_licznik()
    {
        return this.licznik;
    }
    public int get_mianownik()
    {
        return this.mianownik;
    }
    @Override
    public String toString()
    {
        if(mianownik==1)
        {
            return Integer.toString(licznik);
        }
        return licznik+"/"+mianownik;
    }
    @Override
    public boolean equals(Object o)
    {
        if(o==this)
        {
            return true;
        }
        if(!(o instanceof Wymierna))
        {
            return false;
        }
        Wymierna w=(Wymierna) o;
        return licznik==w.licznik && mianownik==w.mianownik;
    }
    @Override
    public int compareTo(Wymierna w)
    {
        double val1=(double) this.licznik/this.mianownik;
        double val2=(double) w.licznik/w.mianownik;
        return Double.compare(val1,val2);
    }
    public static Wymierna dodaj(Wymierna w1, Wymierna w2)
    {
        int l=w1.licznik*w2.mianownik+w2.licznik*w1.mianownik;
        int m=w1.mianownik*w2.mianownik;
        return new Wymierna(l,m);
    }
    public static Wymierna odejmij(Wymierna w1, Wymierna w2)
    {
        int l=w1.licznik*w2.mianownik-w2.licznik*w1.mianownik;
        int m=w1.mianownik*w2.mianownik;
        return new Wymierna(l,m);
    }
    public static Wymierna mnoz(Wymierna w1, Wymierna w2)
    {
        int l=w1.licznik*w2.licznik;
        int m=w1.mianownik*w2.mianownik;
        return new Wymierna(l,m);
    }
    public static Wymierna dziel(Wymierna w1, Wymierna w2)
    {
        if(w2.licznik==0)
        {
            throw new IllegalArgumentException("Dzielenie przez 0!");
        }
        int l=w1.licznik*w2.mianownik;
        int m=w1.mianownik*w2.licznik;
        return new Wymierna(l,m);
    }
    public String toFloat() {
        double result = (double) this.licznik / this.mianownik;
        DecimalFormat decimalFormat = new DecimalFormat("#.####");
        return decimalFormat.format(result);
    }
}

