import heapq
from collections import deque

goals = set()
walls = set()
visited = set()
commandos = set()
moves = {"U": (0, -1), "D": (0, 1), "L": (-1, 0), "R": (1, 0)}

def h_bfs(): # heurystyka, która tworzy mapę odległości od najbliższego celu
    h = {}
    queue = deque()
    for goal in goals:
        queue.append((goal, 0))
        h[goal] = 0
    while queue: # każde pole dostaje liczbę kroków, jakie należy wykonać, żeby dotrzeć do celu
        (x, y), dist = queue.popleft()
        for dx, dy in moves.values():
            nx, ny = x + dx, y + dy
            if (nx, ny) not in walls and (nx, ny) not in h:
                h[(nx, ny)] = dist + 1
                queue.append(((nx, ny), dist + 1))
    return h

class State:
    def __init__(self, moves, commandos, g, h):
        self.moves = moves
        self.commandos = commandos
        self.g = g
        self.h = self.get_h(h)
    
    def __lt__(self, other): # teraz porównujemy f = g + h
        return (self.g + self.h) < (other.g + other.h)
    
    def get_h(self, h): # najgorszy przypadek, jak daleko jest komandos od celu
        return max(h.get(commando, float('inf')) for commando in self.commandos)

def move(state, move, h):
    new_commandos = set()
    move_tuple = moves[move]
    for commando in state.commandos:
        new_pos = (commando[0] + move_tuple[0], commando[1] + move_tuple[1])
        if new_pos not in walls:
            new_commandos.add(new_pos)
        else:
            new_commandos.add(commando)
    return State(state.moves + move, new_commandos, state.g + 1, h)

def to_string(commandos):
    return " ".join([f"{commando[0]}.{commando[1]}" for commando in commandos])

def is_goal(state):
    return all(commando in goals for commando in state.commandos)

def main():
    with open("zad_input.txt", "r") as fin, open("zad_output.txt", "w") as fout:
        x, y = 0, 0
        for line in fin:
            x = 0
            for c in line.strip():
                if c == 'G':
                    goals.add((x, y))
                elif c == '#':
                    walls.add((x, y))
                elif c == 'B':
                    commandos.add((x, y))
                    goals.add((x, y))
                elif c == 'S':
                    commandos.add((x, y))
                x += 1
            y += 1        
        h = h_bfs()
        start = State("", commandos, 0, h)
        pq = []
        heapq.heappush(pq, start)
        while pq:
            current = heapq.heappop(pq)
            if is_goal(current):
                fout.write(current.moves + "\n")
                return
            state_str = to_string(current.commandos)
            if state_str in visited:
                continue
            visited.add(state_str)
            for dir in ["U", "D", "L", "R"]:
                new_state = move(current, dir, h)
                heapq.heappush(pq, new_state)

if __name__ == "__main__":
    main()