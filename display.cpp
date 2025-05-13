#include "game.h"

static const short COLOR[16][6] = {{0, 0, 0, 189, 172, 151},
                                   {117, 100, 82, 238, 228, 218},
                                   {117, 100, 82, 235, 216, 182},
                                   {255, 255, 255, 240, 175, 115},
                                   {255, 255, 255, 246, 148, 98},
                                   {255, 255, 255, 248, 128, 98},
                                   {255, 255, 255, 248, 98, 68},
                                   {255, 255, 255, 242, 205, 85},
                                   {255, 255, 255, 243, 210, 98},
                                   {255, 255, 255, 246, 210, 58},
                                   {255, 255, 255, 250, 200, 50},
                                   {255, 255, 255, 238, 202, 74},
                                   {255, 255, 255, 158, 138, 118},
                                   {117, 100, 82, 242, 242, 242},
                                   {255, 255, 255, 39, 174, 111},
                                   {255, 255, 255, 173, 68, 40}};

static const short BORDER = 12, TEXT = 13, WIN = 14, LOSE = 15;                                  

inline void color(int num) {printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm", COLOR[num][0], COLOR[num][1], COLOR[num][2], COLOR[num][3], COLOR[num][4], COLOR[num][5]);}
inline void pos(short x, short y) {SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x, y});}

void guide() {
    system("color F0");
    color(TEXT); Sleep(800);
    cout << "A Terminal 2048 Game made by Grass Duck."; Sleep(800);
    cout << endl << "Your goal is to create 2048."; Sleep(800);
    cout << endl << endl << "Press W/A/S/D to slide"; Sleep(800);
    cout << endl << "Press Z to undo (5 steps at most)"; Sleep(800);
    cout << endl << "Press R to retry"; Sleep(800);
    cout << endl << endl << "Press any key to start...";
    getch();
}

void Stage::background() const{
    system("cls");
    system("color F0");
    pos(0, 0); color(BORDER);
    for (short i = 0; i < 13; i ++) cout << setw(28) << ' ' << endl;
    cout << setw(28) << ' ';
}

void Stage::printItem(short row, short col) const {
    short x = 6 * col + 2, y = 3 * row + 1;
    color(log2(item[row][col]));
    pos(x, y);
    cout << setw(6) << ' ';
    pos(x, y + 1);
    if (item[row][col] == 1) 
        cout << setw(6) << ' ';
    else {
        cout << setw(3 + int(ceil(log10(item[row][col]))) / 2) << item[row][col];
        cout << setw(3 - int(ceil(log10(item[row][col]))) / 2) << ' ';
    }
    pos(x, y + 2);
    cout << setw(6) << ' ';
}

void Stage::print() const {
    for (short row = 0; row < 4; row ++)
        for (short col = 0; col < 4; col ++)
            printItem(row, col);
    color(TEXT); pos(31, 5);
    cout << "Score: " << left << setw(7) << score << right;
    pos(30,7);
    cout << "Record: " << left << setw(7) << record << right;
    pos(28, 13);
}

void Stage::printWin() const {
    Sleep(1000);
    pos(0, 0); color(WIN);
    for (short i = 0; i < 5; i ++) {
        cout << setw(28) << ' ' << endl;
        Sleep(80);
    }
    cout << setw(10) << ' ' << "You Win!" << setw(10) << ' ' << endl;
    Sleep(80);
    cout << setw(28) << ' ' << endl;
    Sleep(80);
    cout << setw(3) << ' ' << "Press R to play again." << setw(3) << ' ';
    for (short i = 0; i < 6; i ++) {
        Sleep(80);
        cout << endl << setw(28) << ' ';
    }
    
    while(true) {
        char opr = getch();
        if (opr == 'r' || opr == 'R') break;
    }
}

void Stage::printLose() const {
    Sleep(1000);
    pos(0, 0); color(LOSE);
    for (short i = 0; i < 5; i ++) {
        cout << setw(28) << ' ' << endl;
        Sleep(80);
    }
    cout << setw(9) << ' ' << "You Lose!" << setw(10) << ' ' << endl;
    Sleep(80);
    cout << setw(28) << ' ' << endl;
    Sleep(80);
    cout << setw(3) << ' ' << "Press R to play again." << setw(3) << ' ';
    for (short i = 0; i < 6; i ++) {
        Sleep(80);
        cout << endl << setw(28) << ' ';
    }
    
    while(true) {
        char opr = getch();
        if (opr == 'r' || opr == 'R') break;
    }
}