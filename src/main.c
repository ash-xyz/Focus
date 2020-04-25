#include <stdio.h>
#include "UserInterface.h"
#include "GAME_SETUP.h"
#include "GAME.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");//Used for unicode functionality
    Game game = init_game();//Initialises our game
    run_game(&game);//Runs the game
    return 0;
}