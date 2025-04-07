import heapq

goals = set()
walls = set()
visited = set()
commandos = set()
moves = {"U": (0, -1), "D": (0, 1), "L": (-1, 0), "R": (1, 0)}

class State:
    def __init__(self, moves, commandos, g):
        self.moves = moves
        self.commandos = commandos
        self.g = g 
        self.h = self.heuristic()

    def __lt__(self, other):
        return (self.g + self.h) < (other.g + other.h)

    def heuristic(self): # heurystyka manhattańska
        return max(min(abs(c[0] - g[0]) + abs(c[1] - g[1]) for g in goals) for c in self.commandos)

def move(state, move):
    new_commandos = set()
    move_tuple = moves[move]
    for commando in state.commandos:
        new_pos = (commando[0] + move_tuple[0], commando[1] + move_tuple[1])
        if new_pos not in walls:
            new_commandos.add(new_pos)
        else:
            new_commandos.add(commando)
    return State(state.moves + move, new_commandos, state.g + 1)

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
        start = State("", commandos, 0)
        queue = []
        heapq.heappush(queue, start)
        while queue:
            current = heapq.heappop(queue)
            if is_goal(current):
                fout.write(current.moves + "\n")
                return
            state_str = to_string(current.commandos)
            if state_str in visited:
                continue
            visited.add(state_str)
            for dir in ["U", "D", "L", "R"]:
                new_state = move(current, dir)
                heapq.heappush(queue, new_state)

if __name__ == "__main__":
    main()