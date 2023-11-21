package obliczenia;

import struktury.*;

public class Main 
{
    public static void main(String[] args)
    {
        // //7+5*3-1=21
        Wyrazenie w1=new Odejmij(
                new Dodaj(
                        new Liczba(7),
                        new Mnoz(
                                new Liczba(5),
                                new Liczba(3)
                        )
                ),
                new Liczba(1)
        );
        System.out.println(w1.toString());
        System.out.println(w1.oblicz());
        Zmienna.dodaj_zmienna("x", 1.618);
        Wyrazenie w2 = new Mnoz(
                new Neg(new Odejmij(new Liczba(2), new Zmienna("x"))),
                new E()
        );
        System.out.println(w2.toString());
        System.out.println(w2.oblicz());
        Wyrazenie w3 = new Dziel(
                new Odejmij(
                        new Mnoz(new Liczba(3), new Pi()),
                        new Liczba(1)
                ),
                new Dodaj(new Zmienna("x"), new Liczba(5))
        );
        System.out.println(w3);
        Wyrazenie w4 = new Sin(
                new Dziel(
                        new Dodaj(new Zmienna("x"), new Liczba(13)),
                        new Odejmij(new Liczba(1), new Zmienna("x"))
                )
        );
        System.out.println(w4);
        Wyrazenie w5 = new Dodaj(
                new Pot(new E(), new Liczba(5)),
                new Mnoz(new Zmienna("x"), new Log(new E(), new Zmienna("x")))
        );
        System.out.println(w5.oblicz());
        Zmienna x1=new Zmienna("y");
        Zmienna x2=new Zmienna("y");
        System.out.println(x1.equals(x2));
        ZbiorTablicowy z=new ZbiorTablicowy(10);
        try
        {
            ZbiorTablicowy z2=(ZbiorTablicowy) z.clone();
            System.out.println(z);
            System.out.println(z2);
        } 
        catch(CloneNotSupportedException e)
        {
            e.printStackTrace();
        }
    }
}
