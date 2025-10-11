#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

static const int M = 8;
vector<pair<int, int>> DIRS = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

class Reversi {
public:
    vector<vector<int>> board;
    set<pair<int, int>> fields;
    vector<pair<int, int>> move_list;
    vector<vector<vector<int>>> history;

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

    vector<pair<int, int>> moves(int player) {
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

    bool can_beat(int x, int y, pair<int, int> d, int player) {
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

    void do_move(pair<int, int> move, int player) {
        history.push_back(board);
        move_list.push_back(move);
        if (move.first == -1 && move.second == -1) return;
        int x0 = move.first;
        int y0 = move.second;
        board[y0][x0] = player;
        fields.erase(move);
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

    bool terminal() {
        return fields.empty() ||
               (move_list.size() >= 2 && move_list[move_list.size() - 1] == make_pair(-1, -1) && move_list[move_list.size() - 2] == make_pair(-1, -1));
    }
};

class Player {
public:
    Reversi game;
    int my_player;

    Player() {
        reset();
    }

    void reset() {
        game = Reversi();
        my_player = 1;
        say("RDY");
    }

    void say(const string& what) {
        cout << what << endl;
        cout.flush();
    }

    pair<string, vector<string>> hear() {
        string line;
        getline(cin, line);
        istringstream iss(line);
        string cmd;
        vector<string> args;
        iss >> cmd;
        string arg;
        while (iss >> arg) args.push_back(arg);
        return {cmd, args};
    }

    void loop() {
        while (true) {
            auto p = hear();
            string cmd = p.first;
            vector<string> args = p.second;
            if (cmd == "HEDID") {
                int x = stoi(args[2]);
                int y = stoi(args[3]);
                pair<int, int> move = (x == -1 && y == -1) ? make_pair(-1, -1) : make_pair(x, y);
                game.do_move(move, 1 - my_player);
            } else if (cmd == "ONEMORE") {
                reset();
                continue;
            } else if (cmd == "BYE") {
                break;
            } else {
                my_player = 0;
            }
            vector<pair<int, int>> legal_moves = game.moves(my_player);
            pair<int, int> move;
            if (!legal_moves.empty()) {
                move = legal_moves[rand() % legal_moves.size()];
                game.do_move(move, my_player);
            } else {
                move = {-1, -1};
                game.do_move(move, my_player);
            }
            say("IDO " + to_string(move.first) + " " + to_string(move.second));
        }
    }
};

int main() {
    Player player;
    player.loop();
    return 0;
}
