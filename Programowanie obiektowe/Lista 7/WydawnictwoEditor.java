import java.io.*;
import javax.swing.*;
import java.awt.*;
import static javax.swing.JOptionPane.showMessageDialog;

public class WydawnictwoEditor
{
    JPanel addWPanel;
    public WydawnictwoEditor(Wydawnictwo w) 
    {
        addWPanel=new JPanel();
        addWPanel.setLayout(new GridLayout(5, 2));
        JLabel tytulLabel=new JLabel("Tytul");
        JLabel autorLabel=new JLabel("Autor");
        JLabel rokWydaniaLabel=new JLabel("Rok wydania");
        JLabel nrWydaniaLabel=new JLabel("Nr wydania");
        JTextField tytulField = new JTextField();
        tytulField.setText(w.get_tytul());
        JTextField autorField=new JTextField();
        autorField.setText(w.get_autor());
        JTextField rokWydaniaField=new JTextField();
        rokWydaniaField.setText(String.valueOf(w.get_rok()));
        JTextField nrWydaniaField=new JTextField();
        nrWydaniaField.setText(String.valueOf(w.get_nr()));
        JButton saveWButton=new JButton("Zapisz wydawnictwo");
        addWPanel.add(tytulLabel);
        addWPanel.add(tytulField);
        addWPanel.add(autorLabel);
        addWPanel.add(autorField);
        addWPanel.add(rokWydaniaLabel);
        addWPanel.add(rokWydaniaField);
        addWPanel.add(nrWydaniaLabel);
        addWPanel.add(nrWydaniaField);
        addWPanel.add(saveWButton);
        saveWButton.addActionListener(e->{
            w.set_tytul(tytulField.getText());
            w.set_autor(autorField.getText());
            w.set_rok(Integer.parseInt(rokWydaniaField.getText()));
            w.set_nr(Integer.parseInt(nrWydaniaField.getText()));
            try 
            {
                FileOutputStream fileOut=new FileOutputStream("wydawnictwo.txt");
                ObjectOutputStream out=new ObjectOutputStream(fileOut);
                out.writeObject(w);
                out.close();
                fileOut.close();
                showMessageDialog(null,"Zapisano wydawnictwo");
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
