import javax.swing.*;
import java.awt.*;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

public class Main 
{
    public static JFrame okno;
    public static JPanel menu;
    public static void main(String[] args)
    {
        okno=new JFrame();
        menu=new JPanel();
        okno.setContentPane(menu);
        okno.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        okno.setSize(400, 400);
        GridLayout layout=new GridLayout(3, 1);
        menu.setLayout(layout);
        JButton dodajKsiazke=new JButton("Edytuj ksiazke");
        JButton dodajCzasopismo=new JButton("Edytuj czasopismo");
        JButton dodajWydawnictwo=new JButton("Edytuj wydawnictwo");
        menu.add(dodajKsiazke);
        menu.add(dodajCzasopismo);
        menu.add(dodajWydawnictwo);
        okno.setVisible(true);
        dodajKsiazke.addActionListener(e -> {
            Ksiazka odczytanaKsiazka=new Ksiazka();
            try 
            {
                FileInputStream fileIn=new FileInputStream("ksiazka.ser");
                ObjectInputStream in=new ObjectInputStream(fileIn);
                odczytanaKsiazka=(Ksiazka) in.readObject();
                in.close();
                fileIn.close();
            } 
            catch(IOException | ClassNotFoundException x) 
            {
                x.printStackTrace();
            }
            KsiazkaEditor addKsiazkaEditor=new KsiazkaEditor(odczytanaKsiazka);
            okno.setContentPane(addKsiazkaEditor.addKPanel);
            okno.revalidate();
            okno.repaint();
        });
        dodajCzasopismo.addActionListener(e -> {
            Czasopismo odczytaneCZ=new Czasopismo();
            try 
            {
                FileInputStream fileIn=new FileInputStream("czasopismo.txt");
                ObjectInputStream in=new ObjectInputStream(fileIn);
                odczytaneCZ=(Czasopismo) in.readObject();
                in.close();
                fileIn.close();
            } 
            catch(IOException | ClassNotFoundException x) 
            {
                x.printStackTrace();
            }
            CzasopismoEditor addCzasopismoEditor = new CzasopismoEditor(odczytaneCZ);
            okno.setContentPane(addCzasopismoEditor.addCPanel);
            okno.revalidate();
            okno.repaint();
        });
        dodajWydawnictwo.addActionListener(e -> {
            Wydawnictwo odczytaneW=new Wydawnictwo();
            try 
            {
                FileInputStream fileIn=new FileInputStream("wydawnictwo.txt");
                ObjectInputStream in=new ObjectInputStream(fileIn);
                odczytaneW=(Wydawnictwo) in.readObject();
                in.close();
                fileIn.close();
            } 
            catch (IOException | ClassNotFoundException x) 
            {
                x.printStackTrace();
            }
            WydawnictwoEditor addWydawnictwoEditor = new WydawnictwoEditor(odczytaneW);
            okno.setContentPane(addWydawnictwoEditor.addWPanel);
            okno.revalidate();
            okno.repaint();
        });
    }
}
