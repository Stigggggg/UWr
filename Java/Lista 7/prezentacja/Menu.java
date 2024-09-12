package prezentacja;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import javax.swing.Box;
import javax.swing.ButtonGroup;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.KeyStroke;
import gra.Gra;
public class Menu extends JMenuBar
{
	private static final long serialVersionUID=1L;
	boolean eur;
	Okno okno;
	public Menu(Okno okno)
	{
		this.okno=okno;
		JMenuBar menuBar;
		JMenu menu;
		JMenuItem menuItem;
		JRadioButtonMenuItem rbMenuItem;		
		menuBar=this;
		menu=new JMenu("Gra");
		menu.setMnemonic(KeyEvent.VK_G);
		menu.getAccessibleContext().setAccessibleDescription("Menu gry");
		menuBar.add(menu);
		menuItem=new JMenuItem("Nowa gra",KeyEvent.VK_N);
		menuItem.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				okno.nowaGra(new Gra(eur));
			}
		});
		menu.add(menuItem);
		menuItem=new JMenuItem("Wyjdź");
		menuItem.setMnemonic(KeyEvent.VK_W);
		menuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.zapisGry();
				okno.dispose();
			}
		});
		menu.add(menuItem);
		menu=new JMenu("Ruchy");
		menu.setMnemonic(KeyEvent.VK_R);
		menu.getAccessibleContext().setAccessibleDescription("Menu ruchów");
		menuBar.add(menu);
		menuItem=new JMenuItem("Wybierz pole",KeyEvent.VK_Y);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_E,ActionEvent.ALT_MASK));
		menuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.click(okno.plansza.x,okno.plansza.y);
			}
		});
		menu.add(menuItem);
		menu.addSeparator();
		menuItem = new JMenuItem("Pole do góry",KeyEvent.VK_W);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_W,ActionEvent.ALT_MASK));
		menuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.y--;
				okno.plansza.repaint();
			}
		});
		menu.add(menuItem);
		menuItem=new JMenuItem("Pole po lewej",KeyEvent.VK_A);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A,ActionEvent.ALT_MASK));
		menuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.x--;
				okno.plansza.repaint();
			}
		});
		menu.add(menuItem);
		menuItem=new JMenuItem("Pole do dołu",KeyEvent.VK_S);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, ActionEvent.ALT_MASK));
		menuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.y++;
				okno.plansza.repaint();
			}
		});
		menu.add(menuItem);
		menuItem=new JMenuItem("Pole po prawej",KeyEvent.VK_D);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_D,ActionEvent.ALT_MASK));
		menuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.x++;
				okno.plansza.repaint();
			}
		});
		menu.add(menuItem);
		menu=new JMenu("Ustawienia");
		menu.setMnemonic(KeyEvent.VK_U);
		menu.getAccessibleContext().setAccessibleDescription("Menu ustawień");
		menuBar.add(menu);
		ButtonGroup group=new ButtonGroup();
		rbMenuItem=new JRadioButtonMenuItem("Wersja brytyjska");
		rbMenuItem.setSelected(true);
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				eur=false;
			}
		});
		group.add(rbMenuItem);
		menu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Wersja europejska");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				eur=true;
			}
		});
		group.add(rbMenuItem);
		menu.add(rbMenuItem);
		menu.addSeparator();
		JMenu submenu=new JMenu("Kolor tła");
		ButtonGroup subgroup=new ButtonGroup();
		rbMenuItem=new JRadioButtonMenuItem("Czarny");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.background=Color.BLACK;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Czerwony");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.background=Color.RED;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Niebieski");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.background=Color.BLUE;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Żółty");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.background=Color.YELLOW;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Zielony");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.background=Color.GREEN;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Jasno-szary");
		rbMenuItem.setSelected(true);
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.background=Color.LIGHT_GRAY;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		menu.add(submenu);
		submenu=new JMenu("Kolor kołków");
		subgroup=new ButtonGroup();
		rbMenuItem=new JRadioButtonMenuItem("Czarny");
		rbMenuItem.setSelected(true);
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.peg=Color.BLACK;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Czerwony");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.peg = Color.RED;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Niebieski");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.peg=Color.BLUE;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Żółty");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.peg=Color.YELLOW;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Zielony");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.peg = Color.GREEN;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Biały");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent arg0){
				okno.plansza.peg=Color.WHITE;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);menu.add(Box.createHorizontalGlue());
		submenu.add(rbMenuItem);
		menu.add(submenu);
		submenu=new JMenu("Kolor pustych pól");
		subgroup=new ButtonGroup();
		rbMenuItem=new JRadioButtonMenuItem("Czarny");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.empty=Color.BLACK;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Czerwony");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.empty=Color.RED;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Niebieski");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.empty=Color.BLUE;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Żółty");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.empty=Color.YELLOW;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Zielony");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.empty=Color.GREEN;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Biały");
		rbMenuItem.setSelected(true);
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.empty=Color.WHITE;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		menu.add(submenu);
		submenu = new JMenu("Kolor zaznaczenia");
		subgroup = new ButtonGroup();
		rbMenuItem=new JRadioButtonMenuItem("Czarny");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.selected=Color.BLACK;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Czerwony");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.selected=Color.RED;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Niebieski");
		rbMenuItem.setSelected(true);
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.selected=Color.BLUE;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Żółty");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.selected=Color.YELLOW;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Zielony");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.selected=Color.GREEN;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		rbMenuItem=new JRadioButtonMenuItem("Biały");
		rbMenuItem.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				okno.plansza.selected=Color.WHITE;
				okno.plansza.repaint();
			}
		});
		subgroup.add(rbMenuItem);
		submenu.add(rbMenuItem);
		menu.add(submenu);
		menu.add(Box.createHorizontalGlue());
		menu.add(menuItem);
		okno.setJMenuBar(this);
		setVisible(true);
	}
}