class Punkt
{
    private double x,y;
    public Punkt(double x, double y)
    {
        this.x=x;
        this.y=y;
    }
    public double get_x()
    {
        return this.x;
    }
    public double get_y()
    {
        return this.y;
    }
    void przesun(Wektor v)
    {
        this.x+=v.dx;
        this.y+=v.dy;
    }
    void obroc(Punkt p, double kat)
    {
        double rad=kat*Math.PI/180.0;
        double x2=(x-p.x)*Math.cos(rad)-(y-p.y)*Math.sin(rad)+p.x;
        double y2=(x-p.x)*Math.sin(rad)+(y-p.y)*Math.cos(rad)+p.y;
        x=x2;
        y=y2;
    }
    void odbij(Prosta p)
    {
        Prosta prostop=new Prosta(-p.b,p.a, p.b*x-p.a*y);
        Punkt srodek= new Punkt(-((p.c*prostop.b-prostop.c*p.b)/(p.a*prostop.b-prostop.a*p.b)),(-(p.a*prostop.c-prostop.a*p.c)/(p.a*prostop.b-prostop.a*p.b)));
        // if(p.a*x+p.b*y+p.c==0)
        // {
        //     x=x;
        //     y=y;
        // }
        if(srodek.x==-x)
        {
            y=-y;
        }
        else if(srodek.y==y)
        {
            x=-x;
        }
        else
        {
            x=2*srodek.x-x;
            y=2*srodek.y-y;
        }
    }
}