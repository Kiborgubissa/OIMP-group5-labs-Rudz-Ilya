#include <cctype>
#include <clocale>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int N = 10;

enum Cell : char {
    EMPTY = '.',
    SHIP = '#',
    HIT = 'X',
    MISS = 'o'
};

enum Result {
    OUT_OF_BOUNDS,
    ALREADY,
    MISS_R,
    HIT_R
};

// ---------- Поле ----------
struct Board {
    char g[N][N];

    Board() { clear(); }

    void clear() {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                g[i][j] = EMPTY;
    }

    bool canPlace(int r, int c, int len, bool horiz) const {
        if (horiz && c + len > N) return false;
        if (!horiz && r + len > N) return false;
        for (int i = 0; i < len; i++) {
            int rr = horiz ? r : r + i;
            int cc = horiz ? c + i : c;
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++) {
                    int nr = rr + dr, nc = cc + dc;
                    if (nr >= 0 && nr < N && nc >= 0 && nc < N && g[nr][nc] == SHIP)
                        return false;
                }
        }
        return true;
    }

    void placeShip(int r, int c, int len, bool horiz) {
        for (int i = 0; i < len; i++) {
            int rr = horiz ? r : r + i;
            int cc = horiz ? c + i : c;
            g[rr][cc] = SHIP;
        }
    }

    void generateRandom(mt19937& rng) {
        clear();
        int fleet[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
        for (int len : fleet) {
            while (true) {
                int r = rng() % N;
                int c = rng() % N;
                bool horiz = rng() % 2;
                if (canPlace(r, c, len, horiz)) {
                    placeShip(r, c, len, horiz);
                    break;
                }
            }
        }
    }

    int remainingShips() const {
        int cnt = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (g[i][j] == SHIP) cnt++;
        return cnt;
    }

    bool allSunk() const { return remainingShips() == 0; }

    void print(bool showShips, const string& title) const {
        cout << "\n=== " << title << " ===\n";
        cout << "   ";
        for (int j = 1; j <= N; j++) cout << setw(2) << j;
        cout << "\n";
        for (int i = 0; i < N; i++) {
            cout << " " << char('A' + i) << " ";
            for (int j = 0; j < N; j++) {
                char ch = g[i][j];
                if (ch == SHIP && !showShips) ch = EMPTY;
                cout << setw(2) << ch;
            }
            cout << "\n";
        }
    }
};

// ---------- Общая атака ----------
Result attack(Board& b, int r, int c) {
    if (r < 0 || r >= N || c < 0 || c >= N) return OUT_OF_BOUNDS;
    if (b.g[r][c] == HIT || b.g[r][c] == MISS) return ALREADY;
    if (b.g[r][c] == SHIP) { b.g[r][c] = HIT;  return HIT_R; }
    b.g[r][c] = MISS;
    return MISS_R;
}

// ---------- Ввод ----------
bool parseCoord(const string& s, int& r, int& c) {
    size_t i = 0;
    while (i < s.size() && isspace((unsigned char)s[i])) i++;
    if (i >= s.size() || !isalpha((unsigned char)s[i])) return false;
    r = toupper((unsigned char)s[i]) - 'A';
    i++;
    int num = 0;
    bool ok = false;
    while (i < s.size() && isdigit((unsigned char)s[i])) {
        num = num * 10 + (s[i] - '0');
        i++;
        ok = true;
    }
    if (!ok || num < 1 || num > N) return false;
    c = num - 1;
    return r >= 0 && r < N;
}

string cellName(int r, int c) {
    return string(1, char('A' + r)) + to_string(c + 1);
}

string trim(const string& s) {
    size_t a = 0, z = s.size();
    while (a < z && isspace((unsigned char)s[a])) a++;
    while (z > a && isspace((unsigned char)s[z - 1])) z--;
    return s.substr(a, z - a);
}

vector<string> splitWords(const string& s) {
    vector<string> out;
    size_t i = 0;
    while (i < s.size()) {
        while (i < s.size() && isspace((unsigned char)s[i])) i++;
        if (i >= s.size()) break;
        size_t j = i;
        while (j < s.size() && !isspace((unsigned char)s[j])) j++;
        out.push_back(s.substr(i, j - i));
        i = j;
    }
    return out;
}

