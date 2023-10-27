import math
import timeit

def czy_pierwsza(n):
    if n<2:
        return 0
    if n==2:
        return 1
    if n%2==0:
        return 0
    for i in range(3,(int)(math.sqrt(n))+1):
        if n%i==0:
            return 0
    return 1

def pierwsze_imperatywna(n):
    pierwsze=[]
    for i in range(2,n):
        if czy_pierwsza(i):
            pierwsze.append(i)
    return pierwsze

print(pierwsze_imperatywna(20))

def pierwsze_skladana(n):
    mniejsze=range(n)
    pierwsze=[n for n in mniejsze if czy_pierwsza(n)]
    return pierwsze

print(pierwsze_skladana(20))

def pierwsze_funkcyjna(n):
    mniejsze=[i for i in range(n)]
    pierwsze=list(filter(czy_pierwsza,mniejsze))
    return pierwsze

print(pierwsze_funkcyjna(20))

print("n:\t\tskladana\timperatywna\tfunkcyjna")
for n in range(10, 91, 10):
    skladana_time=timeit.timeit(lambda:pierwsze_skladana(n),number=1000)
    imperatywna_time=timeit.timeit(lambda:pierwsze_imperatywna(n),number=1000)
    funkcyjna_time=timeit.timeit(lambda:pierwsze_funkcyjna(n),number=1000)
    print(f"{n}:\t\t{skladana_time:.3f}\t\t{imperatywna_time:.3f}\t\t{funkcyjna_time:.3f}")





