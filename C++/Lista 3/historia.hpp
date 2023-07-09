#ifndef HISTORIA_HPP
#define HISTORIA_HPP

class Liczba
{
    private:
        double val;
        double *hist;
        int size;
        int ind;
        static const int max_size=3;
    public:
        Liczba(double x); //konstruktor domyslny
        Liczba(); //konstruktor bezparametrowy/delegatowy
        Liczba(const Liczba& l); //konstruktor kopiujacy
        Liczba(Liczba&& l); //konstruktor przenoszacy
        const Liczba& operator=(const Liczba& l); //przypisanie kopiujace
        const Liczba& operator=(Liczba&& l); //przypisanie przenoszace
        ~Liczba(); //destruktor
    public:
        double get_val(); 
        void set_val(double x);
        double undo_val();
};

#endif //HISTORIA_HPP