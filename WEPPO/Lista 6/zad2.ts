function fib_rek(n: number): number
{
    if(n==0)
    {
        return 0;
    }
    else if(n==1)
    {
        return 1;
    }
    else return fib_rek(n-1)+fib_rek(n-2);
}

//type Func<T1 extends string|number,T2>=(n: T1)=>T2

function fib_memo<T1 extends string|number|symbol,T2>(f: (arg: T1)=>T2): (arg: T1)=>T2
{
    var cache={} as Record<T1,T2>
    return function(n: T1)
    {
        if(n in cache)
        {
            return cache[n];
        }
        else
        {
            var f_n=f(n);
            cache[n]=f_n;
            return f_n;
        }
    }
}

var fib_m=fib_memo(fib_rek);
console.log(fib_m(8));