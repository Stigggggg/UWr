import random
import sys

class Reversi:
    M = 8
    DIRS = [(0, 1), (1, 0), (-1, 0), (0, -1), (1, 1), (-1, -1), (1, -1), (-1, 1)]
    ZOBRIST_TABLE = [[[random.getrandbits(64) for _ in range(2)] for _ in range(8)] for _ in range(M)]

    def __init__(self):
        self.board = self.initial_board()
        self.fields = set()
        self.move_list = []
        self.history = []
        self.zobrist_hash = self.compute_zobrist()  # ← Zobrist hash na starcie
        for i in range(self.M):
            for j in range(self.M):
                if self.board[i][j] is None:
                    self.fields.add((j, i))

    def initial_board(self):
        B = [[None] * self.M for _ in range(self.M)]
        B[3][3] = 1
        B[4][4] = 1
        B[3][4] = 0
        B[4][3] = 0
        return B

    def compute_zobrist(self):
        # Oblicz Zobrist hash na podstawie planszy
        h = 0
        for y in range(self.M):
            for x in range(self.M):
                p = self.board[y][x]
                if p is not None:
                    h ^= self.ZOBRIST_TABLE[y][x][p]
        return h

    def update_zobrist(self, move, player, flipped):
        # Aktualizuj Zobrist hash po wykonanym ruchu i zamianach pionków
        x, y = move
        self.zobrist_hash ^= self.ZOBRIST_TABLE[y][x][player]
        for fx, fy in flipped:
            opponent = 1 - player
            self.zobrist_hash ^= self.ZOBRIST_TABLE[fy][fx][opponent]
            self.zobrist_hash ^= self.ZOBRIST_TABLE[fy][fx][player]

    def draw(self):
        for i in range(self.M):
            res = []
            for j in range(self.M):
                b = self.board[i][j]
                if b is None:
                    res.append('.')
                elif b == 1:
                    res.append('#')
                else:
                    res.append('o')
            print(''.join(res))
        print('')

    def moves(self, player):
        res = []
        for (x, y) in self.fields:
            if any(self.can_beat(x, y, direction, player)
                   for direction in self.DIRS):
                res.append((x, y))
        return res

    def can_beat(self, x, y, d, player):
        dx, dy = d
        x += dx
        y += dy
        cnt = 0
        while self.get(x, y) == 1 - player:
            x += dx
            y += dy
            cnt += 1
        return cnt > 0 and self.get(x, y) == player

    def get(self, x, y):
        if 0 <= x < self.M and 0 <= y < self.M:
            return self.board[y][x]
        return None

    def do_move(self, move, player):
        assert player == len(self.move_list) % 2
        self.history.append([x[:] for x in self.board])
        self.move_list.append(move)
        if move is None:
            return
        x, y = move
        x0, y0 = move
        self.board[y][x] = player
        self.fields -= set([move])
        flipped = []  # ← zbieraj pola do przewrócenia
        for dx, dy in self.DIRS:
            x, y = x0, y0
            to_beat = []
            x += dx
            y += dy
            while self.get(x, y) == 1 - player:
                to_beat.append((x, y))
                x += dx
                y += dy
            if self.get(x, y) == player:
                for (nx, ny) in to_beat:
                    self.board[ny][nx] = player
                    flipped.append((nx, ny))  # ← zapisz odwrócone pola
        self.update_zobrist(move, player, flipped)  # ← aktualizacja hash

    def result(self):
        res = 0
        for y in range(self.M):
            for x in range(self.M):
                b = self.board[y][x]
                if b == 0:
                    res -= 1
                elif b == 1:
                    res += 1
        return res

    def terminal(self):
        if not self.fields:
            return True
        if len(self.move_list) < 2:
            return False
        return self.move_list[-1] is None and self.move_list[-2] is None

    def copy(self):
        new = Reversi()
        new.board = [row[:] for row in self.board]
        new.fields = set(self.fields)
        new.move_list = list(self.move_list)
        new.zobrist_hash = self.zobrist_hash  # ← kopiuj hash
        return new
    
