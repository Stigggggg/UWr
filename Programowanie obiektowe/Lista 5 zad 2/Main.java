public class Main 
{
    public static void main(String args[])
    {
        //Test dodawania
        Variable x=new Variable("x");
        x.set_val(2);
        Expression expr=new Add(new Const(4), x);
        System.out.println(expr.evaluate());
        System.out.println(expr.to_string());
        x.set_val(10);
        System.out.println(expr.evaluate());
        System.out.println(expr.to_string());
        //Test odejmowania
        Variable y = new Variable("y");
        y.set_val(3);
        Expression expr2 = new Subtract(new Const(7), y);
        System.out.println(expr2.evaluate());  
        System.out.println(expr2.to_string());
    }
}
