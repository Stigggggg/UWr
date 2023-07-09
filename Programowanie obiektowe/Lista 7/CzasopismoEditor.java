import java.io.*;
import javax.swing.*;
import java.awt.*;
import static javax.swing.JOptionPane.showMessageDialog;

public class CzasopismoEditor
{
    JPanel addCPanel;
    public CzasopismoEditor(Czasopismo c) 
    {
        addCPanel=new JPanel();
        addCPanel.setLayout(new GridLayout(5, 2));
        JLabel tytulLabel=new JLabel("Tytul");
        JLabel autorLabel=new JLabel("Autor");
        JLabel rokWydaniaLabel=new JLabel("Rok wydania");
        JLabel nrISSNLabel=new JLabel("Nr ISSN");
        JTextField tytulField = new JTextField();
        tytulField.setText(c.get_tytul());
        JTextField autorField=new JTextField();
        autorField.setText(c.get_autor());
        JTextField rokWydaniaField=new JTextField();
        rokWydaniaField.setText(String.valueOf(c.get_rok()));
        JTextField nrISSNField=new JTextField();
        nrISSNField.setText(String.valueOf(c.get_ISSN()));
        JButton saveWButton=new JButton("Zapisz czasopismo");
        addCPanel.add(tytulLabel);
        addCPanel.add(tytulField);
        addCPanel.add(autorLabel);
        addCPanel.add(autorField);
        addCPanel.add(rokWydaniaLabel);
        addCPanel.add(rokWydaniaField);
        addCPanel.add(nrISSNLabel);
        addCPanel.add(nrISSNField);
        addCPanel.add(saveWButton);
        saveWButton.addActionListener(e->{
            c.set_tytul(tytulField.getText());
            c.set_autor(autorField.getText());
            c.set_rok(Integer.parseInt(rokWydaniaField.getText()));
            c.set_ISSN(nrISSNField.getText());
            try 
            {
                FileOutputStream fileOut=new FileOutputStream("czasopismo.txt");
                ObjectOutputStream out=new ObjectOutputStream(fileOut);
                out.writeObject(c);
                out.close();
                fileOut.close();
                showMessageDialog(null,"Zapisano czasopismo");
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
