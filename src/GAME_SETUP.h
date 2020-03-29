//
// Created by ashraf on 26/03/2020.
//

#ifndef FOCUS_GAME_SETUP_H
#define FOCUS_GAME_SETUP_H

/*Defines a set of Colors users can choose from*/
typedef enum {
    RED,
    GREEN
} Colour;

typedef struct player {
    char player_name[20];
    int opponentPieces; //number of adversary's pieces captured
    int numOfPieces; //number of own pieces kept
    Colour colour;
} player;

/*Stack datastructure based on a linked list*/
typedef struct piece_node {
    Colour *colour;
    struct piece_node *next;
} piece_node;

typedef struct square {
    /*marks the size of the stack*/
    int height;
    /* marks top of the stack*/
    piece_node *head;
} square;

#endif //FOCUS_GAME_SETUP_H
