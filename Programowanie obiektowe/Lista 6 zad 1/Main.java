import java.io.*;

public class Main 
{
    public static void main(String[] args) 
    {
        Lista lista = new Lista();
        lista.add(1);
        lista.add(2);
        lista.add(3);
        try 
        {
            FileOutputStream wyjscie = new FileOutputStream("plik.txt");
            ObjectOutputStream wy = new ObjectOutputStream(wyjscie);
            wy.writeObject(lista);
            wy.close();
            wyjscie.close();
            System.out.println("Zapisano do pliku");
        } 
        catch (IOException i) 
        {
            i.printStackTrace();
        }
        Lista nowa_lista=null;
        try 
        {
            FileInputStream wejscie = new FileInputStream("plik.txt");
            ObjectInputStream we = new ObjectInputStream(wejscie);
            nowa_lista=(Lista) we.readObject();
            we.close();
            wejscie.close();
        } 
        catch (IOException i) 
        {
            i.printStackTrace();
            return;
        } 
        catch (ClassNotFoundException c) 
        {
            System.out.println("Blad klasy");
            c.printStackTrace();
            return;
        }
        System.out.println("Lista:");
        for (int i = 0; i < nowa_lista.size(); i++) 
        {
            System.out.println(nowa_lista.get(i));
        }
    }
}