// ---------- Ручная расстановка ----------
void setupManual(Board& b) {
    b.clear();
    int fleet[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    int total = 10, placed = 0;

    for (int len : fleet) {
        while (true) {
            b.print(true, "Расстановка вашего флота");
            cout << "[" << (placed + 1) << "/" << total << "] Корабль длиной " << len
                << " (например B2 B" << (2 + len - 1) << "): ";
            string line;
            if (!getline(cin, line)) exit(0);

            auto tok = splitWords(line);
            if (tok.size() != 2) {
                cout << "Нужно две координаты через пробел.\n\n";
                continue;
            }
            int r1, c1, r2, c2;
            if (!parseCoord(tok[0], r1, c1) || !parseCoord(tok[1], r2, c2)) {
                cout << "Неверные координаты (буква A-J, число 1-10).\n\n";
                continue;
            }
            if (r1 != r2 && c1 != c2) {
                cout << "Корабль должен быть горизонтальным или вертикальным.\n\n";
                continue;
            }
            int actualLen = (r1 == r2) ? abs(c2 - c1) + 1 : abs(r2 - r1) + 1;
            if (actualLen != len) {
                cout << "Нужна длина " << len << ", а вы задали " << actualLen << ".\n\n";
                continue;
            }
            int r = min(r1, r2), c = min(c1, c2);
            bool horiz = (r1 == r2);
            if (!b.canPlace(r, c, len, horiz)) {
                cout << "Сюда нельзя: выход за границы или касание другого корабля.\n\n";
                continue;
            }
            b.placeShip(r, c, len, horiz);
            ++placed;
            break;
        }
    }
    b.print(true, "Ваш флот расставлен");
}

// ---------- Случайная расстановка с перебросом ----------
void setupRandomInteractive(Board& b, mt19937& rng) {
    while (true) {
        b.generateRandom(rng);
        b.print(true, "Случайная расстановка");
        cout << "[Enter — принять, r — перебросить]: ";
        string line;
        if (!getline(cin, line)) exit(0);
        string ans = trim(line);
        if (ans.empty()) return;
        if (ans == "r" || ans == "R" || ans == "к" || ans == "К") continue;
        cout << "Enter — принять, r — перебросить.\n\n";
    }
}

// ---------- ИИ ----------
struct AI {
    mt19937& rng;
    set<pair<int, int>> tried;
    vector<pair<int, int>> pending;

    AI(mt19937& r) : rng(r) {}

    void onHit(int r, int c) {
        int dr[] = { -1, 1, 0, 0 };
        int dc[] = { 0, 0,-1, 1 };
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N && !tried.count({ nr, nc }))
                pending.push_back({ nr, nc });
        }
    }

    pair<int, int> choose() {
        while (!pending.empty()) {
            auto p = pending.back();
            pending.pop_back();
            if (!tried.count(p)) {
                tried.insert(p);
                return p;
            }
        }
        uniform_int_distribution<int> d(0, N - 1);
        for (int k = 0; k < 10000; k++) {
            int r = d(rng), c = d(rng);
            if (!tried.count({ r, c })) {
                tried.insert({ r, c });
                return { r, c };
            }
        }
        return { -1, -1 };
    }
};

// ---------- main ----------
int main() {
    setlocale(LC_ALL, "Russian");
    mt19937 rng((unsigned)time(nullptr));

    Board player, enemy;
    AI ai(rng);

    cout << "=== МОРСКОЙ БОЙ ===\n";
    cout << "Флот: 1x4, 2x3, 3x2, 4x1 (20 клеток).\n";
    cout << "Корабли не касаются друг друга, даже углами.\n";

    // --- Выбор расстановки игрока ---
    while (true) {
        cout << "\nКак расставить ваш флот?\n";
        cout << "  1 — вручную\n";
        cout << "  2 — случайно\n";
        cout << "Выбор: ";
        string line;
        if (!getline(cin, line)) return 0;
        string ans = trim(line);
        if (ans == "1") { setupManual(player); break; }
        if (ans == "2") { setupRandomInteractive(player, rng); break; }
        cout << "Введите 1 или 2.\n";
    }

    // --- Программа расставляет свой флот ---
    cout << "\nПрограмма расставляет свой флот...\n";
    enemy.generateRandom(rng);

    cout << "\n=== Начало игры ===\n";
    cout << "Формат хода: буква A-J и число 1-10 (например, C7).\n";
    cout << "Попал — стреляешь ещё раз, промахнулся — ход переходит.\n";

    bool playerTurn = true;
    int playerMoves = 0, aiMoves = 0;

    while (true) {
        if (playerTurn) {
            player.print(true, "Ваше поле");
            enemy.print(false, "Поле противника");

            int r = 0, c = 0;
            Result res = ALREADY;
            while (true) {
                cout << "\nВаш ход: ";
                string line;
                if (!getline(cin, line)) return 0;
                if (trim(line).empty()) continue;
                if (!parseCoord(line, r, c)) {
                    cout << "Неверный формат. Буква A-J и число 1-10.\n";
                    continue;
                }
                res = attack(enemy, r, c);
                if (res == ALREADY) { cout << "Сюда уже стреляли.\n"; continue; }
                if (res == OUT_OF_BOUNDS) { cout << "Вне поля.\n"; continue; }
                break;
            }
            ++playerMoves;

            if (res == HIT_R) {
                cout << "Попадание! Стреляйте снова.\n";
                if (enemy.allSunk()) {
                    cout << "\n*** Вы победили за " << playerMoves << " ходов! ***\n";
                    return 0;
                }
            }
            else {
                cout << "Промах. Ход переходит к программе.\n";
                playerTurn = false;
            }
        }
        else {
            auto p = ai.choose();
            int r = p.first, c = p.second;
            if (r < 0) { cout << "Программа не нашла цель.\n"; return 0; }

            ++aiMoves;
            Result res = attack(player, r, c);
            cout << "\nПрограмма стреляет в " << cellName(r, c) << ": ";

            if (res == HIT_R) {
                ai.onHit(r, c);
                cout << "попадание!\n";
                player.print(true, "Ваше поле");
                if (player.allSunk()) {
                    cout << "\n*** Программа победила. Её ходов: " << aiMoves << " ***\n";
                    return 0;
                }
            }
            else {
                cout << "промах.\n";
                playerTurn = true;
            }
        }
    }
}
