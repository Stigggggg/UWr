import itertools

figury = ['J', 'Q', 'K', 'A']
blotki = [str(i) for i in range(2, 11)]
kolory = ['H', 'D', 'S', 'C'] 
talia_b = [(b, k) for b in blotki for k in kolory]
talia_f = [(f, k) for f in figury for k in kolory]

def to_dict(list):
  dict = {}
  for i in list:
    if i in dict:
      dict[i] += 1
    else:
      dict[i] = 1
  return dict

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
   
def uklady(hand):
   value_map = {'2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, '10': 10, 'J': 11, 'Q': 12, 'K': 13, 'A': 14}
   hand = sorted(((value_map[h[0]], h[1]) for h in hand), key=lambda x: x[0])
   hand_v = sorted(to_dict(map(lambda x: x[0], hand)).items(), key=lambda x: x[1], reverse=True)
   uklad = 0 # wysoka karta
   if czy_poker(hand): # poker
      uklad = 8
   elif hand_v[0][1] == 4: # kareta
      uklad = 7
   elif hand_v[0][1] == 3 and hand_v[1][1] == 2: # full
      uklad = 6
   elif czy_kolor(hand): # kolor
      uklad = 5
   elif czy_strit(hand): # strit
      uklad = 4
   elif hand_v[0][1] == 3: # trójka
      uklad = 3
   elif hand_v[0][1] == 2 and hand_v[1][1] == 2: # 2 pary
      uklad = 2
   elif hand_v[0][1] == 2: # para
      uklad = 1
   return uklad

def count(talia):
   counts = [0] * 9
   for hand in itertools.combinations(talia, 5):
      uklad = uklady(hand)
      counts[uklad] += 1
   return counts

b = count(talia_b)
f = count(talia_f)
b = [x / sum(b) for x in b]
f = [x / sum(f) for x in f]
res = 0
for i in range(0, 9):
   for j in range(i):
      res += b[i] * f[j]
print(f'Procent wygranych blotkarza: {res * 100:.2f}%')
    
          
          

   
   