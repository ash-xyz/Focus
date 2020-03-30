#include <stdio.h>
#include "UserInterface.h"
#include "GAME_SETUP.h"
#include <locale.h>
int main() {
    setlocale(LC_ALL, "");
    Game game = init_board();
    drawGame();
    return 0;
}