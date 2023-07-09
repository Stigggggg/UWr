#include<iostream>
using namespace std;

namespace obliczenia
{
    class wyjatek_wymierny: public logic_error
    {
        public:
            wyjatek_wymierny(const string &err): logic_error(err) {}
    };
    class przekroczenie_zakresu: public wyjatek_wymierny
    {
        public:
            przekroczenie_zakresu(const string &err): wyjatek_wymierny(err) {}
    };
    class dzielenie_przez_0: public wyjatek_wymierny
    {
        public:
            dzielenie_przez_0(const string &err): wyjatek_wymierny(err) {}
    };
    class wymierna
    {
        private:
            int licz;
            int mian;
        public:
            wymierna(int l, int m);
            wymierna(int l);
            wymierna();
            wymierna(const wymierna& other)=default;
            wymierna &operator=(const wymierna &other)=default;
            int get_licz() const;
            int get_mian() const;
            wymierna operator-() const;
            wymierna operator!() const;
            wymierna operator+(const wymierna &w);
            wymierna operator-(const wymierna &w);
            wymierna operator*(const wymierna &w);
            wymierna operator/(const wymierna &w);
            operator double();
            explicit operator int();
            // friend ostream &operator<<(ostream &wyj, const wymierna &w);
    };
    ostream &operator<<(ostream &wyj, const wymierna &w);
}
