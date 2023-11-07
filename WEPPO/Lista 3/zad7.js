function *fib_2()
{
    var f0=0,f1=1,f2;
    while(true)
    {
        yield f0;
        f2=f1+f0;
        f0=f1;
        f1=f2;
    }
}

function *new_generator(it,n)
{
    for(let i=0; i<n; i++)
    {
        yield it.next().value;
    }
}

for(let num of new_generator(fib_2(),10))
{
    console.log(num);
}