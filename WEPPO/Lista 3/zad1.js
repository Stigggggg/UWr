function fib_rek(n)
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

function fib_iter(n)
{
    var f0=0;
    var f1=1;
    var f2;
    for(let i=2; i<=n; i++)
    {
        f2=f1+f0;
        f0=f1;
        f1=f2;
    }
    return f2;
}

function fib_memo(f)
{
    var cache={};
    return function(n)
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

// console.time("n=41 rekurencja");
// console.log(fib_rek(41));
// console.timeEnd("n=41 rekurencja");

console.time("n=100 memoizacja");
var fib_rek=fib_memo(fib_rek);
console.log(fib_rek(100));
console.timeEnd("n=100 memoizacja");

