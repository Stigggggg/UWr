#include<iostream>
#include<cmath>
#include<stdexcept>
#include "geometria.h"
using namespace std;

int main()
{
    //TESTY KLASY TROJKAT
    punkt p1(-3,0);
    punkt p2(3,0);
    punkt p3(0,3);
    punkt p4(-2,0);
    punkt p5(2,0);
    punkt p6(0,2);
    punkt p7(4,5);
    punkt p8(2,8);
    punkt p9(6,12);
    trojkat t1(p1,p2,p3);
    trojkat t2(p4,p5,p6);
    trojkat t3(p7,p8,p9);
    punkt p10(0,1);
    cout<<t1.obwod()<<" "<<t2.obwod()<<endl;
    cout<<t1.pole()<<" "<<t2.pole()<<endl;
    cout<<t1.czy_wewnatrz(p10)<<endl;
    cout<<czy_rozlaczne(t1,t3)<<endl;
    cout<<czy_rozlaczne(t1,t2)<<endl;
    cout<<czy_sie_zawiera(t1,t2)<<endl;
    cout<<czy_sie_zawiera(t2,t1)<<endl;
    cout<<czy_sie_zawiera(t1,t3)<<endl;
    return 0;
}