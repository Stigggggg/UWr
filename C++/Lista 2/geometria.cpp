#include<iostream>
#include<cmath>
#include<stdexcept>
#include "geometria.h"
using namespace std;

void punkt::przesun(wektor v)
{
    x+=v.get_x();
    y+=v.get_y();   
}

void punkt::obroc(punkt pkt, double kat)
{
    double rad=kat*M_PI/180.0;
    double x2=(x-pkt.x)*cos(rad)-(y-pkt.y)*sin(rad)+pkt.x;
    double y2=(x-pkt.x)*sin(rad)+(y-pkt.y)*cos(rad)+pkt.y;
    x=x2;
    y=y2;
}

void punkt::symetria_punkt(punkt pkt)
{
    double x2=2*pkt.x-x;
    double y2=2*pkt.y-y;
    x=x2;
    y=y2;
}
        
void punkt::symetria_prosta(prosta p)
{
    prosta prostop(-p.get_b(), p.get_a(), p.get_b()*x-p.get_a()*y);
    punkt srodek(-((p.get_c()*prostop.get_b() - prostop.get_c()*p.get_b())/(p.get_a()*prostop.get_b() - prostop.get_a()*p.get_b())), (-(p.get_a()*prostop.get_c() - prostop.get_a()*p.get_c())/(p.get_a()*prostop.get_b() - prostop.get_a()*p.get_b())));
    if(p.get_a()*x+p.get_b()*y+p.get_c()==0)
    {
         x=x;
         y=y;
    }
    if(srodek.x==-x)
    {
        x=x;
        y=-y;
    }
    else if(srodek.y==y)
    {
        x=-x;
        y=y;
    }
    else
    {
        x=2*srodek.x-x;
        y=2*srodek.y-y;
    }
}

double odl(punkt p1, punkt p2)
{
    return sqrt((p2.get_x()-p1.get_x())*(p2.get_x()-p1.get_x())+(p2.get_y()-p1.get_y())*(p2.get_y()-p1.get_y()));
}

 
void odcinek::przesun_odc(wektor v)
{
    p1.przesun(v);
    p2.przesun(v);
}
        
void odcinek::obroc_odc(punkt p, double kat)
{
    p1.obroc(p,kat);
    p2.obroc(p,kat);
}
        
void odcinek::symetria_punkt_odc(punkt p)
{
    p1.symetria_punkt(p);
    p2.symetria_punkt(p);
}
        
void odcinek::symetria_prosta_odc(prosta p)
{
    p1.symetria_prosta(p);
    p2.symetria_prosta(p);
}
        
double odcinek::dl_odc()
{
    double dl=odl(p1,p2);
    return dl;
}
        
bool odcinek::czy_w_odc(punkt p)
{
    double eps=0.00001;
    if(p2.get_x()!=p1.get_x())
    {
        double a=(p2.get_y()-p1.get_y())/(p2.get_x()-p1.get_x());
        double b=p1.get_y()-a*p1.get_x();
        if(int (p.get_y()-a*p.get_x()-b)==0)
        {
            if((p.get_x()<=max(p1.get_x(), p2.get_x()) && p.get_x()>=min(p1.get_x(), p2.get_x())-eps) && (p.get_y()<=max(p1.get_y(),p2.get_y()) and p.get_y()>=min(p1.get_y(), p2.get_y())-eps))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        double a=0.0;
        double b=p1.get_x();
        if(p.get_y()==a*p.get_x()+b)
        {
            if(p.get_y()<=max(p1.get_y(), p2.get_y()) && p.get_y()>=min(p1.get_y(), p2.get_y()))
            {
                return true;
            }
            else
            {
                return false;
            }
        }   
        else
        {
            return false;
        }
    }
}


bool prostopadle(odcinek o1, odcinek o2) 
{
    double a1=((o1.get_p2().get_y())-(o1.get_p1().get_y()))/((o1.get_p2().get_x())-(o1.get_p1().get_x()));
    double a2=((o2.get_p2().get_y())-(o2.get_p1().get_y()))/((o2.get_p2().get_x())-(o2.get_p1().get_x()));
    double eps=0.00001;
    if(a1*a2+1<eps)
    {
        return true;
    }
    else return false;
}

bool rownolegle(odcinek o1, odcinek o2)
{
    double a1=((o1.get_p2().get_y())-(o1.get_p1().get_x()))/((o1.get_p2().get_x())-(o1.get_p1().get_x()));
    double a2=((o2.get_p2().get_y())-(o2.get_p1().get_y()))/((o2.get_p2().get_x())-(o2.get_p1().get_x()));
    double xa=o1.get_p1().get_x();
    double ya=o1.get_p1().get_y();
    double xb=o1.get_p2().get_x();
    double yb=o1.get_p2().get_y();
    double xc=o2.get_p1().get_x();
    double yc=o2.get_p1().get_y();
    double xd=o2.get_p2().get_x();
    double yd=o2.get_p2().get_y();
    if((xa==xb && xc==xd) || (ya==yb && yc==yd))
    {
        return true;
    }
    else if((xa==xb && yc==yd) || (xc==xd && ya==yb))
    {
        return true;
    }
    else if(a1==a2)
    {
        return true;
    }
    else return false;
}

void trojkat::przesun_troj(wektor v)
{
    p1.przesun(v);
    p2.przesun(v);
    p3.przesun(v);
}
void trojkat::obroc_troj(punkt p, double kat)
{
    p1.obroc(p,kat);
    p2.obroc(p,kat);
    p3.obroc(p,kat);
}
void trojkat::symetria_punkt_troj(punkt p)
{
    p1.symetria_punkt(p);
    p2.symetria_punkt(p);
    p3.symetria_punkt(p);
}

void trojkat::symetria_prosta_troj(prosta p)
{
    p1.symetria_prosta(p);
    p2.symetria_prosta(p);
    p3.symetria_prosta(p);
}

double trojkat::obwod()
{
    return odl(p1,p2)+odl(p2,p3)+odl(p3,p1);
}
        
double trojkat::pole()
{
    double a=odl(p1,p2);
    double b=odl(p2,p3);
    double c=odl(p3,p1);
    double p=(a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}
        
bool trojkat::czy_wewnatrz(punkt p)
{
    double eps=0.00001;
    trojkat t1(p,p1,p2);
    trojkat t2(p,p2,p3);
    trojkat t3(p,p3,p1);
    double po1=t1.pole();
    double po2=t2.pole();
    double po3=t3.pole();
    double po=pole();
    if(po1+po2+po3-po<eps)
    {
        return true;
    }
    return false;
}


bool czy_rozlaczne(trojkat t1, trojkat t2)
{
    punkt p=t2.get_p1();
    punkt q=t2.get_p2();
    punkt r=t2.get_p3();
    punkt a=t1.get_p1();
    punkt b=t1.get_p2();
    punkt c=t1.get_p3();
    if(t1.czy_wewnatrz(p)==true || t1.czy_wewnatrz(q)==true || t1.czy_wewnatrz(r)==true)
    {
        return false;
    }
    if(t2.czy_wewnatrz(a)==true || t2.czy_wewnatrz(b)==true || t2.czy_wewnatrz(c)==true)
    {
        return false;
    }
    return true;
}

bool czy_sie_zawiera(trojkat t1, trojkat t2)
{
    punkt p=t2.get_p1();
    punkt q=t2.get_p2();
    punkt r=t2.get_p3();
    if(t1.czy_wewnatrz(p)==false || t1.czy_wewnatrz(q)==false || t1.czy_wewnatrz(r)==false)
    {
        return false;
    }
    return true;
}
