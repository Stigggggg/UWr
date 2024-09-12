function forEach<T>(a: T[],f: (x: T)=>void): void
{
    for(let i=0; i<a.length; i++)
    {
        f(a[i]);
    }
}

function map<T1,T2>(a: T1[],f: (x: T1)=>T2): T2[]
{
    var mapped: T2[]=[];
    for(let i=0; i<a.length; i++)
    {
        mapped[i]=f(a[i]);
    }
    return mapped;
}

function filter<T>(a: T[],f: (x: T)=>boolean): T[]
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

var tab=[1,2,3,4];

forEach(tab, _=>console.log(_));
var mapped=map(tab, _=>_*2);
console.log(mapped);
var filtered=filter(tab, _=>_<3);
console.log(filtered);