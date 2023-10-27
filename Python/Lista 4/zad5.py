import itertools

def eval(slowo,podst):
    s=0
    i=1
    for l in reversed(slowo):
        s+=i*podst[l]
        i*=10
    return s

def solve(s):
    slowa=s.split()
    l,r,wynik,op=slowa[0],slowa[1],slowa[2],slowa[3]
    litery=set(l+r+wynik)
    cyfry=range(10)
    for perm in itertools.permutations(cyfry,len(litery)):
        rozw=dict(zip(litery,perm))
        if op=="+" and eval(l,rozw)+eval(r,rozw)==eval(wynik,rozw):
            return rozw
        if op=="-" and eval(l,rozw)-eval(r,rozw)==eval(wynik,rozw):
            return rozw
        if op=="*" and eval(l,rozw)*eval(r,rozw)==eval(wynik,rozw):
            return rozw
        if op=="/" and eval(l,rozw)/eval(r,rozw)==eval(wynik,rozw):
            return rozw

print(solve("KIOTO OSAKA TOKIO +"))
#KIOTO=41373
#OSAKA=32040
#TOKIO=74313
print(41373+32040==73413)