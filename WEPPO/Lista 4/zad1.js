function getLastProto(o)
{
    var p=o;
    do
    {
        o=p;
        p=Object.getPrototypeOf(o);
    }while(p);
    return o;
}

var o1={};

var o2={
    name: "Mikołaj",
    surname: "Drozd",
};

var o3={
    say: function()
    {
        console.log("Hello world");
    }
}

Object.setPrototypeOf(o1,o2);

console.log(getLastProto(o1));
console.log(getLastProto(o2));
console.log(getLastProto(o3));
console.log(getLastProto(o1)===getLastProto(o2) && getLastProto(o2)===getLastProto(o3));