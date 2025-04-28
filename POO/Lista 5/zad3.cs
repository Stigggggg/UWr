using System;
using System.Collections;

//chcemy użyć Comparison<int> jako implementacji interfejsu IComparer
public class ComparisonAdapter : IComparer
{
    private readonly Comparison<int> _comparison;
    public ComparisonAdapter(Comparison<int> comparison)
    {
        _comparison = comparison ?? throw new ArgumentNullException(nameof(comparison));
    }
    public int Compare(object x, object y)
    {
        return _comparison((int)x, (int)y); //rzutujemy obiekty i przekazujemy do _comparison
    }
}

class Zad3
{
    static int IntComparer(int x, int y)
    {
        return x.CompareTo(y);
    }
    static void Main()
    {
        ArrayList a = new ArrayList() { 1, 5, 3, 3, 2, 4, 3 };
        Console.WriteLine("Przed sortowaniem:");
        foreach (int i in a) 
        {
            Console.Write(i + " ");
        }
        Console.WriteLine();
        a.Sort(new ComparisonAdapter(IntComparer)); //comparison adapter opakowuje IComparer, za pomocą funkcji Compare sortujemy
        Console.WriteLine("Po sortowaniu:");
        foreach (int i in a)
        {
            Console.Write(i + " ");
        }
        Console.WriteLine();
    }
}

