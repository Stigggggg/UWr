//Mikolaj Drozd
//Zad 2 z listy 4
//mcs fibonacci.cs
//kompilator: Mono, srodowisko: VSCode

using System;
using System.Collections;
using System.Collections.Generic;

public class SlowaFibonacciego : IEnumerable<string>
{
    private int n;
    public SlowaFibonacciego(int n)
    {
        this.n=n;
    }
    public IEnumerator<string> GetEnumerator()
    {
        int i=1;
        string s="b";
        yield return s;
        if(n>=2)
        {
            i++;
            s="a";
            yield return s;
        }
        if(n>=3)
        {
            i++;
            string s2="ab";
            yield return s2;
            while(i<n)
            {
                string s3=s2+s;
                yield return s3;
                s=s2;
                s2=s3;
                i++;
            }
        }
    }
    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }
}

class Program
{
    public static void Main()
    {
        SlowaFibonacciego sf=new SlowaFibonacciego(6);
        foreach(string s in sf)
        {
            Console.WriteLine(s);
        }
    }
}