from decimal import Decimal

def vat_faktura(lista):
    suma_netto = sum(lista)
    suma_netto *= 0.23
    return suma_netto
def vat_paragon(lista):
    vat = 0
    for i in lista:
        vat += i * 0.23
    return vat

zakupy = [1.2, 2.4, 3.6]

print(vat_faktura(zakupy) == vat_paragon(zakupy))

zakupy_decimal = [Decimal('1.2'), Decimal('2.4'), Decimal('3.6')]

def vat_faktura_decimal(lista):
    suma = sum(lista)
    suma *= Decimal('0.23')
    return suma

def vat_paragon_decimal(lista):
    suma = 0
    for i in lista:
        suma += i * Decimal('0.23')
    return suma

print(vat_faktura_decimal(zakupy_decimal) == vat_paragon_decimal(zakupy_decimal))
