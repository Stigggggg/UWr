public class Main 
{
    public static void main(String[] args)
    {
        OrderedList<Stopien> stopnie=new OrderedList<>();
        stopnie.add_elem(new Captain());
        stopnie.add_elem(new Lieutenant());
        stopnie.add_elem(new General());
        stopnie.add_elem(new Private());
        stopnie.add_elem(new Corporal());
        System.out.println(stopnie.to_string());
        System.out.println(stopnie.get_first_elem());
    }    
}
