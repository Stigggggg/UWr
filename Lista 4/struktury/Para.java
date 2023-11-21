package struktury;

public class Para implements Cloneable, Comparable<Para>
{
    public final String klucz;
    private double wartosc;
    public Para(String klucz, double wartosc)
    {
        for(int i=0; i<klucz.length(); i++)
        {
            if(klucz.charAt(i)<'a' || klucz.charAt(i)>'z')
            {
                throw new IllegalArgumentException("Niepoprawny klucz");
            }
        }
        this.klucz=klucz;
        this.wartosc=wartosc;
    }
    public double get_wartosc()
    {
        return this.wartosc;
    }
    public void set_wartosc(double w)
    {
        this.wartosc=w;
    }
    @Override
    public String toString()
    {
        return "("+klucz+", "+wartosc+")";
    }
    @Override
    public boolean equals(Object o)
    {
        if(o==this)
        {
            return true;
        }
        if(!(o instanceof Para))
        {
            return false;
        }
        Para p=(Para) o;
        return klucz.equals(p.klucz);
    }
    @Override
    public Para clone() throws CloneNotSupportedException
    {
        return (Para) super.clone();
    }
    @Override
    public int compareTo(Para p)
    {
        return klucz.compareTo(p.klucz);
    }
}