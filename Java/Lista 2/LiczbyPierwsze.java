import java.lang.System;

public final class LiczbyPierwsze
{
    private final static int potega2=21;
    private final static int[] sito=new int[1<<potega2];
    static
    {
        sito[0]=0;
        sito[1]=1;
        for(int i=2; i*i<sito.length; i++)
        {
            if(sito[i]==0)
            {
                for(int j=i; j<sito.length; j+=i)
                {
                    if(sito[j]==0)
                    {
                        sito[j]=i;
                    }
                }
            }
        }
    }
    public static boolean czyPierwsza(long x) 
    {
        if(x<=1) 
        {
            return false;
        }
        if(x>sito.length)
        {
            for(long i=2; i<(long)Math.sqrt(x); i++)
            {
                if(x%i==0)
                {
                    return false;
                }
            }
            return true;
        }
        return sito[(int) x]==x;
    }
    public static long[] naCzynnikiPierwsze(long x)
    {
        long[] factors=new long[64];
        int i=0;
        if(x==0 || x==1 | x==-1)
        {
            return new long[]{x};
        }
        if(x<0)
        {
            factors[0]=-1;
            x=-x;
            if(x<0)
            {
                factors[1]=2;
                x/=2;
                x=-x;
                i=2;
            }
            else
            {
                i=1;
            }
        }
        if(x<sito.length)
        {
            while(x!=1)
            {
                long d=sito[(int) x];
                factors[i]=d;
                i++;
                x/=d;
            }
        }
        else
        {
            long d=2;
            while(x!=1)
            {
                if(x%d==0)
                {
                    factors[i]=d;
                    i++;
                    x/=d;
                }
                else
                {
                    d++;
                }
            }
        }
        long[] wynik=new long[i];
        System.arraycopy(factors,0,wynik,0,i);
        return wynik;
    }
    public static void main(String[] args)
    {
        if(args.length==0)
        {
            System.err.println("Nalezy podac liczby calkowite typu long");
            return;
        }
        long[] argtab=new long[args.length];
        for(int i=0; i<args.length; i++)
        {
            try
            {
                argtab[i]=Long.parseLong(args[i]);
            }
            catch(NumberFormatException e)
            {
                System.err.println("Niepoprawne wejscie, prosze podac dobra liczbe typu long");
                return;
            }
            System.out.println(czyPierwsza(argtab[i]));
            long[] czynniki=LiczbyPierwsze.naCzynnikiPierwsze(argtab[i]);
            System.out.print(argtab[i]+"=");
            for(int j=0; j<czynniki.length; j++)
            {
                System.out.print(czynniki[j]);
                if(j<czynniki.length-1)
                {
                    System.out.print("*");
                }
            }
            System.out.println();
        }
        // for(int i=0; i<20; i++)
        // {
        //     System.out.println(sito[i]);
        // }
        // System.out.println(czyPierwsza(4));
        // System.out.println(czyPierwsza(5));
        // System.out.println(czyPierwsza(2100001));
        // long[] x=naCzynnikiPierwsze(-24);
        // for(int i=0; i<x.length; i++)
        // {
        //     System.out.println(x[i]);
        // }
        // System.out.println(czyPierwsza(9223372036854775783L));
        // long[] y=naCzynnikiPierwsze(-9223372036854775808L);
        // for(int i=0; i<y.length; i++)
        // {
        //     System.out.println(y[i]);
        // }
    }
}