//
// Created by ashraf on 26/03/2020.
//
#include "GAME_SETUP.h"
#include <stdlib.h>
#include "USER_INTERFACE.h"

/*
 * This file aims to contain utility functions for the Game.
 * */

/*Initialise a square to empty*/
void set_empty(square *s) {
    s->type = VALID;
    s->head = NULL;
    s->height = 0;
}

/*Sets a square as invalid*/
void set_invalid(square *s) {
    s->type = INVALID;
    s->head = NULL;
    s->height = 0;
}

/*Sets a square to be a green piece*/
void set_green(square *s) {
    s->type = VALID;
    s->height = 1;
    s->head = (piece_node *) malloc(sizeof(piece_node));
    s->head->colour = GREEN;
    s->head->next = NULL;
}

/*Sets a square to be a red piece*/
void set_red(square *s) {
    s->type = VALID;
    s->height = 1;
    s->head = (piece_node *) malloc(sizeof(piece_node));
    s->head->colour = RED;
    s->head->next = NULL;
}

/*Initialises our board*/
void init_board(square board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {

            //invalid squares
            if ((i == 0 && (j == 0 || j == 1 || j == 6 || j == 7)) ||
                (i == 1 && (j == 0 || j == 7)) ||
                (i == 6 && (j == 0 || j == 7)) ||
                (i == 7 && (j == 0 || j == 1 || j == 6 || j == 7))) {
                set_invalid(&board[i][j]);
            }

            //squares with no pieces
            if (i == 0 || i == 7 || j == 0 || j == 7)
                set_empty(&board[i][j]);
            else {
                //squares with red pieces
                if ((i % 2 == 1 && (j < 3 || j > 4)) ||
                    (i % 2 == 0 && (j == 3 || j == 4)))
                    set_red(&board[i][j]);
                    //green squares
                else set_green(&board[i][j]);
            }
        }
    }
}

/*Initialise Players*/
void init_player(Game *game, int playerNum) {
    promptName(game->player[playerNum].player_name, playerNum);// Prompts user for their name
    game->player[playerNum].colour = playerNum == 0 ? RED : GREEN;//Sets player colour
    game->player[playerNum].graveyardPieces = 0;//Sets the number of own pieces captured to 0
    game->player[playerNum].capturedPieces = 0;//Sets the number of pieces captured from the opponent to 0
}

Game init_game() {
    init_screens(); // Initialises our ncurses screen
    drawRules(); // Draws the rules
    drawLogo();//Draws Logo onto the screen
    Game game;//Initialises a game type
    init_board(game.board);// Initialises the baord for our game
    /*Initialises the players*/
    for (int i = 0; i < PLAYER_NUM; ++i) {
        init_player(&game, i);
    }
    return game;
}