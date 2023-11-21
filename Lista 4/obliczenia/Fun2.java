package obliczenia;

public abstract class Fun2 extends Fun1 
{
    protected Wyrazenie arg2;
    public Fun2(Wyrazenie arg, Wyrazenie arg2)
    {
        super(arg);
        this.arg2=arg2;
    }
}
