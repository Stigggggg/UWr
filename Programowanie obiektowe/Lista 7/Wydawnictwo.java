class Wydawnictwo extends Ksiazka
{
    int nr_wydania;
    public int get_nr()
    {
        return nr_wydania;
    }
    public void set_nr(int nr)
    {
        nr_wydania=nr;
    }
    @Override
    public String toString()
    {
        return "Wydawnictwo: (Tytul: "+tytul+" Autor: "+autor+" Rok wydania: "+rok_wydania+" Nr wydania: "+nr_wydania+")";
    }
}
