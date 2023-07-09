#include<iostream>
#include<stdexcept>
#include"piksele.hpp"
using namespace std;

int main()
{
    kolor k1=kolor(); 
    kolortransparentny k2(255,0,0,255); 
    kolornazwany k3(0,255,0,"zielony"); 
    kolornt k4(0,0,0,0,"czarny");
    piksel p1(400,300);
    pikselkolorowy p2(400,0,255,0,0,255); 
    cout<<"Czarny na czerwony"<<endl;
    cout<<"Kolory: r="<<k1.get_r()<<" g="<<k1.get_g()<<" b="<<k1.get_b()<<endl;
    k1.set_r(255);
    cout<<"Po zmianie: r="<<k1.get_r()<<" g="<<k1.get_g()<<" b="<<k1.get_b()<<endl;
    cout<<"Z czerwonego mocnego na czarny przezroczysty: "<<endl;
    cout<<"Kolory: r="<<k2.get_r()<<" g="<<k2.get_g()<<" b="<<k2.get_b()<<" Alfa="<<k2.get_alfa()<<endl;
    k2.set_alfa(0);
    k2.set_r(0);
    cout<<"Po zmianie: r="<<k2.get_r()<<" g="<<k2.get_g()<<" b="<<k2.get_b()<<" Alfa="<<k2.get_alfa()<<endl;
    cout<<"Z zielonego na niebieski + zmiana nazwy:"<<endl;
    cout<<"Kolory: r="<<k3.get_r()<<" g="<<k3.get_g()<<" b="<<k3.get_b()<<" Nazwa: "<<k3.get_nazwa()<<endl;
    k3.set_nazwa("niebieski");
    k3.set_b(255);
    k3.set_g(0);
    cout<<"Po zmianie: r="<<k3.get_r()<<" g="<<k3.get_g()<<" b="<<k3.get_b()<<" Nazwa: "<<k3.get_nazwa()<<endl;
    cout<<"Kolory: r="<<k4.get_r()<<" g="<<k4.get_g()<<" b="<<k4.get_b()<<" Nazwa: "<<k4.get_nazwa()<<" Alfa: "<<k4.get_alfa()<<endl;
    k4.set_alfa(56);
    k4.set_r(255);
    k4.set_nazwa("czerwony");
    cout<<"Po zmianie: r="<<k4.get_r()<<" g="<<k4.get_g()<<" b="<<k4.get_b()<<" Nazwa: "<<k4.get_nazwa()<<" Alfa: "<<k4.get_alfa()<<endl;
    cout<<"Odleglosc od gory: "<<p1.odleglosc_g()<<endl;
    cout<<"Odleglosc od dolu: "<<p1.odleglosc_d()<<endl;
    cout<<"Odleglosc od lewej: "<<p1.odleglosc_l()<<endl;
    cout<<"Odleglosc od prawej: "<<p1.odleglosc_r()<<endl;
    cout<<"Odleglosc miedzy p1 i p2: "<<odleglosc(p1,p2)<<endl;
    p2.przesun(0,200);
    cout<<"Odleglosc miedzy p1 i p2 po przesunieciu: "<<odleglosc(p1,p2)<<endl;
    cout<<"Kolory piksela p2 oraz alfa: "<<p2.get_kolor()<<endl;
    cout<<"Testy errorow: "<<endl;
    p2.przesun(500,500);
    k1.set_b(256);
    k3.set_nazwa("Biały");
    k2.set_alfa(256);
    return 0;
}