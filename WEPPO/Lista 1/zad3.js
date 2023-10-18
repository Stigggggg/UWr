function is_prime(x)
{
    if(x<2)
    {
        return false;
    }
    else if(x==2)
    {
        return true;
    }
    else if(x%2==0)
    {
        return false;
    }
    else
    {
        for(let i=3; i*i<=x; i+=2)
        {
            if(x%i==0)
            {
                return false;
            }
        }
        return true;
    }
}

for(let i=2; i<=100000; i++)
{
    if(is_prime(i)==true)
    {
        console.log(i);
    }
}
