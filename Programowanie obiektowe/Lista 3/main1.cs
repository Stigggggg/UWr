using System;
using Lista1;
class Program
{
    public static void Main() //testy wszystkich klas
    {
        Lista<int> l=new Lista<int>();
        l.push_front(1);
        Console.WriteLine(l.is_empty());
        Console.WriteLine(l.pop_back());
        Console.WriteLine(l.is_empty());
        l.pop_front();
        l.push_front(2);
        Console.WriteLine(l.pop_back());
    }
}