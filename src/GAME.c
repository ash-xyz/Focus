//
// Created by ashraf on 07/04/2020.
//
#include "GAME.h"
#include "UserInterface.h"
#include <stdlib.h>

bool checkValidUp(GameState *state) {
    if (state->y < 0 || (state->y == 0 && (state->x == 1 || state->x == 6)) ||
        (state->y == 1 && (state->x == 0 || state->x == 7))) {
        state->y++;
        return false;
    }
    return true;
}

bool checkValidDown(GameState *state) {
    if (state->y > 7 || (state->y == 7 && (state->x == 1 || state->x == 6)) ||
        (state->y == 6 && (state->x == 0 || state->x == 7))) {
        state->y--;
        return false;
    }
    return true;
}

bool checkValidRight(GameState *state) {
    if (state->x > 7 || (state->x == 7 && (state->y == 1 || state->y == 6)) ||
        (state->x == 6 && (state->y == 0 || state->y == 7))) {
        state->x--;
        return false;
    }
    return true;
}

bool checkValidLeft(GameState *state) {
    if (state->x < 0 || (state->x == 0 && (state->y == 1 || state->y == 6)) ||
        (state->x == 1 && (state->y == 0 || state->y == 7))) {
        state->x++;
        return false;
    }
    return true;
}

bool checkOwnedPlayer(Game *game, GameState *state) {
    if (game->board[state->y][state->x].head == NULL) {
        /*TODO: Output message to box saying you're selecting a missing piece*/
        return false;
    }
    if (game->board[state->y][state->x].head->colour == game->player[state->playerTurn].colour) {
        state->selected = true;
        state->selectedX = state->x;
        state->selectedY = state->y;
        return true;
    }
    printw("You selected a piece that isn't your own! Player %d", state->playerTurn);
    /*TODO: Output message to a box if you're selecting a piece that isn't your own*/
    return false;
}

bool validMove(square board[BOARD_SIZE][BOARD_SIZE], GameState state) {
    /*Ensures you can't move to the same position*/
    if (state.x == state.selectedX && state.y == state.selectedY)
        return false;
    /*Ensures that you are within bounds*/
    int height = board[state.selectedY][state.selectedX].height;
    int numOfMoves = abs(state.selectedX - state.x) + abs(state.selectedY - state.y);
    /*TODO: Output message to a box to state that the move is not valid*/
    return height >= numOfMoves;
}

//Trims piece down to a height of 5
void trimStack(square *s, Player *player) {
    /*Only trims pieces down to a height of 5*/
    if (s->height > 5) {
        /*Creates a pointer that skips directly to the 5th node*/
        piece_node *curNode = s->head->next->next->next->next->next;
        /*Loops through and trims the stack accordingly*/
        while (curNode != NULL) {
            /*Temporary pointer so that we can free it later*/
            piece_node *temp = curNode;
            /*Increments the current pointer*/
            curNode = curNode->next;
            /*If the player owns the piece, we increment their graveyard pieces(To be used for graveyard functionality)*/
            if (temp->colour == player->colour) {
                player->graveyardPieces++;
                free(temp);
            } else {
                player->capturedPieces++;
                free(temp);
            }
        }
        //Ends our new stack with a null and sets the new height to 5
        s->head->next->next->next->next->next = NULL;
        s->height = 5;
    }
}

void movePieces(Game *game, GameState *state) {
    int heightOfSource = game->board[state->selectedY][state->selectedX].height;

    /*Finds the bottom of our source stack*/
    piece_node *bottomOfSource = game->board[state->selectedY][state->selectedX].head;
    for (int i = heightOfSource; i > 1; i--) {
        bottomOfSource = bottomOfSource->next;
    }
    /*Connects the bottom of our source with the top of our destination*/
    bottomOfSource->next = game->board[state->y][state->x].head;
    /*Makes our source head the new destination head*/
    game->board[state->y][state->x].head = game->board[state->selectedY][state->selectedX].head;
    /*Sets our source to NULL*/
    set_empty(&game->board[state->selectedY][state->selectedX]);

    //Change our game height
    game->board[state->y][state->x].height += heightOfSource;

    //Ensures our stack stays at size of 5
    trimStack(&game->board[state->y][state->x], &game->player[state->playerTurn]);
}

