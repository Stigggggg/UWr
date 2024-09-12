package obliczenia;

public class Dziel extends Oper2 
{
    public Dziel(Wyrazenie arg1, Wyrazenie arg2)
    {
        super(arg1,arg2);
        if(arg2.oblicz()==0)
        {
            throw new IllegalArgumentException("Dzielenie przez 0");
        }
    }
    @Override
    public double oblicz()
    {
        return arg.oblicz()/arg2.oblicz();
    }
    @Override
    public String toString()
    {
        if((arg instanceof Dodaj || arg instanceof Odejmij) && (arg2 instanceof Dodaj || arg2 instanceof Odejmij))
            return"("+arg+")"+"/"+"("+arg2+")";
        else if(arg instanceof Dodaj || arg instanceof Odejmij)
            return "("+arg+")"+"/"+arg2.toString();
        else if(arg2 instanceof Dodaj || arg2 instanceof Odejmij)
            return arg.toString()+"/"+"("+ arg2+")";
        else
            return arg.toString()+"/"+arg2.toString();
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
        Dziel d=(Dziel) o;
        return arg.equals(d.arg) && arg2.equals(d.arg2);
    }
}

