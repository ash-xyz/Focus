#include <stdio.h>
#include "UserInterface.h"
#include "GAME_SETUP.h"
#include "GAME.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");

    Game game = init_game();
    return 0;
}