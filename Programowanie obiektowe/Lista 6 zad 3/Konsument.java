class Konsument implements Runnable
{
    Bufor<String> bufor;
    public Konsument(Bufor<String> bufor) 
    {
        this.bufor=bufor;
    }
    @Override
    public void run() 
    {
        try
        {
            while(true)
            {
                String elem=bufor.remove();
                consume(elem);
                System.out.println("Skonsumowano "+elem);
            }
        } 
        catch(InterruptedException e)
        {
            Thread.currentThread().interrupt();
            System.err.println("Konsumpcja przerwana ");
        }
    }
    void consume(String item) throws InterruptedException
    {
        Thread.sleep(1000);
    }
}  
