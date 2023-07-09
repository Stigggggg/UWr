#include<iostream>
#include<cstdint>
#include<string>

class tab_bit
{
    typedef uint64_t slowo; //element tablicy
    static const int rozmiarslowa=sizeof(slowo)*8;//rozmiar elementu
    friend std::istream& operator>>(std::istream& we, const tab_bit& tb);
    friend std::ostream& operator<<(std::ostream& wy, const tab_bit& tb);
    class ref //pomocnicza klasa ref
    {
        friend class tab_bit;
        tab_bit& tablica;
        int indeks;
        ref(tab_bit& tb, int i): tablica(tb), indeks(i){}
        public:
            operator bool() const;
            ref& operator=(bool b);
            ref& operator=(const ref& r);
    };
    protected:
        int dl; //liczba bitow
        slowo *tab; //tablica bitow
    public:
        explicit tab_bit(int rozm); //wyzerowana tablica bitow [0,...,rozm]
        explicit tab_bit(slowo tb); //tablica bitow [0,...,rozmiarSlowa], zainicjowana wzorcem
        explicit tab_bit(initializer_list<bool> l);
        tab_bit(const tab_bit& tb); //konstruktor kopiujacy
        tab_bit(tab_bit&& tb); //konstruktor przenoszacy
        tab_bit& operator=(const tab_bit& tb); //przypisanie kopiujace
        tab_bit& operator=(tab_bit&& tb); //przypisanie przenoszace
        ~tab_bit(); //destruktor
    private:
        bool czytaj(int i) const; //funkcja pomocnicza do odczytu bitu
        bool pisz(int i, bool b); //funkcja pomocnicza do zapisu bitu
    public:
        bool operator[](int i) const; //indeksowanie dla stalych tablic
        ref operator[](int i); //indeksowanie dla zwyklych tablic bitow
        inline int rozmiar() const; //rozmiar tablicy w bitach
    public:
        //wszystkie operatory
        tab_bit operator|(const tab_bit &tb) const;
        tab_bit operator&(const tab_bit &tb) const;
        tab_bit operator^(const tab_bit &tb) const;
        tab_bit& operator|=(const tab_bit &tb);
        tab_bit& operator&=(const tab_bit &tb);
        tab_bit& operator^=(const tab_bit &tb);
        tab_bit operator!() const;
    public: 
        //zaprzyjaznione operatory wejscia i wyjscia
        friend std::istream& operator>>(std::istream& we, tab_bit& tb);
        friend std::ostream& operator<<(std::ostream& wy, const tab_bit& tb);
}; 

