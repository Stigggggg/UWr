function forEach(a,f)
{
    for(let i=0; i<a.length; i++)
    {
        f(a[i]);
    }
}

function map(a,f)
{
    var mapped=[];
    for(let i=0; i<a.length; i++)
    {
        mapped[i]=f(a[i]);
    }
    return mapped;
}

function filter(a,f)
{
    var filtered=[];
    for(let i=0; i<a.length; i++)
    {
        if(f(a[i]))
        {
            filtered[i]=a[i];
        }
    }
    return filtered;
}

var a=[1,2,3,4];

forEach(a, _=>{console.log(_);});
var mapped=map(a,_=>_*2);
console.log(mapped);
var filtered=filter(a,_=>_<3);
console.log(filtered);

