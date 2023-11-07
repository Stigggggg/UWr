package figury;

public class Prosta 
{
    public final double a,b,c;
    public Prosta(double a, double b, double c)
    {
        if(a==0 && b==0)
        {
            throw new IllegalArgumentException("a i b nie moga byc jednoczesnie rowne 0");
        }
        this.a=a;
        this.b=b;
        this.c=c;
    }
    public static Prosta przesun(Prosta p, Wektor v)
    {
        return new Prosta(p.a,p.b,p.c-v.dx-v.dy);
    }
    public static boolean czy_prostopadle(Prosta p1, Prosta p2) 
    {
        if(p1.a*p2.a+p1.b*p2.b==0)
        {
            return true;
        }
        return false;
    }
    public static boolean czy_rownolegle(Prosta p1, Prosta p2) 
    {
        if(p1.a*p2.b==p2.a*p1.b)
        {
            return true;
        }
        return false;
    }
    public static Punkt przeciecie(Prosta p1, Prosta p2)
    {
        if(czy_rownolegle(p1,p2))
        {
            throw new IllegalArgumentException("Proste sa rownolegle - nie ma punktu przeciecia");
        }
        double x=((p1.b*p2.c-p2.b*p1.c)/(p1.a*p2.b-p2.a*p1.b));
        double y=((p2.a*p1.c-p1.a*p2.c)/(p1.a*p2.b-p2.a*p1.b));
        return new Punkt(x,y);
    }
}
