import argparse
from sqlalchemy import create_engine, Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship

"""Stworzenie bazy"""
Base = declarative_base()

"""Klasa Osoba z polami id, imieniem, mailem i statusem"""
class Osoba(Base):
    __tablename__ = "osoby"
    id = Column(Integer, primary_key=True)
    imie = Column(String, nullable=False)
    email = Column(String, nullable=False, unique=True)
    pozyczone = relationship("Ksiazka", back_populates="wlasciciel")

"""Klasa Ksiazka z polami id, tytulem, autorem, rokiem wydania i danych wlasciciela"""
class Ksiazka(Base):
    __tablename__ = "ksiazki"
    id = Column(Integer, primary_key=True)
    tytul = Column(String, nullable=False)
    autor = Column(String, nullable=False)
    rok = Column(Integer, nullable=False)
    kto_pozyczyl = Column(Integer, ForeignKey("osoby.id"))
    wlasciciel = relationship("Osoba", back_populates="pozyczone")

"""Tworzymy baze danych"""
engine = create_engine('sqlite:///baza_danych.db')
Base.metadata.create_all(engine)
Session = sessionmaker(bind=engine)
session = Session()

"""Funkcja dodajaca ksiazke do bazy"""
def dodaj(tytul, autor, rok):
    nowa_ksiazka = Ksiazka(tytul=tytul, autor=autor, rok=rok)
    session.add(nowa_ksiazka)
    session.commit()
    print(f'Dodano nową książkę: {tytul} - {autor} ({rok})')

"""Funkcja wypozyczajaca ksiazke osobie"""
def wypozycz(email, tytul):
    znajomy = session.query(Osoba).filter_by(email=email).first()
    if znajomy:
        ksiazka = session.query(Ksiazka).filter_by(
            tytul=tytul, kto_pozyczyl=None).first()
        if ksiazka:
            ksiazka.wlasciciel = znajomy
            session.commit()
            print(f'Wypożyczono książkę "{tytul}" znajomemu {znajomy.imie}')
        else:
            print(f'Książka "{tytul}" jest już wypożyczona')
    else:
        print(f'Nie znaleziono znajomego o emailu {email}')

"""Funkcja sluzaca do oddawania ksiazek"""
def oddaj(tytul):
    ksiazka = session.query(Ksiazka).filter_by(tytul=tytul).first()
    if ksiazka:
        if ksiazka.wlasciciel:
            print(
                f'Oddano książkę "{tytul}" od znajomego {ksiazka.wlasciciel.imie}')
            ksiazka.wlasciciel = None
            session.commit()
        else:
            print(f'Książka "{tytul}" nie jest wypożyczona')
    else:
        print(f'Nie znaleziono książki o tytule {tytul}')

"""Parser argumentow"""
def main():
    parser = argparse.ArgumentParser(
        description='Zarządzanie książkami i wypożyczaniem')
    subparsers = parser.add_subparsers(
        dest='command', help='Dostępne polecenia')
    parser_dodaj = subparsers.add_parser('dodaj', help='Dodaj nową książkę')
    parser_dodaj.add_argument('--tytul', required=True, help='Tytuł książki')
    parser_dodaj.add_argument('--autor', required=True, help='Autor książki')
    parser_dodaj.add_argument(
        '--rok',
        required=True,
        type=int,
        help='Rok wydania książki')
    parser_wypozycz = subparsers.add_parser(
        'wypozycz', help='Wypożycz książkę')
    parser_wypozycz.add_argument(
        '--email',
        required=True,
        help='Email znajomego')
    parser_wypozycz.add_argument(
        '--tytul',
        required=True,
        help='Tytuł książki')
    parser_oddaj = subparsers.add_parser('oddaj', help='Oddaj książkę')
    parser_oddaj.add_argument('--tytul', required=True, help='Tytuł książki')
    args = parser.parse_args()
    if args.command == 'dodaj':
        dodaj(args.tytul, args.autor, args.rok)
    elif args.command == 'wypozycz':
        wypozycz(args.email, args.tytul)
    elif args.command == 'oddaj':
        oddaj(args.tytul)
    else:
        print('Nieznane polecenie')


if __name__ == '__main__':
    main()
