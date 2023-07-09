import java.io.*;
import javax.swing.*;
import java.awt.*;
import static javax.swing.JOptionPane.showMessageDialog;

public class KsiazkaEditor
{
    JPanel addKPanel;
    public KsiazkaEditor(Ksiazka k) 
    {
        addKPanel=new JPanel();
        addKPanel.setLayout(new GridLayout(4, 2));
        JLabel tytulLabel=new JLabel("Tytul");
        JLabel autorLabel=new JLabel("Autor");
        JLabel rokWydaniaLabel=new JLabel("Rok wydania");
        JTextField tytulField = new JTextField();
        tytulField.setText(k.get_tytul());
        JTextField autorField=new JTextField();
        autorField.setText(k.get_autor());
        JTextField rokWydaniaField=new JTextField();
        rokWydaniaField.setText(String.valueOf(k.get_rok()));
        JButton saveKButton=new JButton("Zapisz ksiazke");
        addKPanel.add(tytulLabel);
        addKPanel.add(tytulField);
        addKPanel.add(autorLabel);
        addKPanel.add(autorField);
        addKPanel.add(rokWydaniaLabel);
        addKPanel.add(rokWydaniaField);
        addKPanel.add(saveKButton);
        saveKButton.addActionListener(e->{
            k.set_tytul(tytulField.getText());
            k.set_autor(autorField.getText());
            k.set_rok(Integer.parseInt(rokWydaniaField.getText()));
            try 
            {
                FileOutputStream fileOut = new FileOutputStream("ksiazka.ser");
                ObjectOutputStream out = new ObjectOutputStream(fileOut);
                out.writeObject(k);
                out.close();
                fileOut.close();
                showMessageDialog(null,"Zapisano ksiazke");
            } 
            catch(IOException x) 
            {
                showMessageDialog(null,"Blad zapisu");
                x.printStackTrace();
            }
            Main.okno.setContentPane(Main.menu);
        });
    }
}
