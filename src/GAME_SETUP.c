//
// Created by ashraf on 26/03/2020.
//
#include "GAME_SETUP.h"
#include <stdlib.h>

/*
 * This file aims to contain utility functions for the game.
 * */
void set_empty(square *s) {
    s->head = NULL;
    s->height = 0;
}

void set_green(square *s) {
    s->height = 1;
    s->head = (piece_node *) malloc(sizeof(piece_node));
    s->head->colour = GREEN;
    s->head->next = NULL;
}

void set_red(square *s) {
    s->height = 1;
    s->head = (piece_node *) malloc(sizeof(piece_node));
    s->head->colour = RED;
    s->head->next = NULL;
}
/*TODO*/
/*Make Function initialise Board*/
void init_board(square **board) {
    board = (struct square **) calloc(BOARD_SIZE, sizeof(struct square *));
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = (struct square *) calloc(8, sizeof(struct square));
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            /*
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7)))
                set_invalid(&game.board[i][j]);*/

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
/*TODO*/
/*Initialise Players*/
void init_player(Game* game, int playerNum)
{
}
Game init_game()
{
    Game game;
    init_board(game.board);

    for(int i = 0; i < 2;++i)
    {
        init_player(&game,i);
    }
    return game;
}