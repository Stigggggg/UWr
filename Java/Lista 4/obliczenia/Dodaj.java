package obliczenia;

public class Dodaj extends Oper2 
{
    public Dodaj(Wyrazenie arg1, Wyrazenie arg2)
    {
        super(arg1,arg2);
    }
    @Override
    public double oblicz()
    {
        return arg.oblicz()+arg2.oblicz();
    }
    @Override
    public String toString()
    {
        return "("+arg+"+"+arg2+")";
    }
    @Override 
    public boolean equals(Object o)
    {
        if(this==o)
        {
            return true;
        }
        if(!(o instanceof Log))
        {
            return false;
        }
        Dodaj d=(Dodaj) o;
        return arg.equals(d.arg) && arg2.equals(d.arg2);
    }
}
