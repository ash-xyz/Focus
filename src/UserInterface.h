//
// Created by ashraf on 25/03/2020.
//

#ifndef FOCUS_USERINTERFACE_H
#define FOCUS_USERINTERFACE_H

#include <ncurses.h>
#include "GAME_SETUP.h"

void displayMessage(char *msg);

void drawLogo();

void displayRules(); // Deals with the functionality of clearing the screen in order to display the rules

void promptName(char playername[], int i);

void drawBoard(square board[BOARD_SIZE][BOARD_SIZE], GameState state);

void drawStack(square *piece);

void drawWinner(Player winner);

void displayPlayer(Player currentPlayer);

void deleteWindows();

void init_screens();

#endif //FOCUS_USERINTERFACE_H