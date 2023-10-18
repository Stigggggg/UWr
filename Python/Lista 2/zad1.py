def dhondt(glosy, miejsca):
    prog = 0.05 * sum(glosy)
    mandaty = [0] * len(glosy)
    for i in range(miejsca):
        max_iloraz = 0
        max_indeks = -1
        for j in range(len(glosy)):
            iloraz = glosy[j]/(mandaty[j]+1)
            if iloraz >= prog:
                if iloraz > max_iloraz:
                    max_iloraz = iloraz
                    max_indeks = j
        if max_indeks != -1:
            mandaty[max_indeks] += 1
    return mandaty

print(dhondt([720, 300, 480],8))