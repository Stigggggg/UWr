#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <chrono>
#include <optional>

using namespace std;

const int M = 8;
const int WEIGHTS[8][8] = {
    {120, -20, 20, 5, 5, 20, -20, 120},
    {-20, -40, -5, -5, -5, -5, -40, -20},
    {20, -5, 15, 3, 3, 15, -5, 20},
    {5, -5, 3, 3, 3, 3, -5, 5},
    {5, -5, 3, 3, 3, 3, -5, 5},
    {20, -5, 15, 3, 3, 15, -5, 20},
    {-20, -40, -5, -5, -5, -5, -40, -20},
    {120, -20, 20, 5, 5, 20, -20, 120}
};
const vector<pair<int, int>> DIRS = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
const vector<pair<int, int>> CORNERS = {{0,0}, {0,7}, {7,0}, {7,7}};
unordered_map<unsigned long, pair<int, optional<pair<int, int>>>> TRANSPOSITION_TABLE;

class Reversi {
public:
    vector<vector<int>> board;
    set<pair<int, int>> fields;
    vector<optional<pair<int, int>>> move_list;

    Reversi() {
        board = initial_board();
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < M; ++j) {
                if (board[i][j] == -1) {
                    fields.insert({j, i});
                }
            }
        }
    }

    vector<vector<int>> initial_board() {
        vector<vector<int>> B(M, vector<int>(M, -1));
        B[3][3] = 1;
        B[4][4] = 1;
        B[3][4] = 0;
        B[4][3] = 0;
        return B;
    }

    bool can_beat(int x, int y, pair<int, int> d, int player) const {
        int dx = d.first;
        int dy = d.second;
        x += dx;
        y += dy;
        int cnt = 0;
        while (get(x, y) == 1 - player) {
            x += dx;
            y += dy;
            cnt++;
        }
        return cnt > 0 && get(x, y) == player;
    }

    int get(int x, int y) const {
        if (x >= 0 && x < M && y >= 0 && y < M) {
            return board[y][x];
        }
        return -2;
    }

    vector<pair<int, int>> moves(int player) const {
        vector<pair<int, int>> res;
        for (auto pos : fields) {
            int x = pos.first;
            int y = pos.second;
            for (auto d : DIRS) {
                if (can_beat(x, y, d, player)) {
                    res.push_back(pos);
                    break;
                }
            }
        }
        return res;
    }

    void do_move(optional<pair<int, int>> move, int player) {
        move_list.push_back(move);
        if (!move) {
            return;
        }
        int x0 = move->first;
        int y0 = move->second;
        board[y0][x0] = player;
        fields.erase({x0, y0});
        for (auto d : DIRS) {
            int dx = d.first;
            int dy = d.second;
            int x = x0 + dx;
            int y = y0 + dy;
            vector<pair<int, int>> to_beat;
            while (get(x, y) == 1 - player) {
                to_beat.emplace_back(x, y);
                x += dx;
                y += dy;
            }
            if (get(x, y) == player) {
                for (auto p : to_beat) {
                    board[p.second][p.first] = player;
                }
            }
        }
    }

    bool terminal() const {
        if (fields.empty()) {
            return true;
        } 
        if (move_list.size() < 2) {
            return false;
        } 
        return !move_list.back().has_value() && !move_list[move_list.size() - 2].has_value();
    }
};

int evaluate(const Reversi& game, int player) {
    size_t hash = 0;
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < M; x++) {
            hash ^= std::hash<int>{}(game.board[y][x] + 2) << (y * M + x);
        }
    }
    hash ^= std::hash<int>{}(player);
    auto it = TRANSPOSITION_TABLE.find(hash);
    if (it != TRANSPOSITION_TABLE.end()) {
        return it->second.first;
    }
    int score = 0;
    for (int y = 0; y < M; ++y) {
        for (int x = 0; x < M; ++x) {
            if (game.board[y][x] == player) score += WEIGHTS[y][x];
            else if (game.board[y][x] == 1 - player) score -= WEIGHTS[y][x];
        }
    }
    int my_moves = game.moves(player).size();
    int opp_moves = game.moves(1 - player).size();
    score += (my_moves - opp_moves) * 10;
    for (auto [x, y] : CORNERS) {
        if (game.board[y][x] == player) score += 50;
        else if (game.board[y][x] == 1 - player) score -= 50;
    }
    TRANSPOSITION_TABLE[hash] = {score, nullopt};
    return score;
}

