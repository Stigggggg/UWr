package obliczenia;

public class Neg extends Oper1 
{
    public Neg(Wyrazenie arg)
    {
        super(arg);
    }
    @Override
    public double oblicz()
    {
        return -arg.oblicz();
    }
    @Override
    public String toString()
    {
        return "-("+arg+")";
    }
    public boolean equals(Object o)
    {
        if(o==this)
        {
            return true;
        }
        if(!(o instanceof Neg))
        {
            return false;
        }
        Neg n=(Neg) o;
        return arg.equals(n.arg);
    }
}