/*Updates the game following a player move*/
void updateGameState(GameState *state) {
    /*Changes player turn*/
    state->playerTurn++;
    state->playerTurn %= 2;
    /*Makes selected pieces invalid*/
    state->selected = false;
    /*TODO: Output to text box the current players turn and their colour */
}

/*Resurrects a piece from a players graveyard*/
bool resurrectPiece(Game *game, GameState *state) {
    if (game->player[state->playerTurn].graveyardPieces > 0) {
        /*Initialises a piece of the players color*/
        piece_node *resurrectedPiece = (piece_node *) malloc(sizeof(piece_node));
        resurrectedPiece->colour = game->player[state->playerTurn].colour;

        /*Makes the resurrected piece the new head*/
        resurrectedPiece->next = game->board[state->y][state->x].head;
        game->board[state->y][state->x].head = resurrectedPiece;

        /*Changes our counters for the stack height and the graveyard */
        game->board[state->y][state->x].height++;
        game->player[state->playerTurn].graveyardPieces--;

        //Ensures our stack stays at size of 5
        trimStack(&game->board[state->y][state->x], &game->player[state->playerTurn]);
        return true;
    } else {
        //TODO: OUTPUT MESSAGE SAYING YOU'RE NOT ALLOWED TO DO THAT YOU HAVE NO PIECES
        printw("Now now bois");
        return false;
    }
}

void run_game(Game *game) {
    GameState state;
    state.x = state.y = 4;
    state.playerTurn = 0;

    /*TODO: REMOVE LATER; USED FOR TESTING*/
    piece_node *curNode = game->board[4][4].head;
    for (int i = 0; i < 5; i++) {
        curNode->next = (piece_node *) malloc(sizeof(piece_node));
        curNode = curNode->next;
        curNode->colour = RED; //i % 2 == 0 ? RED : GREEN;
    }
    curNode->next = NULL;
    game->board[4][4].height = 6;

    drawBoard(game->board, state);
    drawStack(&game->board[state.y][state.x]);
    do {
        printw("PLayer  %d", state.playerTurn);
        switch (getch()) {
            case KEY_UP:
                state.y--;
                if (checkValidUp(&state)) {
                    drawBoard(game->board, state);
                    drawStack(&game->board[state.y][state.x]);
                }
                break;
            case KEY_DOWN:
                state.y++;
                if (checkValidDown(&state)) {
                    drawBoard(game->board, state);
                    drawStack(&game->board[state.y][state.x]);
                }
                break;
            case KEY_LEFT:
                state.x--;
                if (checkValidLeft(&state)) {
                    drawBoard(game->board, state);
                    drawStack(&game->board[state.y][state.x]);
                }
                break;
            case KEY_RIGHT:
                state.x++;
                if (checkValidRight(&state)) {
                    drawBoard(game->board, state);
                    drawStack(&game->board[state.y][state.x]);
                }
                break;
            case 'f'  :
                if (state.selected == true) {
                    if (validMove(game->board, state)) {
                        printw("valid");
                        movePieces(game, &state);
                        updateGameState(&state);//Updates the current gamestate
                        drawBoard(game->board, state);
                        drawStack(&game->board[state.y][state.x]);
                    } else
                        printw("not valid");
                } else {
                    /*Checks if the piece is owned by the current player
                     * If so, it will highlight that piece and record the coordinates*/
                    if (checkOwnedPlayer(game, &state) == true) {
                        drawBoard(game->board, state);
                    }
                }
                break;
            case 'g':
                //TODO: Build Graveyard and give the ability to move pieces from the graveyard.
                // Suggestion: Add to the game state a counter to keep track of the number of pieces a player has in the graveyard
                // Remember to keep stack of size 5
                if (resurrectPiece(game, &state)) {
                    updateGameState(&state);
                    drawBoard(game->board, state);
                    drawStack(&game->board[state.y][state.x]);
                }
                break;
            default:
                break;
        }
    } while (state.x !=
             -1);//TODO: Implement wincondition, where graveyard pieces are 0 and they have no pieces they can move on the board

    delwin(boardWin);
    delwin(stackWin);
    endwin();
}