pair<int, optional<pair<int, int>>> minimax(Reversi& game, int depth, int alpha, int beta, bool maximizing, int original_player) {
    int current_player = maximizing ? original_player : 1 - original_player;
    auto legal_moves = game.moves(current_player);
    if (depth == 0 || (legal_moves.empty() && game.moves(1 - current_player).empty())) {
        return {evaluate(game, original_player), nullopt};
    }
    if (legal_moves.empty()) {
        Reversi game_copy = game;
        game_copy.do_move(nullopt, current_player);
        return minimax(game_copy, depth - 1, alpha, beta, !maximizing, original_player);
    }
    auto move_priority = [](const pair<int,int>& m) {
        if (find(CORNERS.begin(), CORNERS.end(), m) != CORNERS.end()) return 3;
        if (m.first == 0 || m.first == 7 || m.second == 0 || m.second == 7) return 2;
        if ((m.first == 1 || m.first == 6) && (m.second == 1 || m.second == 6)) return 0;
        return 1;
    };
    bool use_ordered_moves = true;
    if (use_ordered_moves) {
        sort(legal_moves.begin(), legal_moves.end(), [&](auto a, auto b) {
            return move_priority(a) > move_priority(b);
        });
    } else {
        random_shuffle(legal_moves.begin(), legal_moves.end());
    }
    optional<pair<int, int>> best_move;
    int best_eval = maximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
    for (auto& move : legal_moves) {
        Reversi game_copy = game;
        game_copy.do_move(move, current_player);
        auto [eval, _] = minimax(game_copy, depth - 1, alpha, beta, !maximizing, original_player);
        if (maximizing) {
            if (eval > best_eval) {
                best_eval = eval;
                best_move = move;
            }
            alpha = max(alpha, eval);
        } else {
            if (eval < best_eval) {
                best_eval = eval;
                best_move = move;
            }
            beta = min(beta, eval);
        }
        if (beta <= alpha) break;
    }
    return {best_eval, best_move};
}


class Player {
    Reversi game;
    int my_player;
    
public:
    Player() : my_player(1) {}

    void reset() {
        game = Reversi();
        my_player = 1;
        TRANSPOSITION_TABLE.clear();
        cout << "RDY" << endl << flush;
    }

    pair<string, vector<string>> hear() {
        string line;
        if (!getline(cin, line)) {
            return {"BYE", {}};
        }
        istringstream iss(line);
        string cmd;
        iss >> cmd;
        vector<string> args;
        string token;
        while (iss >> token) args.push_back(token);
        return {cmd, args};
    }

    void loop() {
        reset();
        while (true) {
            auto [cmd, args] = hear();
            if (cmd == "UGO") {
                my_player = 0;
            } 
            else if (cmd == "HEDID") {
                optional<pair<int, int>> move = nullopt;
                if (args.size() >= 4) {
                    int x = stoi(args[2]);
                    int y = stoi(args[3]);
                    if (x != -1 && y != -1)
                        move = make_pair(x, y);
                }
                game.do_move(move, 1 - my_player);
            } 
            else if (cmd == "ONEMORE") {
                reset();
                continue;
            } 
            else if (cmd == "BYE") {
                break;
            }
            auto moves = game.moves(my_player);
            optional<pair<int, int>> move;
            if (!moves.empty()) {
                move = minimax(game, 2, numeric_limits<int>::min(), numeric_limits<int>::max(), true, my_player).second;
            }
            if (move) {
                game.do_move(move, my_player);
                cout << "IDO " << move->first << " " << move->second << endl << flush;
            } else {
                game.do_move(nullopt, my_player);
                cout << "IDO -1 -1" << endl << flush;
            }
        }
    }    
};

int main() {
    Player player;
    player.loop();
    return 0;
}
