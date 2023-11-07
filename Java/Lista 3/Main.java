import figury.*;

public class Main
{
    public static void main(String[] args)
    {
        //testy klasy punkt
        Punkt p=new Punkt(1,3);
        Punkt q=new Punkt(4, 7);
        Wektor v=new Wektor(2, 4);
        p.przesun(v);
        System.out.print(p.get_x()+" "+p.get_y());
        System.out.println();
        p.obroc(q,90);
        System.out.print(p.get_x()+" "+p.get_y());
        System.out.println();
        Prosta pr=new Prosta(-1, 1, 0);
        p.odbij(pr);
        System.out.print(p.get_x()+" "+p.get_y());
        System.out.println();
        //testy klasy odcinek
        Odcinek o=new Odcinek(p,q);
        System.out.println(o.dl_odc());
        o.przesun_odc(v);
        System.out.println(o.get_p1().get_x()+" "+o.get_p1().get_y());
        System.out.println(o.get_p2().get_x()+" "+o.get_p2().get_y());
        //o.odbij_odc(pr);
        //System.out.println(o.get_p1().get_x()+" "+o.get_p1().get_y());
        //testy bledow - odcinek
        // Punkt p1=new Punkt(1,3);
        // Punkt p2=new Punkt(1,3);
        // Odcinek o2=new Odcinek(p1,p2);
        // System.out.println(o2.dl_odc());
        //testy bledow - trojkat
        // Punkt p3=new Punkt(1,1);
        // Punkt p4=new Punkt(1,2);
        // Punkt p5=new Punkt(1,3);
        // Trojkat t1=new Trojkat(p3,p4,p5);
        Wektor v2=new Wektor(5,-2);
        Wektor v3=Wektor.zloz(v,v2);
        System.out.println(v3.dx+" "+v3.dy);
        Prosta pr2=new Prosta(-2,5,3);
        Punkt prz=Prosta.przeciecie(pr,pr2);
        System.out.println(prz.get_x()+" "+prz.get_y());
        //testy rownoleglosci i prostopadlosci
        Prosta a1=new Prosta(-2,4,5);
        Prosta a2=new Prosta(-6,13,6);
        boolean czy=Prosta.czy_rownolegle(a1,a2);
        System.out.println(czy);
        Prosta a3=new Prosta(0,1,1);
        Prosta a4=new Prosta(1,0,3);
        System.out.println(Prosta.czy_prostopadle(a3,a4));
    }
}