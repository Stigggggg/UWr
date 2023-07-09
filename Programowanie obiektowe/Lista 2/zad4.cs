//Mikolaj Drozd
//Zadanie 4 z listy 2
//mcs zad4.cs
using System;
using System.Collections.Generic;

class LazyIntList
{
    protected List<int> lista;
    public LazyIntList()
    {
        lista=new List<int>();
    }
    public int size()
    {
        return lista.Count;
    }
    virtual public int element(int i)
    {
        if(i<1)
        {
            return -1; //na niedozwolonych numerach indeksu program zwróci -1
        }
        else if(i>size())
        {
            for(int j=size(); j<i; j++)
            {
                lista.Add(j);
            }
            return lista[i-1];
        }
        else 
        {
            return lista[i-1];
        }
    }
}

class LazyPrimeList : LazyIntList
{
    protected bool pierwsza(int n)
    {
        if(n<2)
        {
            return false;
        }
        else if(n==2)
        {
            return true;
        }
        else if(n%2==0)
        {
            return false;
        }
        else
        {
            for(int i=3; i*i<=n; i+=2)
            {
                if(n%i==0)
                {
                    return false;
                }
            }
            return true;
        }
    }
    override public int element(int i)
    {
        if(i<1)
        {
            return -1; //tak samo jak w oryginale
        }
        else if(i>size())
        {
            for(int j=size(); j<i; j++)
            {
                int temp;
                if(size()>0)
                {
                    temp=lista[size()-1]+1;
                }
                else temp=2;
                while(pierwsza(temp)==false)
                {
                    temp++;
                }
                lista.Add(temp);
            }
            return lista[i-1];
        }
        else return lista[i-1];
    }
}

class Program
{
    public static void Main()
    {
        // testy do klasy LazyIntList
        // LazyIntList l=new LazyIntList();
        // Console.WriteLine(l.size());
        // Console.WriteLine(l.element(3));
        // Console.WriteLine(l.size());
        // Console.WriteLine(l.element(2));
        // Console.WriteLine(l.size());
        // Console.WriteLine(l.element(0));
        // Console.WriteLine(l.element(5));
        // Console.WriteLine(l.size());

        // testy do klasy LazyPrimeList
        // LazyPrimeList lp=new LazyPrimeList();
        // Console.WriteLine(lp.element(1));
        // Console.WriteLine(lp.size());
        // Console.WriteLine(lp.size());
        // Console.WriteLine(lp.element(2));
        // Console.WriteLine(lp.element(5));
        // Console.WriteLine(lp.size());
        // Console.WriteLine(lp.element(0));
    }
}