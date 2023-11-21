package rozgrywka;

import obliczenia.Wymierna;

public class Gra 
{
    private int zakres;
    private Wymierna liczba;
    private int maksIloscProb;
    private int licznikProb;
    private boolean aktywna;
    public Gra() 
    {
        aktywna=false;
    }
    public int start(int z) 
    {
        if (z<5 || z>20)
        {
            throw new IllegalArgumentException("Zakres: 5-20.");
        }
        zakres=z;
        int licz, mian;
        do 
        {
            licz=(int) (Math.random()*zakres)+1;
            mian=(int) (Math.random()*zakres)+1;
        }while(licz>=mian);
        liczba=new Wymierna(licz, mian);
        maksIloscProb=(int) Math.ceil(3*(Math.log(zakres)/Math.log(2)));
        licznikProb=0;
        aktywna=true;
        if(liczba.get_licznik()<liczba.get_mianownik())
        {
            return maksIloscProb;
        }
        else return -1;
    }
    public String odgadnij(Wymierna propozycja) 
    {
        if (aktywna==false) 
        {
            throw new IllegalStateException("Gra nie jest aktywna.");
        }
        licznikProb++;
        if(propozycja.equals(liczba)) 
        {
            aktywna=false;
            return "Zwyciestwo";
        }
        if (licznikProb==maksIloscProb) 
        {
            aktywna=false;
            return "Porazka";
        }
        return "Kontynuacja";
    }
    public String rezygnuj() 
    {
        aktywna=false;
        return "Rezygnacja";
    }
    public boolean czy_aktywna() 
    {
        return aktywna;
    }
    public int ile_prob() 
    {
        return licznikProb;
    }
    public int ile_zostalo() 
    {
        return maksIloscProb-licznikProb;
    }
    public int porownaj(Wymierna proba) 
    {
        if(aktywna==false) 
        {
            throw new IllegalStateException("Gra nie jest aktywna.");
        }
        if(proba.equals(liczba)) 
        {
            return 0;
        }
        return proba.compareTo(liczba);
    }
}
