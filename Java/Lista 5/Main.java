import java.util.logging.*;
import java.io.IOException;
import prezentacja.*;

public class Main 
{
    public static void main(String[] args)
    {
        Okno o=new Okno();
        o.setVisible(true);
        FileHandler f;
        try
        {
            f=new FileHandler("rozgrywka.log",true);
            Okno.log.addHandler(f);
            SimpleFormatter form=new SimpleFormatter();
            f.setFormatter(form);
            Okno.log.info("Log uruchomiony");
        }
        catch(SecurityException | IOException e)
        {
            e.printStackTrace();
        }
    }
}
