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
Game init_board()
{
    /*
    struct square **board = (struct square **) calloc(BOARD_SIZE, sizeof(struct square *));
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = (struct square *) calloc(8, sizeof(struct square));
    }*/
}
/*TODO*/
/*Initialise Players*/

/*TODO*/
/*Make Function to delete the cells at the bottom of a stack*/

