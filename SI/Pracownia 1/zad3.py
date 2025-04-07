# na początku losujemy ręce blotkarza i figuranta, po 5 kart dla każdego
# przechowujemy informację, jakie i ile kart ma każdy z graczy, co pomaga nam analizować poszczególne układy
# metodą prób i błędów znajdujemy pierwszą możliwą talię, która da statystyczne zwycięstwo blotkarzowi

import random

figury = ['J', 'Q', 'K', 'A']
blotki = [str(i) for i in range(2, 11)]
blotki_2 = [str(i) for i in range(8, 11)]
kolory = ['H', 'D', 'S', 'C'] # H - kier, D - karo, S - trefl, C - pik
talia_b = [(b, k) for b in blotki for k in kolory]
talia_b2 = [(b, k) for b in blotki_2 for k in kolory]
talia_f = [(f, k) for f in figury for k in kolory]

def to_dict(list):
  dict = {}
  for i in list:
    if i in dict:
      dict[i] += 1
    else:
      dict[i] = 1
  return dict

def los_blotkarz(talia_b):
    hand = []
    for i in range(5):
        hand.append(random.choice(talia_b))
        talia_b.remove(hand[i])
    return hand

def los_blotkarz2(talia_b2):
    hand = []
    for i in range(5):
        hand.append(random.choice(talia_b2))
        talia_b2.remove(hand[i])
    return hand

def los_figurant(talia_f):
    hand = []
    for i in range(5):
        hand.append(random.choice(talia_f))
        talia_f.remove(hand[i])
    return hand

def czy_strit(hand):
   if hand[0][0] + 1 == hand[1][0] and hand[1][0] + 1 == hand[2][0] and hand[2][0] + 1 == hand[3][0] and hand[3][0] + 1 == hand[4][0]:
      return True
   else:
      return False
   
def czy_kolor(hand):
   if hand[0][1] == hand[1][1] and hand[1][1] == hand[2][1] and hand[2][1] == hand[3][1] and hand[3][1] == hand[4][1]:
      return True
   else:
      return False

def czy_poker(hand):
   if czy_strit(hand) and czy_kolor(hand):
      return True
   else:
      return False

def uklady(figurant, blotkarz):
   value_map = {'2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, '10': 10, 'J': 11, 'Q': 12, 'K': 13, 'A': 14}
   figurant = sorted(((value_map[f[0]], f[1]) for f in figurant), key=lambda x: x[0])
   blotkarz = sorted(((value_map[b[0]], b[1]) for b in blotkarz), key=lambda x: x[0])
   figurant_v = sorted(to_dict(map(lambda x: x[0], figurant)).items(), key=lambda x: x[1], reverse=True)
   blotkarz_v = sorted(to_dict(map(lambda x: x[0], blotkarz)).items(), key=lambda x: x[1], reverse=True)
   f_uklad = 0 # wysoka karta
   b_uklad = 0 # wysoka karta
   if figurant_v[0][1] == 4: # kareta
      f_uklad = 7
   elif figurant_v[0][1] == 3 and figurant_v[1][1] == 2: # full
      f_uklad = 6
   elif figurant_v[0][1] == 3: # trójka
      f_uklad = 3
   elif figurant_v[0][1] == 2 and figurant_v[1][1] == 2: # 2 pary
      f_uklad = 2
   else: # para
      f_uklad = 1
   if czy_poker(blotkarz): # poker
      b_uklad = 8
   elif blotkarz_v[0][1] == 4: # kareta
      b_uklad = 7
   elif blotkarz_v[0][1] == 3 and blotkarz_v[1][1] == 2: # full
      b_uklad = 6
   elif czy_kolor(blotkarz): # kolor
      b_uklad = 5
   elif czy_strit(blotkarz): # strit
      b_uklad = 4
   elif blotkarz_v[0][1] == 3: # trójka
      b_uklad = 3
   elif blotkarz_v[0][1] == 2 and blotkarz_v[1][1] == 2: # 2 pary
      b_uklad = 2
   elif blotkarz_v[0][1] == 2: # para
      b_uklad = 1
   if b_uklad > f_uklad:
      return 0
   else:
      return 1
    
n = 100000
blotkarz_win = 0
figurant_win = 0
for i in range(n):
   res = uklady(los_figurant(talia_f), los_blotkarz2(talia_b2))
   talia_b = [(b, k) for b in blotki for k in kolory]
   talia_b2 = [(b, k) for b in blotki_2 for k in kolory]
   talia_f = [(f, k) for f in figury for k in kolory]
   if res == 1:
      figurant_win = figurant_win + 1
   else:
      blotkarz_win = blotkarz_win + 1

print(f'Procent wygranych figuranta: {(figurant_win / n) * 100:.2f}%\nProcent wygranych blotkarza: {(blotkarz_win / n) * 100:.2f}%')



    



