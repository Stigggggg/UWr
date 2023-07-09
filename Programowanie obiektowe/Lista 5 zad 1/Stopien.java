public class Stopien implements Comparable<Stopien>
{
    private String nazwa;
    private int ranga;
    public Stopien(String n, int r)
    {
        this.nazwa=n;
        this.ranga=r;
    }
    public String get_nazwa()
    {
        return nazwa;
    }
    public int get_ranga()
    {
        return ranga;
    }
    public int compareTo(Stopien st)
    {
        return Integer.compare(this.ranga,st.ranga);
    }
    @Override
    public String toString()
    {
        return nazwa;
    }
}

