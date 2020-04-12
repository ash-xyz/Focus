//
// Created by ashraf on 26/03/2020.
//

#ifndef FOCUS_GAME_SETUP_H
#define FOCUS_GAME_SETUP_H

#include "stdbool.h"

#define BOARD_SIZE 8
#define PLAYER_NUM 2

/*Defines a set of Colors users can choose from*/
typedef enum {
    RED = 1,
    GREEN,
    BLUE
} Colour;

// Square types
//INVALID: squares that are on the sides and where no piece can be placed
//VALID: squares where it is possible to place a piece or a stack
typedef enum square_type {
    VALID,
    INVALID
} square_type;

typedef struct Player {
    char player_name[20];
    int opponentPieces; //number of adversary's pieces captured
    int numOfPieces; //number of own pieces kept
    Colour colour;
} Player;

/*Stack data structure based on a linked list*/
typedef struct piece_node {
    Colour colour;
    struct piece_node *next;
} piece_node;

typedef struct square {
    /*marks the size of the stack*/
    int height;
    square_type type;
    /* marks top of the stack*/
    piece_node *head;

} square;

typedef struct Game {
    square board[BOARD_SIZE][BOARD_SIZE];
    Player player[PLAYER_NUM];
} game;

/*Holds current game state*/
typedef struct GameState {
    int x;//Holds the current x coordinate
    int y;//Holds the current y coordinate

    bool selected;//Holds whether or not a piece has been selected
    int selectedX;//Holds the current selected X piece
    int selectedY;//Holds the current selected Y piece

    /*Used for win condition*/
    int player1Top;//Holds how many pieces player 1 has on top
    int player2Top;//Holds how many pieces player 2 has on top
} GameState;

game init_game();

#endif //FOCUS_GAME_SETUP_H
