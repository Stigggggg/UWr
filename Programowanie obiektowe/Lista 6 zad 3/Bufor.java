import java.util.LinkedList;
import java.util.Queue;

class Bufor<T>
{
    Queue<T> kolejka;
    int rozmiar;
    public Bufor(int rozmiar)
    {
        this.kolejka=new LinkedList<>();
        this.rozmiar=rozmiar;
    }
    public synchronized void add(T elem) throws InterruptedException
    {
        while(kolejka.size()==rozmiar)
        {
            wait();
        }
        kolejka.add(elem);
        notifyAll();
    }
    public synchronized T remove() throws InterruptedException
    {
        while(kolejka.isEmpty())
        {
            wait();
        }
        T elem=kolejka.remove();
        notifyAll();
        return elem;
    }
}