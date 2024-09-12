package gra;

import java.io.Serializable;

public class Gra implements Serializable
{
	private static final long serialVersionUID=-5894641575020688707L;
	private enum square {NULL,PEG,EMPTY};
	private square[][] state;
	private int peg_count;
	private boolean eur;
	private boolean active;
	public Gra(boolean eur)
	{
		this.eur=eur;
		state=new square[7][7];
		for(int i=0; i<7; i++)
		{
			for(int j=0; j<7; j++)
			{
				state[i][j]=square.PEG;
			}
		}
		state[0][0]=square.NULL;
		state[1][0]=square.NULL;
		state[0][1]=square.NULL;
		state[6][0]=square.NULL;
		state[5][0]=square.NULL;
		state[6][1]=square.NULL;
		state[0][6]=square.NULL;
		state[0][5]=square.NULL;
		state[1][6]=square.NULL;
		state[6][6]=square.NULL;
		state[5][6]=square.NULL;
		state[6][5]=square.NULL;
		if(!eur)
		{
			state[1][1]=square.NULL;
			state[5][1]=square.NULL;
			state[1][5]=square.NULL;
			state[5][5]=square.NULL;
			state[3][3]=square.EMPTY;
			peg_count=32;
		}
		else
		{
			state[2][3]=square.EMPTY;
			peg_count=36;
		}
	}
	public String stan()
	{
		StringBuilder s=new StringBuilder(60);
		for (square[] row: state)
		{
			for(square cell: row) 
			{
				char l;
				if(cell == square.NULL)
				{
					l=' ';
				}
				else if(cell == square.PEG)
				{ 
					l='x';
				}
				else l='o';
				s.append(l);
			}
		}
		return s.toString();
	}
	public String opis()
	{
		StringBuilder s=new StringBuilder("Pozostało: ");
		s.append(peg_count);
		if(peg_count==1 && ((eur && state[2][3]==square.PEG) || (!eur && state[3][3]==square.PEG)))
		{
			s.append(", zwycięstwo");
		}
		return s.toString();
	}
	public int ruch(int x1, int y1, int x2, int y2)
	{	
		if(!(0<=x1 && x1<7 && 0<=y1 && y1<7 && 0<=x2 && x2<7 && 0 <= y2 && y2<7))
	        return -1;
		if(state[y1][x1]!=square.PEG || state[y2][x2]!=square.EMPTY)
	        return -1;
		int x3=Math.abs(x1-x2);
		int y3=Math.abs(y1-y2);
		if(!((x3==0 && y3==2)^ (y3==0 && x3==2)))
			return -1;
		int midX=(x1+x2)/2;
		int midY=(y1+y2)/2;
		if (state[midY][midX]!=square.PEG)
			return -1;
		state[y1][x1]=square.EMPTY;
		state[y2][x2]=square.PEG;
		state[midY][midX]=square.EMPTY;
		peg_count--;
		if(peg_count==1) 
			active=false;
		return 0;
	}
	public boolean aktywna() 
	{
		return active;
	}
}