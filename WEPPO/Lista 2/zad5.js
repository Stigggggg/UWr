var o={
    a: 5,
    f()
    {
        return this.a;
    },
    get a_val()
    {
        return this.a;
    },
    set a_val(x)
    {
        this.a=x;
    }
};

//test gettera i settera
console.log(o.a_val)
o.a_val=42;
console.log(o.a_val);

//pole i metode da sie ustawic bez defineProperty
o.b="haha";
o.f2=function()
{
    return this.a+1;
}
console.log(o.b);
console.log(o.f2());
//gettera i settera sie nie da:
o.get2={
    get: function()
    {
        return this.b;
    }
}
console.log(o.get2);

//dodanie gettera i settera z objProperty:
Object.defineProperty(o,"get3",{get: function(){return this.b;}});
Object.defineProperty(o,"set3",{set: function(x){this.b=x;}});
console.log(o.get3);
o.b="coś";
console.log(o.get3);
o.set3=3;
console.log(o.b);

