#include "game.h"

int main() {
    initialize();
    guide();
    while (true) {
        Stage stage;
        stage.background();        
        do {
            stage.print();
            if (stage.win()) {stage.printWin(); break;}
            if (stage.lose()) {stage.printLose(); break;}
        } while (stage.update(GetOperation()));
    }
    return 0;
}