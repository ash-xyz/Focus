//
// Created by ashraf on 26/03/2020.
//
#include "GAME_SETUP.h"
#include <stdlib.h>
#include "UserInterface.h"

/*
 * This file aims to contain utility functions for the game.
 * */
void set_empty(square *s) {
    s->type = VALID;
    s->head = NULL;
    s->height = 0;
}

void set_invalid(square *s) {
    s->type = INVALID;
    s->head = NULL;
    s->height = 0;
}

void set_green(square *s) {
    s->type = VALID;
    s->height = 1;
    s->head = (piece_node *) malloc(sizeof(piece_node));
    s->head->colour = GREEN;
    s->head->next = NULL;
}

void set_red(square *s) {
    s->type = VALID;
    s->height = 1;
    s->head = (piece_node *) malloc(sizeof(piece_node));
    s->head->colour = RED;
    s->head->next = NULL;
}

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
            else{
                //squares with red pieces
                if((i%2 == 1 && (j < 3 || j> 4)) ||
                   (i%2 == 0 && (j == 3 || j==4)))
                    set_red(&board[i][j]);
                    //green squares
                else set_green(&board[i][j]);
            }
        }
    }
}
/*TODO*/
/*Initialise Players*/
void init_player(game *game, int playerNum) {
    promptName(game->player[playerNum].player_name, playerNum);
    game->player[playerNum].colour = playerNum == 0 ? RED : GREEN;//Sets player colour
    game->player[playerNum].numOfPieces = 0;//Sets the initial number of pieces a player has
    game->player[playerNum].opponentPieces = 0;//Sets the initial number of opponent
}

game init_game() {
    stdscr = initscr();
    noecho();
    cbreak();
    start_color();
    keypad(stdscr, true);

    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(BLUE,COLOR_BLUE,COLOR_BLACK);
    drawLogo();//Draws Logo onto the screen
    game game;
    init_board(game.board);
    for (int i = 0; i < PLAYER_NUM; ++i) {
        init_player(&game, i);
    }
    return game;
}