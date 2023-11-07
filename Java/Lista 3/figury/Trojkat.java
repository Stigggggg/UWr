package figury;

import java.util.Objects;

public class Trojkat 
{
    private Punkt p1,p2,p3;
    public Trojkat(Punkt p1, Punkt p2, Punkt p3)
    {
        if(!Objects.equals(p1,p2) || !Objects.equals(p1,p3) || !Objects.equals(p3,p2))
        {
            throw new IllegalArgumentException("Nie mozna skonstruowac trojkata, te same punkty");
        }
        if((p2.get_x()-p1.get_x())*(p3.get_y()-p1.get_y())-(p2.get_y()-p1.get_y())*(p3.get_x()-p1.get_x())==0)
        {
            throw new IllegalArgumentException("Nie mozna skonstruowac trojkata, punkty wspolliniowe");
        }
    }
    public Punkt get_p1()
    {
        return this.p1;
    } 
    public Punkt get_p2()
    {
        return this.p2;
    }
    public Punkt get_p3()
    {
        return this.p3;
    }  
    void przesun_troj(Wektor v)
    {
        p1.przesun(v);
        p2.przesun(v);
        p3.przesun(v);
    }
    void obroc_troj(Punkt p, double kat)
    {
        p1.obroc(p,kat);
        p2.obroc(p,kat);
        p3.obroc(p,kat);
    }
    void odbij_troj(Prosta p)
    {
        p1.odbij(p);
        p2.odbij(p);
        p3.odbij(p);
    }
}
