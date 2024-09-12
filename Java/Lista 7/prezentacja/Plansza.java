package prezentacja;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JPanel;

public class Plansza extends JPanel
{
	private static final long serialVersionUID=1L;
	String state;
	Okno okno;
	int x=-1;
	int y=-1;
	int selectedX=-1;
	int selectedY=-1;
	Color background=Color.LIGHT_GRAY;
	Color peg=Color.BLACK;
	Color selected=Color.BLUE;
	Color empty=Color.WHITE;
	public Plansza(Okno okno)
	{
		this.okno=okno;
		setLayout(new GridLayout());
		addMouseListener(new PlanszaMouseListener());
		setVisible(true);
	}
	public void rysuj(String s)
	{	
		state=s;
        repaint();
    }
	public void kursor(int x,int y)
	{
		this.x=x;
		this.y=y;
		repaint();
	}
	@Override
	protected void paintComponent(Graphics g) 
	{
		super.paintComponent(g);
		g.setColor(background);
		g.fillRect(0,0,getWidth(),getHeight());
		int cellWidth=getWidth()/7;
		int cellHeight=getHeight()/7;
		if (state!=null)
		{
			char[] chars=state.toCharArray();
			for (int row=0; row<7; row++)
			{
				for (int col=0; col<7; col++)
				{
					int x=col*cellWidth;
					int y=row*cellHeight;
					char cellValue=chars[row*7+col];
					if (cellValue=='x')
					{
						g.setColor(peg);
						g.fillOval(x,y,cellWidth,cellHeight);
					} 
					else if (cellValue=='o') 
					{
						g.setColor(empty);
						g.fillOval(x,y,cellWidth,cellHeight);
					}
				}
			}
			g.drawRect(this.x*cellWidth,this.y*cellHeight,cellWidth,cellHeight);
			g.setColor(selected);
			if(selectedY*7+selectedX>0 && chars[selectedY*7+selectedX]=='x')
			{
				g.fillOval(this.selectedX * cellWidth, this.selectedY * cellHeight, cellWidth, cellHeight);
			}
		}
	}
	private class PlanszaMouseListener extends MouseAdapter
	{
		@Override
		public void mouseClicked(MouseEvent e) 
		{
			int cellWidth=getWidth()/7;
			int cellHeight=getHeight()/7;
			x=e.getX()/cellWidth;
			y=e.getY()/cellHeight;
			click(x,y);
		}
	}
	void click(int x, int y)
	{
		selectedX=x;
		selectedY=y;
		okno.ruch(selectedX,selectedY);
		repaint();
	}
}