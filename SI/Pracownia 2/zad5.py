import heapq
from collections import deque

goals = set()
walls = set()
visited = set()
commandos = set()
moves = {"U": (0, -1), "D": (0, 1), "L": (-1, 0), "R": (1, 0)}

def h_bfs():
    h = {}
    queue = deque()
    for goal in goals:
        queue.append((goal, 0))
        h[goal] = 0
    while queue:
        (x, y), dist = queue.popleft()
        for dx, dy in moves.values():
            nx, ny = x + dx, y + dy
            if (nx, ny) not in walls and (nx, ny) not in h:
                h[(nx, ny)] = dist + 1
                queue.append(((nx, ny), dist + 1))
    return h

class State:
    def __init__(self, moves, commandos, g, h, alpha):
        self.moves = moves
        self.commandos = commandos
        self.g = g
        self.alpha = alpha
        self.h = self.get_h(h)
    
    def __lt__(self, other):
        return (self.g + self.h) < (other.g + other.h)
    
    def get_h(self, h):
        return max(h.get(commando, float('inf')) * self.alpha for commando in self.commandos)

def move(state, move, h, alpha):
    new_commandos = set()
    move_tuple = moves[move]
    for commando in state.commandos:
        new_pos = (commando[0] + move_tuple[0], commando[1] + move_tuple[1])
        if new_pos not in walls:
            new_commandos.add(new_pos)
        else:
            new_commandos.add(commando)
    return State(state.moves + move, new_commandos, state.g + 1, h, alpha)

def to_string(commandos):
    return " ".join([f"{commando[0]}.{commando[1]}" for commando in commandos])

def is_goal(state):
    return all(commando in goals for commando in state.commandos)

def main():
    alpha = 1.1
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
        start = State("", commandos, 0, h, alpha)
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
                new_state = move(current, dir, h, alpha)
                heapq.heappush(pq, new_state)

if __name__ == "__main__":
    main()