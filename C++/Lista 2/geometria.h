#include<iostream>
#include<cmath>
#include<stdexcept>
using namespace std;

class wektor
{
    private:
        double dx,dy;
    public:
        wektor(double x, double y) : dx(x),dy(y){} //zwykly konstruktor
        double get_x()
        {
            return dx;
        }
        double get_y()
        {
            return dy;
        }
        void set_x(double x)
        {
            this->dx=x;
        }
        void set_y(double y)
        {
            this->dy=y;
        }
};

class prosta
{
    private:
        double a,b,c;
    public:
        prosta(double _a, double _b, double _c) : a(_a),b(_b),c(_c){}
        double get_a()
        {
            return a;
        }
        double get_b()
        {
            return b;
        }
        double get_c()
        {
            return c;
        }
        void set_a(double _a)
        {
            this->a=_a;
        }
        void set_b(double _b)
        {
            this->b=_b;
        }
        void set_c(double _c)
        {
            this->c=_c;
        }
};

class punkt
{
    private:
        double x,y;
    public:
        punkt(double _x, double _y) : x(_x),y(_y){} //zwykly konstruktor
        double get_x()
        {
            return x;
        }
        double get_y()
        {
            return y;
        }
        void set_x(double _x)
        {
            this->x=_x;
        }
        void set_y(double _y)
        {
            this->y=_y;
        }
        void przesun(wektor v);
        void obroc(punkt pkt, double kat);
        void symetria_punkt(punkt p);
        void symetria_prosta(prosta p);
};

double odl(punkt p1, punkt p2);

class odcinek
{
    private:
        punkt p1,p2;
    public:
        odcinek(punkt _p1, punkt _p2) : p1(_p1),p2(_p2){
            if(p1.get_x()==p2.get_x() && p1.get_y()==p2.get_y())
            {
                throw invalid_argument("Nie mozna utworzyc odcinka o dlugosci 0");
            }
        }
        punkt get_p1()
        {
            return p1;
        }
        punkt get_p2()
        {
            return p2;
        }
        void set_p1(punkt _p1)
        {
            this->p1=_p1;
        }
        void set_p2(punkt _p2)
        {
            this->p2=_p2;
        }
        void przesun_odc(wektor v);
        void obroc_odc(punkt p, double kat);
        void symetria_punkt_odc(punkt p);
        void symetria_prosta_odc(prosta p);
        double dl_odc();
        bool czy_w_odc(punkt p);
};

bool prostopadle(odcinek o1, odcinek o2); 

bool rownolegle(odcinek o1, odcinek o2);

class trojkat
{
    private:
        punkt p1,p2,p3;
    public:
        trojkat(punkt _p1, punkt _p2, punkt _p3) : p1(_p1),p2(_p2),p3(_p3){
            odcinek o1(p1,p2);
            odcinek o2(p2,p3);
            odcinek o3(p3,p1);
            if(max(max(o1.dl_odc(),o2.dl_odc()),o3.dl_odc())>o1.dl_odc()+o2.dl_odc()+o3.dl_odc()-max(max(o1.dl_odc(),o2.dl_odc()),o3.dl_odc()))
            {
                throw invalid_argument("Nie mozna skonstruowac trojkata.");
            }
            else if ((p2.get_x()-p1.get_x())*(p3.get_y()-p1.get_y())==(p2.get_y()-p1.get_y())*(p3.get_x()-p1.get_x()))
            {
                if(!(((p2.get_x()-p1.get_x())*(p3.get_y()-p1.get_y())==0 || (p2.get_x()-p1.get_x())*(p3.get_y()-p1.get_y())==-0) && (p2.get_y()-p1.get_y())*(p3.get_x()-p1.get_x())==0 || (p2.get_y()-p1.get_y())*(p3.get_x()-p1.get_x())==-0))
                {
                    throw invalid_argument("Nie mozna skonstruowac trojkata");
                }
            }
        }
        punkt get_p1()
        {
            return p1;
        }
        punkt get_p2()
        {
            return p2;
        }
        punkt get_p3()
        {
            return p3;
        }
        void set_p1(punkt _p1)
        {
            this->p1=_p1;
        }
        void set_p2(punkt _p2)
        {
            this->p2=_p2;
        }
        void set_p3(punkt _p3)
        {
            this->p3=_p3;
        }
        void przesun_troj(wektor v);
        void obroc_troj(punkt p, double kat);
        void symetria_punkt_troj(punkt p);
        void symetria_prosta_troj(prosta p);
        double obwod();
        double pole();
        bool czy_wewnatrz(punkt p);
};

bool czy_rozlaczne(trojkat t1, trojkat t2);

bool czy_sie_zawiera(trojkat t1, trojkat t2);