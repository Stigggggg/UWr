var n=1;
console.log(typeof Object.getPrototypeOf(n));

n.foo="foo";
console.log(n);
console.log(n.foo);

//niejawna koercja prymitywnych typów do obiektów sprawia, że prototypem liczby będzie object
//nie zmienia to jednak faktu, że nie można dodawać tam pól ani metod
