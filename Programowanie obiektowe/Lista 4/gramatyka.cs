//Mikolaj Drozd
//Zad 4 z listy 4
//mcs gramatyka.cs 
//kompilator: Mono, srodowisko: VSCode

using System;
using System.Collections.Generic;

public class Production
{
    public char Var;
    public string Expr;
    public Production(char v, string e)
    {
        Var=v;
        Expr=e;
    }
}

public class CFG
{
    public char StartSymbol;
    public List<Production> Productions;
    public CFG(char s, List<Production> pr)
    {
        StartSymbol=s;
        Productions=pr;
    }
    Random r=new Random();
    public string GenerateRandomWord(int maxLength)
    {
        string slowo="";
        char curr=StartSymbol;
        while(slowo.Length<maxLength)
        {
            List<Production> matchingRules=Productions.FindAll(rule => rule.Var == curr);
            if(matchingRules.Count==0)
            {
                break;
            }
            Production chosenRule=matchingRules[r.Next(matchingRules.Count)];
            slowo+=chosenRule.Expr;
            if(chosenRule.Expr.Length>0)
            {
                curr=chosenRule.Expr[0];
            }
            else
            {
                break;
            }
        }
        return slowo;
    }
}

class Program
{   
    public static void Main()
    {
        List<Production> rules = new List<Production>();
        rules.Add(new Production('S', "ab"));
        rules.Add(new Production('a', "abc"));
        rules.Add(new Production('b', "abbca"));
        rules.Add(new Production('a', "d"));
        CFG grammar=new CFG('S', rules);
        for(int i=0; i<10; i++)
        {
            string word=grammar.GenerateRandomWord(10);
            Console.WriteLine(word);
        }       
    }
}