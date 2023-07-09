public class Main 
{
    public static void main(String args[])
    {
        Bufor<String> bufor=new Bufor<>(10);
        Producent p=new Producent(bufor);
        Konsument k=new Konsument(bufor);
        Thread watek_producenta=new Thread(p);
        Thread watek_konsumenta=new Thread(k);
        watek_producenta.start();
        watek_konsumenta.start();
    }
}
