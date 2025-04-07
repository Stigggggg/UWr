import heapq

moves = {"U": (0, -1), "D": (0, 1), "L": (-1, 0), "R": (1, 0)}
goals = set() # zbiór pól "G/B"
walls = set() # zbiór pól "#"
visited = set() # zbiór pól odwiedzonych
commandos = set() # zbiór pól S/B

class State: # reprezentacja stanu, moves to ciąg liter (ruchów), commandos to zbiór pozycji komandosów
    def __init__(self, moves, commandos):
        self.moves = moves
        self.commandos = commandos
    
    def __lt__(self, other):
        if len(self.commandos) == len(other.commandos):
            return len(self.moves) < len(other.moves)
        return len(self.commandos) < len(other.commandos)

def move(state, move): # analiza ruchu
    new_commandos = set()
    move_tuple = moves[move]
    for commando in state.commandos:
        new_pos = (commando[0] + move_tuple[0], commando[1] + move_tuple[1])
        if new_pos not in walls: # jeśli nowy ruch nie jest w ścianę
            new_commandos.add(new_pos) # to dodajemy nową pozycję komandosa
        else: 
            new_commandos.add(commando) # wpp dodajemy starą
    return State(state.moves + move, new_commandos) # aktualizujemy stan

def to_string(commandos): # pomocnicza funkcja do łatwiejszego porównywania
    return " ".join([f"{x}.{y}" for x, y in commandos])

def is_goal(state): # pomocnicza funkcja do sprawdzania, czy już mamy rozwiązanie
    return all(commando in goals for commando in state.commandos)

def reduce_uncertainty(): # redukcja niepewności - staramy się zawęzić do jednego punktu startowego
    queue = []
    heapq.heappush(queue, State("", commandos))
    visited.clear()
    while queue:
        current = heapq.heappop(queue)
        if len(current.commandos) == 1:
            return current
        if to_string(current.commandos) in visited:
            continue
        visited.add(to_string(current.commandos))
        for direction in ["U", "D", "L", "R"]:
            new_state = move(current, direction)
            heapq.heappush(queue, new_state)
    return None 

def bfs_solve(start, fout):
    queue = []
    heapq.heappush(queue, start)
    visited.clear()
    while queue:
        current = heapq.heappop(queue)
        if to_string(current.commandos) in visited:
            continue
        visited.add(to_string(current.commandos))
        if is_goal(current):
            fout.write(current.moves + "\n")
            return
        for direction in ["U", "D", "L", "R"]:
            new_state = move(current, direction)
            heapq.heappush(queue, new_state)

with open("zad_input.txt", "r", encoding="utf-8") as fin, open("zad_output.txt", "w", encoding="utf-8") as fout:
    i, j = 0, 0
    for line in fin: # czytamy mapę, dodajemy szczególne pola do zbiorów
        i = 0
        for k in line.strip():
            if k == 'G':
                goals.add((i, j))
            elif k == '#':
                walls.add((i, j))
            elif k == 'B':
                commandos.add((i, j))
                goals.add((i, j))
            elif k == 'S':
                commandos.add((i, j))
            i += 1
        j += 1
    start = reduce_uncertainty()
    bfs_solve(start, fout)




