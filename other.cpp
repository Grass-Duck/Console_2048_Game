#include "game.h"

void initialize() {
    srand(time(NULL));
    system("title 2048 Game by Grass Duck");
}

Stage::Stage() {
    summon(); summon();
    history.push_back({item, score});

    fin.open("2048_record.txt");
    if (fin) {
        fin >> record;
        if (fin.fail()) record = 0;
        fin.close();
    }
    else record = 0;
}

Stage::~Stage() {
    fout.open("2048_record.txt");
    fout << record;
    fout.close();
}

void Stage::summon() {
    vector<int*> blank;
    for (short row = 0; row < 4; row ++)
        for (short col = 0; col < 4; col ++)
            if (item[row][col] == 1) blank.push_back(&item[row][col]);
    *blank[rand() % blank.size()] = (rand() % 10 ? 2 : 4);
}

bool Stage::merge(array<int*, 4> &&arr) {
    if (*arr[0] == *arr[1] && *arr[2] == *arr[3] && *arr[0] != 1 && *arr[2] != 1) {
        *arr[0] *= 2; *arr[1] = *arr[2] * 2; *arr[2] = 1; *arr[3] = 1;
        score += *arr[0] + *arr[1];
        return true;    
    }
    
    short temp = 0;
    for (short i = 0; i < 4; i ++)
        if (*arr[i] != 1) 
            *arr[temp ++] = *arr[i];
    for (short i = temp; i < 4; i ++)
        *arr[i] = 1;

    short temp2 = 0;
    for (; temp2 < temp - 1; temp2 ++)
        if (*arr[temp2] == *arr[temp2 + 1]) {
            *arr[temp2] *= 2;
            score += *arr[temp2];
            *arr[temp2 + 1] = 1;
            break;
        }

    for (temp2 ++; temp2 < temp - 1; temp2 ++) {
        *arr[temp2] = *arr[temp2 + 1];
        *arr[temp2 + 1] = 1; 
    }

    return true;
}