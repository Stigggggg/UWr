import itertools

class VariableNotFoundException(Exception):
    pass

class Formula:
    def oblicz(self,zmienne):
        pass
    def __str__(self):
        pass
    def __add__(self,other):
        return Or(self,other)
    def __mul__(self, other):
        return And(self,other)
    def tautologia(self):
        z=self.zmienne()
        for wartosci in self.kombinacje_wartosci(z):
            if not self.oblicz(wartosci):
                return False
        return True
    def zmienne(self):
        pass
    def kombinacje_wartosci(self,zmienne):
        wartosci=[True,False]
        kombinacje=list(itertools.product(wartosci,repeat=len(zmienne)))
        return [dict(zip(zmienne,kombinacja)) for kombinacja in kombinacje]

class Zmienna(Formula):
    def __init__(self, nazwa):
        self.nazwa=nazwa
    def oblicz(self, zmienne):
        if self.nazwa in zmienne:
            return zmienne[self.nazwa]
        else:
            raise VariableNotFoundException(f"Zmienna '{self.nazwa}' nie ma przypisanej wartosci")
    def __str__(self):
        return self.nazwa
    def zmienne(self):
        return [self.nazwa]

class Stala(Formula):
    def __init__(self, wartosc):
        self.wartosc=wartosc
    def oblicz(self, zmienne):
        return self.wartosc
    def __str__(self):
        return str(self.wartosc)
    def zmienne(self):
        return []

class Not(Formula):
    def __init__(self, podformula):
        self.podformula=podformula
    def oblicz(self, zmienne):
        return not self.podformula.oblicz(zmienne)
    def __str__(self):
        return f"¬({self.podformula})"
    def zmienne(self):
        return self.podformula.zmienne()
class Or(Formula):
    def __init__(self, left, right):
        self.left=left
        self.right=right
    def oblicz(self,zmienne):
        return self.left.oblicz(zmienne) or self.right.oblicz(zmienne)
    def __str__(self):
        return f"({self.left} ∨ {self.right})"
    def zmienne(self):
        return list(set(self.left.zmienne() + self.right.zmienne()))

class And(Formula):
    def __init__(self, left, right):
        self.left=left
        self.right=right

    def oblicz(self,zmienne):
        return self.left.oblicz(zmienne) and self.right.oblicz(zmienne)
    def __str__(self):
        return f"({self.left} ∧ {self.right})"
    def zmienne(self):
        return list(set(self.left.zmienne() + self.right.zmienne()))

f=Or(Not(Zmienna("x")), And(Zmienna("y"), Stala(True)))
print(f"Formuła: {f}")
print(f"Wynik: {f.oblicz({'x': False, 'y': True})}")
print(f"Czy to tautologia? {f.tautologia()}")
