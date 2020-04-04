//
// Created by ashraf on 26/03/2020.
//

#ifndef FOCUS_GAME_SETUP_H
#define FOCUS_GAME_SETUP_H
#define BOARD_SIZE 8


/*Defines a set of Colors users can choose from*/
typedef enum {
    RED,
    GREEN
} Colour;

// Square types
//INVALID: squares that are on the sides and where no piece can be placed
//VALID: squares where it is possible to place a piece or a stack
typedef enum square_type {
    VALID,
    INVALID
}square_type;

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
    Player player[2];
} Game;

Game init_game();

#endif //FOCUS_GAME_SETUP_H
