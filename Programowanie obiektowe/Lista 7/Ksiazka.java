import java.io.*;

class Ksiazka implements Serializable
{
    String tytul;
    String autor;
    int rok_wydania;
    public String get_tytul()
    {
        return tytul;
    }
    public void set_tytul(String t)
    {
        tytul=t;
    }
    public String get_autor()
    {
        return autor;
    }
    public void set_autor(String a)
    {
        autor=a;
    }
    public int get_rok()
    {
        return rok_wydania;
    }
    public void set_rok(int r)
    {
        rok_wydania=r;
    }
    @Override
    public String toString()
    {
        return "Ksiazka: (Tytul: "+tytul+", Autor: "+autor+", Rok wydania: "+rok_wydania+")";
    }
}
