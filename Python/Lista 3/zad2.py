from collections import deque

def prio(operator):
    if operator=="+" or operator=="-":
        return 1
    elif operator=="*" or operator=="/":
        return 2
    return 0

def konwersja(wyrazenie_infiksowe):
    onp=[]
    stos=deque()
    for i in wyrazenie_infiksowe:
        if isinstance(i,int) or isinstance(i,float):
            onp.append(i)
        elif i=="(":
            stos.append(i)
        elif i==")":
            while stos and stos[-1]!="(":
                onp.append(stos.pop())
            stos.pop()
        else:
            while stos and prio(stos[-1])>=prio(i):
                onp.append(stos.pop())
            stos.append(i)
    while stos:
        onp.append(stos.pop())
    return onp

wyrazenie=['(', 2, '-', 3, ')', '/', 4]
print(konwersja(wyrazenie))

def oblicz(wyrazenie_onp):
    stos=deque()
    for i in wyrazenie_onp:
        if isinstance(i,int):
            stos.append(i)
        else:
           if i=="+":
               o1=stos.pop()
               o2=stos.pop()
               stos.append(o2+o1)
           elif i=='-':
               o1 = stos.pop()
               o2 = stos.pop()
               stos.append(o2-o1)
           elif i=='*':
               o1 = stos.pop()
               o2 = stos.pop()
               stos.append(o2*o1)
           elif i=='/':
               o1 = stos.pop()
               o2 = stos.pop()
               stos.append(o2/o1)
    return stos[0]

print(oblicz(konwersja(wyrazenie)))



