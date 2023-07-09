using System;
using Slownik;
class Program
{
    public static void Main() //testy mozliwosci klas zakomentowane
    {
        MyDictionary<int,string> d=new MyDictionary<int,string>();
        d.add(1,"aaaa");
        d.add(2,"bbbb");
        d.add(3,"cccc");
        d.add(4,"dddd");
        d.add(5,"eeee");
        Console.WriteLine(d.dict[1].Key);
        Console.WriteLine(d.dict[1].Value);
        //d.add(5,"ffff"); //test sprawdzajacy dodanie drugi raz tego samego klucza
        //Console.WriteLine(d.search(6)); 
        //Console.WriteLine(d.search(5));
        //d.remove(3);
        //Console.WriteLine(d.search(3));
        //d.remove(2);
        //d.remove(4);
    }
}