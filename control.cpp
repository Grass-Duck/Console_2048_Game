#include "game.h"

OPERATION GetOperation() {
    switch (getch()) {
        case 'w': case 'W': return UP;        
        case 's': case 'S': return DOWN;
        case 'a': case 'A': return LEFT;
        case 'd': case 'D': return RIGHT;
        case 'z': case 'Z': return UNDO;
        case 'r': case 'R': return RETRY;
        default: return OTHER;            
    }
}

void Stage::undo() {
    if(history.size() != 1) {
        history.pop_back(); 
        item = history.back().item;
        score = history.back().score;
    }
}

bool Stage::update(OPERATION opr) {    
    switch (opr) {
        case UP: for (short i = 0; i < 4; i ++) merge(col(i)); break;        
        case DOWN: for (short i = 0; i < 4; i ++) merge(colf(i)); break;
        case LEFT: for (short i = 0; i < 4; i ++) merge(row(i)); break;        
        case RIGHT: for (short i = 0; i < 4; i ++) merge(rowf(i)); break;
        case UNDO: undo(); break;
        case RETRY: return false;
        case OTHER: return true;
    }
    if (opr != UNDO && item != history.back().item) {
        summon();
        if (history.size() == MAX_HISTORY + 1) history.pop_front();
        history.push_back({item, score});
    }
    if (record < score) record = score;
    return true;
}

bool Stage::win() const {
    for (short row = 0; row < 4; row ++)
        for (short col = 0; col < 4; col ++)
            if (item[row][col] == GOAL) return true;
    return false;
}

bool Stage::lose() const {
    for (short row = 0; row < 4; row ++)
        for (short col = 0; col < 4; col ++)
            if (item[row][col] == 1) return false;
    for (short row = 0; row < 4; row ++)
        for (short col = 0; col < 4; col ++)
            if ((row != 3 && item[row][col] == item[row + 1][col]) || 
                (row != 0 && item[row][col] == item[row - 1][col]) ||
                (col != 3 && item[row][col] == item[row][col + 1]) || 
                (col != 0 && item[row][col] == item[row][col - 1])) return false;
    return true;
}