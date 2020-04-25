//
// Created by ashraf on 25/03/2020.
//

#ifndef FOCUS_USERINTERFACE_H
#define FOCUS_USERINTERFACE_H

#include <ncurses.h>
#include "GAME_SETUP.h"

void displayMessage(char *msg); // Displays a string to the screen, usually a warning

void drawLogo(); // Draws the Focus Logo to the screen

void drawRules(); // Draws the Rules to the screen

void displayRules(); // Deals with the functionality of clearing the screen in order to display the rules

void promptName(char playername[], int i); // Prompts the player for their name

void drawBoard(square board[BOARD_SIZE][BOARD_SIZE], GameState state); // Draws the board to the screen

void drawStack(square *piece); // Draws the stack of the current position

void drawWinner(Player winner); // Draws the winner to the screen

void displayPlayer(Player currentPlayer); // Displays the winning player and their stats to the screen

void deleteWindows(); // Functionality to clear and delete all the screens

void init_screens(); // Initialises our ncurses screen

#endif //FOCUS_USERINTERFACE_H