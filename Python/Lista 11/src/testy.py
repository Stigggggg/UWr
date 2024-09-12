import unittest
from zad1 import dodaj,wypozycz,Osoba,Ksiazka,engine,Base,Session

# Uruchamianie w PyCharm: py -m unittest testy.py
# Zwraca błędy dla dodania duplikatu i błędnych danych (tak powinno być)

class test_dodaj(unittest.TestCase):
    def setUp(self):
        Base.metadata.create_all(engine)
        self.session=Session()

    def tearDown(self):
        Base.metadata.drop_all(engine)
        self.session.close()

    def test_dodaj(self):
        dodaj("Tytuł1","Autor1",2022)
        ksiazka=self.session.query(Ksiazka).filter_by(tytul="Tytuł1").first()
        self.assertIsNone(ksiazka)
        self.assertEqual(ksiazka.tytul,"Tytuł1")

    def test_dodaj_duplikat(self):
        dodaj("Tytuł1", "Autor1", 2022)
        with self.assertRaises(Exception):
            dodaj("Tytuł1","Autor2",2022)

    def test_dodaj_zle(self):
        with self.assertRaises(Exception):
            dodaj(None,"Autor1",2022)

class test_wypozycz(unittest.TestCase):
    def setUp(self):
        Base.metadata.create_all(engine)
        self.session=Session()

    def tearDown(self):
        Base.metadata.drop_all(engine)
        self.session.close()

    def test_wypozycz(self):
        dodaj("Tytuł1", "Autor1", 2022)
        osoba=Osoba(imie="Jan",email="abc@gef.com")
        self.session.add(osoba)
        self.session.commit()
        wypozycz("abc@gef.com","Tytuł1")
        ksiazka=self.session.query(Ksiazka).filter_by(tytul="Tytuł1").first()
        self.assertIsNotNone(ksiazka.wlasciciel)
        self.assertEqual(ksiazka.wlasciciel.imie,"Jan")

    def test_wypozycz_zle(self):
        with self.assertRaises(Exception):
            wypozycz("zly@mail.com","Tytuł1")


if __name__=="_main__":
    unittest.main()

