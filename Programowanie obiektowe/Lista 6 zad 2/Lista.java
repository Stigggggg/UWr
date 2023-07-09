import java.util.ArrayList;
import java.util.List;
import java.util.Collection;
import java.util.Iterator;
import java.util.Arrays;

public class Lista<T> implements Collection<T> 
{
    private class Element<E>
    {
        public T val;
        public Element<T> prev;
        public Element<T> next;
    } 
    private Element<T> first;
    private Element<T> last;
    private int size;

    public Lista() 
    {
        first = null;
        last = null;
        size = 0;
    }
    public void push_front(T elem)
    {
        var nowy=new Element<T>();
        nowy.val=elem;
        if(first==null)
        {
            first=nowy;
            last=nowy;
        }
        else
        {
            nowy.next=first;
            first.prev=nowy;
            first=nowy;
        }
    }
    public void push_back(T elem)
    {
        var nowy=new Element<T>();
        nowy.val=elem;
        if(last==null)
        {
            first=nowy;
            last=nowy;
        }
        else
        {
            nowy.prev=last;
            last.next=nowy;
            last=nowy;
        }
    }
    public T pop_front()
    {
        if(first==null)
        {
            throw new IllegalStateException("Lista jest pusta");
        }
        var wartosc=first.val;
        if(first==last)
        {
            first=null;
            last=null;
        }
        else
        {
            first=first.next;
            first.prev=null;
        }
        return wartosc;
    }
    public T pop_back()
    {
        if(last==null)
        {
            throw new IllegalStateException("Lista jest pusta");
        }
        var wartosc=last.val;
        if(first==last)
        {
            first=null;
            last=null;
        }
        else
        {
            last=last.prev;
            last.next=null;
        }
        return wartosc;
    }
    public boolean is_empty()
    {
        if(first==null)
        {
            return true;
        }
        else return false;
    }
    // Implementacja metod z interfejsu Collection<E>
    @Override
    public boolean add(T elem) 
    {
        push_back(elem);
        return true;
    }
    @Override
    public boolean addAll(Collection<? extends T> collection) 
    {
        for(T elem : collection) 
        {
            add(elem);
        }
        return true;
    }
    @Override
    public void clear() 
    {
        first = null;
        last = null;
        size = 0;
    }
    @Override
    public boolean contains(Object obj) 
    {
        for(T elem : this) 
        {
            if(elem.equals(obj)) 
            {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean containsAll(Collection<?> collection) 
    {
        for(Object obj : collection) 
        {
            if(!contains(obj)) 
            {
                return false;
            }
        }
        return true;
    }

    @Override
    public boolean isEmpty() 
    {
        return size() == 0;
    }

    @Override
    public Iterator<T> iterator() 
    {
        return new Iterator<T>() 
        {
            private Element<T> current = first;
            @Override
            public boolean hasNext() 
            {
                return current != null;
            }
            @Override
            public T next() 
            {
                T val = current.val;
                current = current.next;
                return val;
            }
        };
    }
    @Override
    public boolean remove(Object obj) 
    {
        Element<T> current = first;
        while(current != null) 
        {
            if(current.val.equals(obj)) 
            {
                if(current == first) 
                {
                    pop_front();
                } 
                else if(current == last) 
                {
                    pop_back();
                } 
                else 
                {
                    current.prev.next = current.next;
                    current.next.prev = current.prev;
                    size--;
                }
                return true;
            }
            current = current.next;
        }
        return false;
    }

    @Override
    public boolean removeAll(Collection<?> collection) {
        boolean modified = false;
        for(Object obj : collection) {
            modified |= remove(obj);
        }
        return modified;
    }

    @Override
    public boolean retainAll(Collection<?> collection) 
    {
        boolean modified = false;
        Element<T> current = first;
        while(current != null) 
        {
            if(!collection.contains(current.val)) 
            {
                if(current == first) 
                {
                    pop_front();
                    current = first;
                } 
                else if(current == last) 
                {
                    pop_back();
                    current = null;
                } 
                else 
                {
                    current.prev.next = current.next;
                    current.next.prev = current.prev;
                    size--;
                    current = current.next;
                }
                modified = true;
            } 
            else 
            {
                current = current.next;
            }
        }
        return modified;
    }

    @Override
    public int size() 
    {
        return size;
    }
    @Override
    public Object[] toArray() 
    {
        Object[] array = new Object[size()]; // tworzymy tablicę o rozmiarze równym liczbie elementów w liście
        Element<T> current = first;
        int index = 0;
        while (current != null) 
        { // iterujemy po elementach listy i dodajemy je do tablicy
            array[index++] = current.val;
            current = current.next;
        }
        return array;
    }
    @Override
    public <T> T[] toArray(T[] a) 
    {
        if (a.length < size()) 
        {
            // Tworzymy nową tablicę o wymaganym rozmiarze i typie elementów T
            a = (T[]) Array.newInstance(a.getClass().getComponentType(), size());
        }
        int i = 0;
        for (Element<T> current = lista.first; current != null; current = current.next) 
        {
            a[i++] = current.val;
        }
        if (a.length > size()) {
            a[size()] = null;
        }
        return a;
    }
}
