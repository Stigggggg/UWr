package obliczenia;

public class Exp extends Fun1
{
    public Exp(Wyrazenie arg)
    {
        super(arg);
    }
    @Override
    public double oblicz()
    {
        return Math.exp(arg.oblicz());
    }
    @Override
    public String toString()
    {
        return "exp("+arg+")";
    }
    public boolean equals(Object o)
    {
        if(o==this)
        {
            return true;
        }
        if(!(o instanceof Exp))
        {
            return false;
        }
        Exp e=(Exp) o;
        return arg.equals(e.arg);
    }
}