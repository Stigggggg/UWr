function fib()
{
    var f0=0,f1=1,f2;
    return{
        next: function(){
            f2=f1+f0;
            f0=f1;
            f1=f2;
            return{
                value: f0,
                done: false
            };
        }
    };
}

//NIE UZYWAC
// var fib_iterator=fib();
// for(var i; (i=fib_iterator.next(), !i.done);)
// {
//     console.log(i.value);
// }

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
//TEGO TEZ NIE
// var fib_generator=fib_2();
// for(var i of fib_2())
// {
//     console.log(i);
// }

//dziala tylko w 2 przypadku, bo 1 nie spelnia iterable
//nie ma tam [Symbol.iterator]