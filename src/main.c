#include <stdio.h>
#include "UserInterface.h"
#include "GAME_SETUP.h"
#include <locale.h>
int main() {
    setlocale(LC_ALL, "");

    Game game = init_game();
    print_board(game);
    return 0;
}