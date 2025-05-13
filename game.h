#ifndef GAME_2048
#define GAME_2048

#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;

enum OPERATION {UP, DOWN, LEFT, RIGHT, UNDO, RETRY, OTHER};

struct History {
    array<array<int, 4>, 4> item;
    int score;
};

class Stage {
    private:
        array<array<int, 4>, 4> item {{{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}}};
        int score = 0, record;
        deque<History> history;
        ifstream fin;
        ofstream fout;
        
        const short GOAL = 2048, MAX_HISTORY = 5;
        
        array<int*, 4> row(short n) {return {&item[n][0],&item[n][1],&item[n][2],&item[n][3]};}
        array<int*, 4> rowf(short n) {return {&item[n][3],&item[n][2],&item[n][1],&item[n][0]};}
        array<int*, 4> col(short n) {return {&item[0][n],&item[1][n],&item[2][n],&item[3][n]};}
        array<int*, 4> colf(short n) {return {&item[3][n],&item[2][n],&item[1][n],&item[0][n]};}

        bool merge(array<int*, 4> &&arr);
        void printItem(short row, short col) const;
        void summon();
        void undo();
    public:
        Stage();
        ~Stage();

        bool update(OPERATION opr);
        bool win() const;
        bool lose() const;

        void background() const;
        void print() const;
        void printWin() const;
        void printLose() const;
};

void initialize();
void guide();
OPERATION GetOperation();

#endif