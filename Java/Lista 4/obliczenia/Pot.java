package obliczenia;

public class Pot extends Fun2 
{
    public Pot(Wyrazenie arg1, Wyrazenie arg2)
    {
        super(arg1,arg2);
    }
    @Override
    public double oblicz()
    {
        return Math.pow(arg.oblicz(),arg2.oblicz());
    }
    @Override
    public String toString()
    {
        return arg+"^"+arg2;
    }
    @Override 
    public boolean equals(Object o)
    {
        if(this==o)
        {
            return true;
        }
        if(!(o instanceof Pot))
        {
            return false;
        }
        Pot p=(Pot) o;
        return arg.equals(p.arg) && arg2.equals(p.arg2);
    }
}
