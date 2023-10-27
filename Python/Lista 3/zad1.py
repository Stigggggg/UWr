def czy_palindrom(tekst):
    if len(tekst)>=2 and tekst==tekst[::-1]:
        return 1
    else:
        return 0
def naj_palindrom(tekst):
    palindromy=[]
    tekst=tekst.lower()
    tekst=tekst.replace(" ","")
    print(tekst)
    for i in range(len(tekst)):
        for j in range(i+2,len(tekst)+1):
            substr=tekst[i:j]
            if czy_palindrom(substr):
                palindromy.append((i,len(substr)))
    if not palindromy:
        return palindromy
    naj=palindromy[0]
    for i in range(1,len(palindromy)):
        if palindromy[i][1]>naj[1]:
            naj=palindromy[i]
    return naj

text="Madam Arora teaches Malayalam level civic deified noon refer deed rotor racecar"
result=naj_palindrom(text)
print(result)
