import java.util.Scanner;

class RokUrodzenia
{
    public static String[] rzymskie={"M", "CM", "D", "CD", "C","XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    public static int[] arabskie={1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    public static String rzymska(int x)
    {
        int n=2023-x;
        if(n<=0 || n>=4000)
        {
            throw new IllegalArgumentException("Liczba "+n+" spoza zakresu 1-3999");
        }
        String s=""; //stringbuilder
        int i=0;
        while(n>0)
        {
            if(n>=arabskie[i])
            {
                s+=rzymskie[i];
                n-=arabskie[i];
            }
            else
            {
                i++;
            }
        }
        return s;
    }
    public static String patron(int n)
    {
        String[] patroni={"szczur","bawół","tygrys","królik","smok","wąż","koń","owca","małpa","kurczak","pies","świnia"};
        int reszta=(2023-n)%12;
        String patron;
        switch(reszta)
        {
            case 0 -> patron=patroni[8];
            case 1 -> patron=patroni[9];
            case 2 -> patron=patroni[10];
            case 3 -> patron=patroni[11];
            case 4 -> patron=patroni[0];
            case 5 -> patron=patroni[1];
            case 6 -> patron=patroni[2];
            case 7 -> patron=patroni[3];
            case 8 -> patron=patroni[4];
            case 9 -> patron=patroni[5];
            case 10 -> patron=patroni[6];
            case 11 -> patron=patroni[7];
            default -> patron="brak";
        }
        return patron;
    }
    public static void main(String args[])
    {
        Scanner s=new Scanner(System.in,"cp852");
        System.out.println("Podaj swoje imię:");
        String imie=s.nextLine();
        System.out.println("Podaj swój wiek: ");
        int wiek=s.nextInt();
        System.out.println("Cześć "+imie+"!");
        System.out.println("Twój rok urodzenia zapisany cyframi rzymskimi: "+rzymska(wiek));
        System.out.println("Twój patron wg chińskiego kalendarza to: "+patron(wiek));
        s.close();
    }
}