class Odcinek 
{
    private Punkt p1,p2; 
    public Odcinek(Punkt p1, Punkt p2) 
    {
        if(p1.get_x()==p2.get_x() && p1.get_y()==p2.get_y())
        {
            throw new IllegalArgumentException("Nie mozna skonstruowac odcinka - dlugosc 0");
        }
        this.p1=p1;
        this.p2=p2;
    }
    public Punkt get_p1()
    {
        return this.p1;
    } 
    public Punkt get_p2()
    {
        return this.p2;
    }
    double dl_odc()
    {
        return Math.sqrt(Math.pow(p2.get_x()-p1.get_x(),2)+Math.pow(p2.get_y()-p1.get_y(),2));
    }
    void przesun_odc(Wektor v)
    {
        p1.przesun(v);
        p2.przesun(v);
    }
    void obroc_odc(Punkt p, double kat)
    {
        p1.obroc(p,kat);
        p2.obroc(p,kat);
    }
    void odbij_odc(Prosta p)
    {
        p1.odbij(p);
        p2.odbij(p);
    }
}