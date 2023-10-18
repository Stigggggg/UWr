function czy_podzielna(x)
{
    var temp=x;
    var suma=0;
    while(x>0)
    {
        let cyfra=x%10;
        if(temp%cyfra!=0)
        {
            return false;
        }
        suma+=cyfra;
        x=Math.trunc(x/10);
    }
    if(temp%suma!=0)
    {
        return false;
    }
    return true;
}

for(let i=1; i<=100000; i++)
{
    if(czy_podzielna(i))
    {
        console.log(i);
    }
}


