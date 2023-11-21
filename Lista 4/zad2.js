function object_or_prototype(o,prop)
{
    return o.hasOwnProperty(prop);
}

var p={
    name: "jan",
};

var q={
    surname: "kowalski",
};

var r={
    age: 20,
}

Object.setPrototypeOf(p,q);
Object.setPrototypeOf(q,r);

console.log("Tylko w obiekcie:")
for(var prop in p)
{
    if(object_or_prototype(p,prop))
    {
        console.log(prop);
    }
}

console.log("W całym łańcuchu:")
for(var prop in p)
{
    console.log(prop);
}

