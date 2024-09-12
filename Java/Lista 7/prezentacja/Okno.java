package prezentacja;

import java.awt.BorderLayout;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import javax.swing.JFrame;
import javax.swing.JLabel;
import gra.Gra;

public class Okno extends JFrame
{
	private static final long serialVersionUID=1L;	
	protected Gra gra;
	protected Menu menu;
	protected Plansza plansza;
	protected JLabel stan;
	int x=-1;
	int y=-1;
	private class Kill extends WindowAdapter
    {
        @Override
        public void windowClosing (WindowEvent ev)
        {
        	zapisGry();
            Okno.this.dispose();
        }
    };
	public Okno()
	{
		super("Peg solitaire");
        setSize(500,350);
        setLocationRelativeTo(null);  
		getContentPane().setLayout(new BorderLayout());
		menu=new Menu(this);
		plansza=new Plansza(this);
		stan=new JLabel("Gra jeszcze się nie rozpoczęłą");
		getContentPane().add(plansza, BorderLayout.CENTER);
		getContentPane().add(stan, BorderLayout.SOUTH);
		addWindowListener(new Kill());
		setVisible(true);
		gra=wczytanieGry();
		update();
	}
	public void nowaGra(Gra gra)
	{
		this.gra=gra;
		update();
	}
	void zapisGry()
	{
		try
		{
			File file=new File("solitaire.ser");
	        if (!file.exists()) 
			{
	            file.createNewFile();
	        }
			ObjectOutputStream objectOutputStream=new ObjectOutputStream(new FileOutputStream("solitaire.ser"));
	        objectOutputStream.writeObject(gra);
	        objectOutputStream.close();
		}
        catch(IOException e)
		{
        	System.out.println("Nie udało się zapisać pliku: "+e.getMessage());
		}
	}
	private Gra wczytanieGry()
	{
		try
		{
			ObjectInputStream objectInputStream=new ObjectInputStream(new FileInputStream("solitaire.ser"));
            Gra temp=(Gra)objectInputStream.readObject();
            File file=new File("solitaire.ser");
            if (!file.exists())
			{
                file.createNewFile();
            }
            objectInputStream.close();
            return temp;
        }
		catch(IOException e)
		{
			System.out.println("Nie udało się zapisać pliku: "+e.getMessage());
			return null;
		}
		catch(ClassNotFoundException e)
		{
			System.out.println("To się nie powinno wydarzyć");
			e.printStackTrace();
			return null;	
		}
	}
	void update()
	{
		stan.setText(gra.opis());
		plansza.rysuj(gra.stan());
	}
	void ruch(int x, int y)
	{
		if(gra==null) return;
		if(gra.ruch(this.x,this.y,x,y)==0)
		{
			this.x=-1;
			this.y=-1;
		}
		else
		{
			this.x=x;
			this.y=y;
		}
		update();
	}
}