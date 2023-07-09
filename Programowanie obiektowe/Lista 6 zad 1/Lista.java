import java.io.Serializable;
import java.util.ArrayList;

public class Lista implements Serializable 
{
    private ArrayList<Integer> l;
    public Lista() 
    {
        l=new ArrayList<>();
    }
    public void add(int val) 
    {
        l.add(val);
    }
    public void remove(int i) 
    {
        l.remove(i);
    }
    public int get(int i) 
    {
        return l.get(i);
    }
    public int size() 
    {
        return l.size();
    }
}