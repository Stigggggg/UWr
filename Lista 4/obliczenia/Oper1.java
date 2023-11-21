package obliczenia;

public abstract class Oper1 extends Wyrazenie 
{
    protected Wyrazenie arg;
    public Oper1(Wyrazenie arg)
    {
        this.arg=arg;
    }
}
