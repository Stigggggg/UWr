package obliczenia;

public class Log extends Fun2 
{
    public Log(Wyrazenie arg1, Wyrazenie arg2)
    {
        super(arg1,arg2);
        if(arg1.oblicz()==1 || arg1.oblicz()<0 || arg2.oblicz()<0)
        {
            throw new IllegalArgumentException("Blad argumentow logarytmu");
        }
    }
    @Override
    public double oblicz()
    {
        return Math.log(arg2.oblicz())/Math.log(arg.oblicz());
    }
    @Override
    public String toString()
    {
        return "log_"+arg+"("+arg2+")";
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
        Log l=(Log) o;
        return arg.equals(l.arg) && arg2.equals(l.arg2);
    }
}
