class Prosta 
{
    public final double a,b,c;
    public Prosta(double a, double b, double c)
    {
        this.a=a;
        this.b=b;
        this.c=c;
    }
    static Prosta przesun(Prosta p, Wektor v)
    {
        return new Prosta(p.a,p.b,p.c-v.dx-v.dy);
    }
    static boolean czy_prostopadle(Odcinek o1, Odcinek o2) 
    {
        double a1=(o1.get_p2().get_y()-o1.get_p1().get_y())/(o1.get_p2().get_x()-o1.get_p1().get_x());
        double a2=(o2.get_p2().get_y()-o2.get_p1().get_y())/(o2.get_p2().get_x()-o2.get_p1().get_x());
        double eps = 0.00001;
        if(Math.abs(a1*a2+1)<eps) 
        {
            return true;
        } 
        else 
        {
            return false;
        }
    }
    static boolean czy_rownolegle(Odcinek o1, Odcinek o2) 
    {
        double a1=(o1.get_p2().get_y()-o1.get_p1().get_y())/(o1.get_p2().get_x()-o1.get_p1().get_x());
        double a2=(o2.get_p2().get_y()-o2.get_p1().get_y())/(o2.get_p2().get_x()-o2.get_p1().get_x());
        double xa=o1.get_p1().get_x();
        double ya=o1.get_p1().get_y();
        double xb=o1.get_p2().get_x();
        double yb=o1.get_p2().get_y();
        double xc=o2.get_p1().get_x();
        double yc=o2.get_p1().get_y();
        double xd=o2.get_p2().get_x();
        double yd=o2.get_p2().get_y();
        if((xa==xb && xc==xd) || (ya==yb && yc==yd)) 
        {
            return true;
        }
        else if((xa==xb && yc==yd) || (xc==xd && ya==yb)) 
        {
            return true;
        }
        else if(Math.abs(a1-a2)<0.00001) 
        {
            return true;
        } 
        else 
        {
            return false;
        }
    }
    static Punkt przeciecie(Prosta p1, Prosta p2)
    {
        double x=((p2.b*p1.c-p1.b*p2.c)/(p1.a*p2.b-p2.a*p1.b));
        double y=((p1.a*p2.c-p2.a*p1.c)/(p1.a*p2.b-p2.a*p1.b));
        return new Punkt(x,y);
    }
}
