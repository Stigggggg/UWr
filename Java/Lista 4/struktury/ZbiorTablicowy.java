package struktury;

import java.util.Arrays;

public class ZbiorTablicowy implements Zbior, Cloneable
{
    private Para[] zbior;
    private int zapelnienie;
    public ZbiorTablicowy(int rozmiar)
    {
        this.zbior=new Para[rozmiar];
        this.zapelnienie=0;
    }
    public Para szukaj(String k)
    {
        for(Para p: zbior)
        {
            if(p!=null && p.klucz.equals(k))
            {
                return p;
            }
        }
        return null;
    }
    public void wstaw(Para p)
    {
        Para p2=szukaj(p.klucz);
        if(p2!=null)
        {
            p2.set_wartosc(p.get_wartosc());
        }
        else
        {
            if(zapelnienie<zbior.length)
            {
                zbior[zapelnienie++]=p;
            }
            else
            {
                throw new IllegalStateException("Zbior jest juz zapelniony");
            }
        }
    }
    public void usun(String k)
    {
        Para u=szukaj(k);
        if(u!=null)
        {
            for(int i=0; i<zapelnienie; i++)
            {
                if(zbior[i].klucz.equals(k))
                {
                    zbior[i]=null;
                    for(int j=i+1; j<zapelnienie; j++)
                    {
                        zbior[j-1]=zbior[j];
                    }
                    zapelnienie--;
                }
            }
        }
    }
    public void czysc()
    {
        Arrays.fill(zbior,null);
    }
    public int ile()
    {
        return zapelnienie;
    }
    @Override
    public ZbiorTablicowy clone() throws CloneNotSupportedException
    {
        ZbiorTablicowy x=(ZbiorTablicowy) super.clone();
        x.zbior=zbior.clone();
        return x;
    }
}
