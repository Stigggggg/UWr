package prezentacja;

import java.awt.*;
import java.awt.event.*;
import obliczenia.*;
import rozgrywka.*;
import java.util.logging.*;

public class Okno extends Frame 
{
    private TextField licznik,mianownik,wyswietlacz;
    private Button propozycja,przerwij,nowa_gra,zakoncz;
    private Scrollbar proby,zakres;
    private Gra gra;
    private Label opis,licznikLabel,mianownikLabel,wyswietlaczLabel,zakresLabel,probyLabel,goraLabel,dolLabel;
    private Wymierna dolna_granica, gorna_granica;
    public static Logger log=Logger.getLogger("MyLog");
    public Okno()
    {
        super("Odgadywanie liczb wymiernych");
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent we) 
            {
                log.log(Level.INFO,"Aplikacja została zamknięta");
                System.exit(0);
            }
        });
        setSize(600,400);
        setLayout(null);
        nowa_gra=new Button("Rozpocznij gre");
        nowa_gra.setBounds(240,250,100,30);
        add(nowa_gra);
        nowa_gra.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent ae)
            {
                rozpocznij_nowa_gre();
            }
        });
        przerwij=new Button("Przerwij gre");
        przerwij.setBounds(360,250,100,30);
        add(przerwij);
        przerwij.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent ae)
            {
                gra.rezygnuj();
                handle("Rezygnacja");
                wyswietlacz.setText("Poddales sie. Jeszcze raz?");
                log.log(Level.INFO,"Gracz się poddał");
            }
        });
        zakoncz=new Button("Zakoncz");
        zakoncz.setBounds(480,250,100,30);
        add(zakoncz);
        zakoncz.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent ae)
            {
                log.log(Level.INFO,"Aplikacja została zamknięta");
                System.exit(0);
            }
        });
        opis=new Label("Odgadywanie liczb wymiernych");
        opis.setBounds(50,50,500,20);
        add(opis);
        licznikLabel=new Label("Licznik");
        licznikLabel.setBounds(50,80,70,20);
        add(licznikLabel);
        licznik=new TextField("",10);
        licznik.setBounds(50,100,70,20);
        add(licznik);
        mianownikLabel=new Label("Mianownik");
        mianownikLabel.setBounds(140,80,70,20);
        add(mianownikLabel);
        mianownik=new TextField("",10);
        mianownik.setBounds(140,100,70,20);
        add(mianownik);
        wyswietlaczLabel=new Label("Stan gry:");
        wyswietlaczLabel.setBounds(245,80,70,20);
        add(wyswietlaczLabel);
        wyswietlacz=new TextField("Wybierz zakres i rozpocznij grę", 10);
        wyswietlacz.setBounds(245,100,300,20);
        add(wyswietlacz);
        wyswietlacz.setEditable(false);
        propozycja=new Button("Liczba:");
        propozycja.setBounds(50,130,160,40);
        add(propozycja);
        propozycja.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent ae) {
                obsluga_propozycji();
            }
        });
        goraLabel=new Label("Odgadniety górny limit");
        goraLabel.setBounds(50,180,200,20);
        add(goraLabel);
        dolLabel=new Label("Odgadniety dolny limit");
        dolLabel.setBounds(50,200,200,20);
        add(dolLabel);
        zakresLabel=new Label("Zakres - gorna granica (5-20):");
        zakresLabel.setBounds(245,130,250,20);
        add(zakresLabel);
        zakres=new Scrollbar(Scrollbar.HORIZONTAL,12,1,5,20);
        zakres.setBounds(245,150,300,20);
        add(zakres);
        probyLabel=new Label("Liczba prób:");
        probyLabel.setBounds(245,180,100,20);
        add(probyLabel);
        proby=new Scrollbar(Scrollbar.HORIZONTAL,0,1,0,10);
        proby.setBounds(245,200,300,20);
        add(proby);
        gra=new Gra();
        handle("Inicjalizacja");
        log.log(Level.INFO,"Uruchomiono aplikację");
    }
    private void handle(String status) 
    {
        switch(status) 
        {
            case "Inicjalizacja","Rezygnacja",
                    "Zwyciestwo","Porazka":
                licznikLabel.setEnabled(false);
                licznik.setEnabled(false);
                przerwij.setEnabled(false);
                mianownikLabel.setEnabled(false);
                mianownik.setEnabled(false);
                probyLabel.setEnabled(false);
                propozycja.setEnabled(false);
                proby.setEnabled(false);
                nowa_gra.setEnabled(true);
                zakresLabel.setFocusable(true);
                zakres.setEnabled(true);
                goraLabel.setEnabled(false);
                dolLabel.setEnabled(false);
                dolLabel.setText("Zgadnięty dolny limit");
                goraLabel.setText("Zgadnięty górny limit");
                break;
            case "Kontynuacja":
                licznikLabel.setEnabled(true);
                licznik.setEnabled(true);
                mianownikLabel.setEnabled(true);
                mianownik.setEnabled(true);
                probyLabel.setEnabled(true);
                propozycja.setEnabled(true);
                nowa_gra.setEnabled(false);
                przerwij.setEnabled(true);
                proby.setEnabled(true);
                proby.setFocusable(false);
                zakresLabel.setFocusable(false);
                zakres.setEnabled(true);
                dolLabel.setEnabled(true);
                goraLabel.setEnabled(true);
                break;
            default:
                log.log(Level.WARNING,"Stan "+status+" nie jest obsługiwany");
                throw new IllegalArgumentException("Nieobslugiwany status");
        }
    }
    private void rozpocznij_nowa_gre()
    {
        int z=zakres.getValue();
        int st=gra.start(z);
        if(st==-1)
        {
            wyswietlacz.setText("Blad losowania liczby");
        }
        else
        {
            wyswietlacz.setText("Liczba prob: "+st);
            handle("Kontynuacja");
        }
    }
    private void obsluga_propozycji()
    {
        if(gra.czy_aktywna())
        {
            try
            {
                int l=Integer.parseInt(licznik.getText());
                int m=Integer.parseInt(mianownik.getText());
                if(l>=m)
                {
                    log.log(Level.FINE,"Licznik musi być mniejszy niż mianownik");
                    wyswietlacz.setText("Licznik musi byc mniejszy niz mianownik!");
                }
                Wymierna propo=new Wymierna(l,m);
                String wynik=gra.odgadnij(propo);
                if(wynik=="Zwyciestwo")
                {
                    wyswietlacz.setText("Wygrales! Jeszcze raz?");
                    log.log(Level.INFO,"Użytkownik wygrał");
                    handle("Zwyciestwo");
                }
                else if(wynik=="Porazka")
                {
                    wyswietlacz.setText("Przegrales! Jeszcze raz?");
                    log.log(Level.INFO,"Użytkownik przegrał");
                    handle("Porazka");
                }
                else 
                {
                    int porownanie=gra.porownaj(propo);
                    if(porownanie<0)
                    {
                        wyswietlacz.setText("Zbyt mala liczba");
                        if(dolna_granica==null || dolna_granica.compareTo(propo)<0)
                        {
                            dolna_granica=propo;
                            dolLabel.setText("Dolny limit: "+dolna_granica.toString());
                        }
                    }
                    else
                    {
                        wyswietlacz.setText("Zbyt duza liczba");
                        if(gorna_granica==null || gorna_granica.compareTo(propo)>0)
                        {
                            gorna_granica=propo;
                            goraLabel.setText("Gorny limit: "+gorna_granica.toString());
                        }
                    }
                    licznik.setText("");
                    mianownik.setText("");
                    proby.setValue(gra.ile_zostalo());
                }
            }
            catch(NumberFormatException e)
            {
                log.log(Level.FINE,"Niepoprawny format liczby");
                wyswietlacz.setText("Zly format liczby!");
            }
        }
        else
        {
            log.log(Level.FINE,"Gra nie jest aktywna");
        }
    }
}
  

