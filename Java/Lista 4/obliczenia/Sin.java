package obliczenia;

public class Sin extends Fun1
{
    public Sin(Wyrazenie arg)
    {
        super(arg);
    }
    @Override
    public double oblicz()
    {
        return Math.sin(arg.oblicz());
    }
    @Override
    public String toString()
    {
        return "sin("+arg+")";
    }
    public boolean equals(Object o)
    {
        if(o==this)
        {
            return true;
        }
        if(!(o instanceof Sin))
        {
            return false;
        }
        Sin s=(Sin) o;
        return arg.equals(s.arg);
    }
}
