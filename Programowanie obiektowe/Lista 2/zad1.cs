//Mikolaj Drozd
//Zad 1 z listy 2
//mcs zad1.cs

using System;

class IntStream 
{
    private const int start=-1;
    private int max=2147483647;
    protected int curr=start;
    virtual public int next()
    {
        curr++;
        return curr;
    }
    virtual protected bool eos()
    {
        if(curr<max)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    void reset()
    {
        //przyjalem, ze gdy osiagniemy maksymalnego inta, eos() osiagnie true i zaczniemy strumien od nowa
        if(eos()==true)
        {
            curr=start; 
        }
    }
}

class PrimeStream : IntStream
{
    private int max_prime=2147483647; 
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
    override public int next()
    {
        curr++;
        while(pierwsza(curr)==false)
        {
            curr++;
        }
        return curr;
    }
    override protected bool eos()
    {
        if(curr<max_prime)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

class RandomStream : IntStream
{
    Random rnd= new Random();
    override public int next()
    {
        int num=rnd.Next();
        return num;
    }
    override protected bool eos()
    {
        return false;
    }
}

class RandomWordStream : PrimeStream
{
    Random rnd=new Random();
    protected int start=0;
    public string nextt()
    {
        start++;
        while(pierwsza(start)==false)
        {
            start++;
        }
        int val;
        string str="";
        char c;
        for(int i=0; i<start; i++)
        {
            val=rnd.Next(33,127); //zakres taki, zeby nie wypisywalo spacji lub enterow, co mogloby sprawiac wrazenie, ze program nie dziala poprawnie
            c=Convert.ToChar(val);
            str+=c;
        }
        return str;
    }
}

class Program
{
    public static void Main()
    {
        IntStream s=new IntStream();
        for(int i=0; i<5; i++)
        {
            Console.WriteLine(s.next());
        }
        Console.WriteLine();
        PrimeStream p=new PrimeStream();
        for(int i=0; i<5; i++)
        {
            Console.WriteLine(p.next());
        }
        Console.WriteLine();
        RandomStream r=new RandomStream();
        for(int i=0; i<5; i++)
        {
            Console.WriteLine(r.next());
        }
        Console.WriteLine();
        RandomWordStream rws=new RandomWordStream();
        for(int i=0; i<5; i++)
        {
            Console.WriteLine(rws.nextt());
        }
        Console.WriteLine();
    }
}