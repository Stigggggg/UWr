package obliczenia;

public class Cos extends Fun1
{
    public Cos(Wyrazenie arg)
    {
        super(arg);
    }
    @Override
    public double oblicz()
    {
        return Math.cos(arg.oblicz());
    }
    @Override
    public String toString()
    {
        return "cos("+arg+")";
    }
    public boolean equals(Object o)
    {
        if(o==this)
        {
            return true;
        }
        if(!(o instanceof Cos))
        {
            return false;
        }
        Cos c=(Cos) o;
        return arg.equals(c.arg);
    }
}
