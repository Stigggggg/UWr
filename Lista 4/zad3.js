//Worker.prototype=Person.prototype
//nie dziala dobrze, poniewaz zmiana w Person skutkuje zmiana w Worker
//sa tym samym obiektem

//Worker.prototype=new Person()
//jeszcze gorzej, bo uzywajac konstruktora Person nie przekazemy argumentow dla Worker

//Worker.prototype=Object.create(Person.prototype)
//dobrze, poniewaz izolujemy prototyp, zmiany w nim nie wplyna na prototyp obiektu, z ktorego dziedziczy