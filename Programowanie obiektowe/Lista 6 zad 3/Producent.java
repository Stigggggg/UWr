import java.util.Random;

class Producent implements Runnable
{
    Bufor<String> bufor;
    public Producent(Bufor<String> bufor) 
    {
        this.bufor=bufor;
    }
    public String produkcja()
    {
        Random rand=new Random();
        int dl=rand.nextInt(10)+1;
        String s="";
        for(int i=0; i<dl; i++)
        {
            s+=((char) (rand.nextInt(26)+'a'));
        }
        return s;
    }
    @Override
    public void run() 
    {
        try
        {
            while(true)
            {
                String elem=produkcja();
                bufor.add(elem);
                System.out.println("Wyprodukowano "+elem);
            }
        } 
        catch(InterruptedException e)
        {
            Thread.currentThread().interrupt();
            System.err.println("Produkcja zatrzymana");
        }
    }
}
