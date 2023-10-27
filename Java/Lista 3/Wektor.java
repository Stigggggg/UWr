class Wektor 
{
    public final double dx,dy;
    public Wektor(double dx, double dy)
    {
        this.dx=dx;
        this.dy=dy;
    }
    static Wektor zloz(Wektor v1, Wektor v2)
    {
        Wektor v3=new Wektor(v1.dx+v2.dx,v1.dy+v2.dy);
        return v3;
    }
}
