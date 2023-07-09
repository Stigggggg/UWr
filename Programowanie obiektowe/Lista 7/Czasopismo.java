class Czasopismo extends Ksiazka
{
    String numer_ISSN;
    public String get_ISSN()
    {
        return numer_ISSN;
    }
    public void set_ISSN(String ISSN)
    {
        numer_ISSN=ISSN;
    }
    @Override
    public String toString()
    {
        return "Wydawnictwo: (Tytul: "+tytul+" Autor: "+autor+" Rok wydania: "+rok_wydania+" Nr ISSN: "+numer_ISSN+")";
    }
}
