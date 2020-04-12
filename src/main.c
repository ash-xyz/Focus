#include <stdio.h>
#include "UserInterface.h"
#include "GAME_SETUP.h"
#include "GAME.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    game game = init_game();
    run_game(&game);
    return 0;
}