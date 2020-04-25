//
// Created by ashraf on 26/03/2020.
//

#ifndef FOCUS_GAME_SETUP_H
#define FOCUS_GAME_SETUP_H

#include "stdbool.h"

#define BOARD_SIZE 8
#define PLAYER_NUM 2

/*Defines a set of Colours users can choose from*/
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
    char player_name[15]; // Stores the players name
    int capturedPieces; //number of adversary's pieces captured;
    int graveyardPieces; //number of own pieces kept; Used for graveyard functionality
    Colour colour;//Player colour, let's them pick colours from the board
} Player;

/*Stack data structure based on a linked list*/
typedef struct piece_node {
    Colour colour;
    struct piece_node *next;
} piece_node;

typedef struct square {
    /*marks the size of the stack*/
    int height;
    /*Tells us whether the square is valid or not*/
    square_type type;
    /* marks top of the stack*/
    piece_node *head;

} square;

/*Stores the players and the games*/
typedef struct Game {
    square board[BOARD_SIZE][BOARD_SIZE];
    Player player[PLAYER_NUM];
} Game;

/*Holds current Game state*/
typedef struct GameState {
    int x;//Holds the current x coordinate
    int y;//Holds the current y coordinate

    bool moveMade;//Tells us whether a player has made a move, helps avoid computing the win condition a needless amount of times

    bool selected;//Holds whether or not a piece has been selected
    int selectedX;//Holds the current selected X piece
    int selectedY;//Holds the current selected Y piece

    /*Tells us the number of pieces each player can move*/
    int moveablePieces[PLAYER_NUM];

    /*Tells us which player turn it is, 0 for player 1, 1 for player 2*/
    int playerTurn;
} GameState;

Game init_game();

void set_empty(square *s);

#endif //FOCUS_GAME_SETUP_H
