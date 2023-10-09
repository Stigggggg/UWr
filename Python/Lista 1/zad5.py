def common_prefix(lista_slow):
    if not lista_slow:
        return ""
    elif len(lista_slow) == 1:
        return lista_slow[0].lower()
    else:
        lista_slow = [slowo.lower() for slowo in lista_slow]
        prefixes = []
        for i in range(len(lista_slow)):
            slowo = lista_slow[i]
            for j in range(1, len(slowo)+1):
                prefixes.append(slowo[:j])
        wyst = {}
        for i in prefixes:
            if i not in wyst:
                wyst[i] = 1
            else:
                wyst[i] += 1
        naj = ""
        for ile in wyst:
            if wyst[ile] >= 3:
                if len(ile) > len(naj):
                    naj = ile
        return naj

print(common_prefix(["Cyprian", "cyberotoman", "cynik", "ceniąc", "czule"]))









