package obliczenia;

public class Ln extends Fun1
{
    public Ln(Wyrazenie arg)
    {
        super(arg);
        if(arg.oblicz()<0)
        {
            throw new IllegalArgumentException("Blad argumentow logarytmu naturalnego");
        }
    }
    @Override
    public double oblicz()
    {
        return Math.log(arg.oblicz());
    }
    @Override
    public String toString()
    {
        return "ln("+arg+")";
    }
    public boolean equals(Object o)
    {
        if(o==this)
        {
            return true;
        }
        if(!(o instanceof Ln))
        {
            return false;
        }
        Ln l=(Ln) o;
        return arg.equals(l.arg);
    }
}
