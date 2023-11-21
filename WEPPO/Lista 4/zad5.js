function Foo()
{
    var priv="Prywatna składowa";//zmienna lokalna nie obiekt 
    this.Bar=function() //do tego moge sie odwolac bo funkcja i bo this
    {
        console.log("Metoda publiczna");
        function Qux()//funkcja w funkcji nie da sie odwolac
        {
            console.log(priv);
        }
        Qux();
    };
}
var call=new Foo();
call.Bar();//dobrze
call.Qux();//zle