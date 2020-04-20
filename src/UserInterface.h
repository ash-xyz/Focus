//
// Created by ashraf on 25/03/2020.
//

#ifndef FOCUS_USERINTERFACE_H
#define FOCUS_USERINTERFACE_H

#include <ncurses.h>
#include "GAME_SETUP.h"

#define LOGO_HEIGHT 9
#define LOGO_WIDTH 50

#define PROMPT_HEIGHT 12
#define PROMPT_WIDTH 40

#define BOARD_WIDTH 65
#define BOARD_HEIGHT 33

#define STACK_WIDTH 10
#define STACK_HEIGHT 15

/*Used for the player and msg boxes*/
#define INFOBOX_HEIGHT 1
#define INFOBOX_WIDTH 50

/*Global Variables that contain the windows for our board and stack*/
/*Initialised in GAME_SETUP.c, game_int*/
WINDOW *boardWin;
WINDOW *stackWin;
WINDOW *playerStatus;
WINDOW *messageBox;

void displayMessage(char *msg);

void drawLogo();

void drawRules();

void displayRules(); // Deals with the functionality of clearing the screen in order to display the rules

void promptName(char playername[], int i);

void drawBoard(square board[BOARD_SIZE][BOARD_SIZE], GameState state);

void drawStack(square *piece);

void drawWinner(Player winner);

void displayPlayer(Player currentPlayer);

void deleteWindows();

void init_screens();

#endif //FOCUS_USERINTERFACE_H