class Player(object):
    def __init__(self):
        self.reset()

    def reset(self):
        self.game = Reversi()
        self.my_player = 1
        self.transposition_table = {}  # ← resetuj cache
        self.say('RDY')

    def say(self, what):
        sys.stdout.write(what)
        sys.stdout.write('\n')
        sys.stdout.flush()

    def hear(self):
        line = sys.stdin.readline().split()
        return line[0], line[1:]

    def loop(self):
        while True:
            cmd, args = self.hear()
            if cmd == 'HEDID':
                unused_move_timeout, unused_game_timeout = args[:2]
                move = tuple((int(m) for m in args[2:]))
                if move == (-1, -1):
                    move = None
                self.game.do_move(move, 1 - self.my_player)
            elif cmd == 'ONEMORE':
                self.reset()
                continue
            elif cmd == 'BYE':
                break
            else:
                assert cmd == 'UGO'
                assert not self.game.move_list
                self.my_player = 0
            move = self.alpha_beta_search(self.game, 4, self.my_player)
            if move is not None:
                self.game.do_move(move, self.my_player)
            else:
                self.game.do_move(None, self.my_player)
                move = (-1, -1)
            self.say('IDO %d %d' % move)

    def alpha_beta_search(self, game, depth, player):
        def alphabeta(game, depth, alpha, beta, maximizingPlayer):
            key = (game.zobrist_hash, depth, maximizingPlayer)
            if key in self.transposition_table:
                return self.transposition_table[key]  # ← odczytaj z cache
            if depth == 0 or game.terminal():
                eval = self.evaluate(game)
                self.transposition_table[key] = (eval, None)
                return eval, None
            legal_moves = game.moves(player if maximizingPlayer else 1 - player)
            if not legal_moves:
                game_copy = game.copy()
                game_copy.do_move(None, player if maximizingPlayer else 1 - player)
                val, _ = alphabeta(game_copy, depth - 1, alpha, beta, not maximizingPlayer)
                self.transposition_table[key] = (val, None)
                return val, None
            def move_priority(move):
                x, y = move
                if (x, y) in [(0,0), (0,7), (7,0), (7,7)]:
                    return 3
                elif x == 0 or x == 7 or y == 0 or y == 7:
                    return 2
                elif (x in {1,6} and y in {1,6}):
                    return 0
                else:
                    return 1
            legal_moves.sort(key=move_priority, reverse=True)
            best_move = None
            if maximizingPlayer:
                maxEval = -float('inf')
                for move in legal_moves:
                    child = game.copy()
                    child.do_move(move, player)
                    eval, _ = alphabeta(child, depth - 1, alpha, beta, False)
                    if eval > maxEval:
                        maxEval, best_move = eval, move
                    alpha = max(alpha, maxEval)
                    if beta <= alpha:
                        break
                self.transposition_table[key] = (maxEval, best_move)
                return maxEval, best_move
            else:
                minEval = float('inf')
                for move in legal_moves:
                    child = game.copy()
                    child.do_move(move, 1 - player)
                    eval, _ = alphabeta(child, depth - 1, alpha, beta, True)
                    if eval < minEval:
                        minEval, best_move = eval, move
                    beta = min(beta, minEval)
                    if beta <= alpha:
                        break
                self.transposition_table[key] = (minEval, best_move)
                return minEval, best_move
        _, best_move = alphabeta(game, depth, -float('inf'), float('inf'), True)
        return best_move
    def evaluate(self, game):
        weights = [
            [100, -20, 10,  5,  5, 10, -20, 100],
            [-20, -50, -2, -2, -2, -2, -50, -20],
            [10, -2, -1, -1, -1, -1, -2, 10],
            [5, -2, -1, -1, -1, -1, -2, 5],
            [5, -2, -1, -1, -1, -1, -2, 5],
            [10, -2, -1, -1, -1, -1, -2, 10],
            [-20, -50, -2, -2, -2, -2, -50, -20],
            [100, -20, 10,  5,  5, 10, -20, 100]
        ]
        score = 0
        for y in range(8):
            for x in range(8):
                val = game.get(y, x)
                if val == self.my_player:
                    score += weights[y][x]
                elif val == 1 - self.my_player:
                    score -= weights[y][x]
        return score

if __name__ == '__main__':
    player = Player()
    player.loop()
    
