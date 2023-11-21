package obliczenia;

public abstract class Oper2 extends Oper1 
{
    protected Wyrazenie arg2;
    public Oper2(Wyrazenie arg, Wyrazenie arg2)//sprawdzic czy arg jest nullem
    {
        super(arg);
        this.arg2=arg2;
    }
}
