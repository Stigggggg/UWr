//warmup
//Hello world (13)
type HelloWorld=string

//easy
//Pick (4)
type MyPick<T,K extends keyof T>={[key in K]: T[key]}
//Readonly (7)
type MyReadonly<T>={readonly[key in keyof T]: T[key]}
//TupleToObject (11)
type TupleToObject<T extends readonly (string|symbol|number)[]>={[K in T[number]]: K};
//First of Array (14)
type First<T extends any[]>=T extends [] ? never : T[0];
//Length of Tuple (18)
type Length<T extends readonly any[]>=T['length'];
//Exclude (43)
type MyExclude<T,U>=T extends U ? never : T;
//Awaited (189)
type MyAwaited<T>=T extends Promise<infer U> ? U : never;
//If (268)
type If<C extends boolean,T,F>=C extends true ? T : F;
//Concat (533)
type Concat<T extends readonly unknown[],U extends readonly unknown[]>=[...T, ...U];
//Includes (898)
type Includes<T extends readonly any[], U> = U extends T[number] ? true : false;
//Push (3057)
type Push<T extends any[],U>=[...T,U];
//Unshift (3060)
type Unshift<T extends any[],U>=[U,...T];
//Parameters (3312)
type MyParameters<T extends (...args: any[])=>any>=T extends (...any: infer S) => any ? S : any 
//wyjaśnienie
//to działa tak, że jeśli T jest funkcją to infer S to będzie tablica argumentów tej funkcji wraz z typami tych argumentów