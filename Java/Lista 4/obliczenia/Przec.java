package obliczenia;

public class Przec extends Oper1 
{
    public Przec(Wyrazenie arg)
    {
        super(arg);
    }
    @Override
    public double oblicz()
    {
        return 1/arg.oblicz();
    }
    @Override
    public String toString()
    {
        return "1/"+arg;
    }
    public boolean equals(Object o)
    {
        if(o==this)
        {
            return true;
        }
        if(!(o instanceof Przec))
        {
            return false;
        }
        Przec p=(Przec) o;
        return arg.equals(p.arg);
    }
}
