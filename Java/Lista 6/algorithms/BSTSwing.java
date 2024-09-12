package algorithms;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class BSTSwing extends JFrame 
{
    private BST<String> bst;
    private JTextArea outpuTextArea;
    private BSTPanel bstPanel;
    public BSTSwing()
    {
        super("Drzewo BST");
        bst=new BST<>();
        setupUI();
    }    
    private void setupUI()
    {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(800,600);
        JPanel mainPanel=new JPanel(new BorderLayout());
        JPanel inputPanel=new JPanel();
        JTextField inputField=new JTextField(20);
        JButton insertButton=new JButton("Wstaw");
        JButton removeButton=new JButton("Usuń");
        inputPanel.add(new JLabel("Wartość:"));
        inputPanel.add(inputField);
        inputPanel.add(insertButton);
        inputPanel.add(removeButton);
        outpuTextArea=new JTextArea();
        bstPanel=new BSTPanel(bst);
        mainPanel.add(inputPanel,BorderLayout.NORTH);
        mainPanel.add(bstPanel,BorderLayout.CENTER);
        insertButton.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent e)
            {
                String value=inputField.getText();
                bst.insert(value);
                update();
            }
        });
        removeButton.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent e)
            {
                String value=inputField.getText();
                bst.remove(value);
                update();
            }
        });
        getContentPane().add(mainPanel);
        setVisible(true);
    }
    private void update()
    {
        outpuTextArea.setText("BST: "+bst.toString());
        bstPanel.repaint();
    }
    public static void main(String[] args)
    {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new BSTSwing();
            }
        });
    }
}
