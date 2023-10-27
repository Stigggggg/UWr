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

// wersja iteracyjna
// for(let i=10; i<=1000; i++)
// {
//     console.time(i+"-ta liczba:");
//     let iter=fib_iter(i);
//     console.timeEnd(i+"-ta liczba:");
// }

//wersja rekurencyjna
for(let i=10; i<=45; i++)
{
    console.time(i+"-ta liczba:");
    let rek=fib_rek(i);
    console.timeEnd(i+"-ta liczba:");
}



