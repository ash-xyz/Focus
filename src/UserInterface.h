//
// Created by ashraf on 25/03/2020.
//

#ifndef FOCUS_USERINTERFACE_H
#define FOCUS_USERINTERFACE_H

#include <ncurses.h>
#include "GAME_SETUP.h"

#define LOGO_HEIGHT 8
#define LOGO_WIDTH 50

#define PROMPT_HEIGHT 12
#define PROMPT_WIDTH 40

#define BOARD_WIDTH 65
#define BOARD_HEIGHT 33

#define STACK_WIDTH 10
#define STACK_HEIGHT 15

void drawLogo();
void promptName(char playername[], int i);
void drawBoard(WINDOW *boardWin, square board[BOARD_SIZE][BOARD_SIZE], GameState state);
void drawStack(WINDOW *stackWin, square *piece);

#endif //FOCUS_USERINTERFACE_H