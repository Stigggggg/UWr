import java.util.*;

public class OrderedList<T extends Comparable<T>>
{
    private List<T> list;
    public OrderedList()
    {
        this.list=new ArrayList<>();
    }
    public void add_elem(T elem)
    {
        int ind=Collections.binarySearch(list,elem);
        if(ind<0)
        {
            ind=-ind-1;
        }
        list.add(ind,elem);
    }
    public T get_first_elem()
    {
        return list.get(0);
    }
    public String to_string()
    {
        StringBuilder sb=new StringBuilder();
        for(T elem : list)
        {
            sb.append(elem.toString()).append(" ");
        }
        return sb.toString();
    }
}
