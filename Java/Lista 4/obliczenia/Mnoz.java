package obliczenia;

public class Mnoz extends Oper2 
{
    public Mnoz(Wyrazenie arg1, Wyrazenie arg2)
    {
        super(arg1,arg2);
    }
    @Override
    public double oblicz()
    {
        return arg.oblicz()*arg2.oblicz();
    }
    @Override
    public String toString()
    {
        return arg+"*"+arg2;
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
        Mnoz m=(Mnoz) o;
        return arg.equals(m.arg) && arg2.equals(m.arg2);
    }
}
