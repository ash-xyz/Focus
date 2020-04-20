//
// Created by ashraf on 07/04/2020.
//
#include "GAME.h"
#include "UserInterface.h"
#include <stdlib.h>

/*Checks if an upward move is valid*/
bool checkValidUp(GameState *state) {
    if (state->y < 0 || (state->y == 0 && (state->x == 1 || state->x == 6)) ||
        (state->y == 1 && (state->x == 0 || state->x == 7))) {
        state->y++;
        return false;
    }
    return true;
}
/*Checks if a downward move is valid*/
bool checkValidDown(GameState *state) {
    if (state->y > 7 || (state->y == 7 && (state->x == 1 || state->x == 6)) ||
        (state->y == 6 && (state->x == 0 || state->x == 7))) {
        state->y--;
        return false;
    }
    return true;
}
/*Checks if a rightward move is valid*/
bool checkValidRight(GameState *state) {
    if (state->x > 7 || (state->x == 7 && (state->y == 1 || state->y == 6)) ||
        (state->x == 6 && (state->y == 0 || state->y == 7))) {
        state->x--;
        return false;
    }
    return true;
}

/*Checks if a leftward move is valid*/
bool checkValidLeft(GameState *state) {
    if (state->x < 0 || (state->x == 0 && (state->y == 1 || state->y == 6)) ||
        (state->x == 1 && (state->y == 0 || state->y == 7))) {
        state->x++;
        return false;
    }
    return true;
}

/*Checks if a selected piece is owned by the player*/
bool checkOwnedPlayer(Game *game, GameState *state) {
    if (game->board[state->y][state->x].head == NULL) {
        displayMessage("You can't select a square with no pieces");
        return false;
    }
    if (game->board[state->y][state->x].head->colour == game->player[state->playerTurn].colour) {
        state->selected = true;
        state->selectedX = state->x;
        state->selectedY = state->y;
        return true;
    }
    displayMessage("You can't select a piece that isn't yours!");
    return false;
}

/*Checks if a piece move is valid(within bounds)*/
bool validMove(square board[BOARD_SIZE][BOARD_SIZE], GameState state) {
    /*Ensures that you are within bounds*/
    int height = board[state.selectedY][state.selectedX].height;
    int numOfMoves = abs(state.selectedX - state.x) + abs(state.selectedY - state.y);
    if (height < numOfMoves) {
        displayMessage("You can't move that far!");
    }
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

/*Moves the the stack in one board from one position to another*/
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

/*Updates the game following a player move, used to switch player turn*/
void updateGameState(GameState *state) {
    /*Changes player turn*/
    state->playerTurn++;
    state->playerTurn %= 2;
    /*Tells us that we have indeed made a move*/
    state->moveMade = true;
    /*Makes selected pieces invalid*/
    state->selected = false;
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
        displayMessage("You don't have any pieces in your graveyard!");
        return false;
    }
}

/*Tells us whether or not we should continue the game*/
bool continueGame(Game *game, int playerTurn) {
    //If we have pieces in the graveyard than we can still play
    if (game->player[playerTurn].graveyardPieces > 0)
        return true;

    //Otherwise we check if there are still any pieces that we can move, if so that we can continue playing
    Colour currentPlayerColour = game->player[playerTurn].colour;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j].type == VALID && game->board[i][j].head != NULL &&
                game->board[i][j].head->colour == currentPlayerColour) {
                return true;
            }
        }
    }
    //If we don't have any pieces in the graveyard and we can't move any pieces in the board, we have lost :(
    return false;
}

void run_game(Game *game) {
    GameState state;
    state.x = state.y = 4;
    state.playerTurn = 0;

    drawBoard(game->board, state);
    drawStack(&game->board[state.y][state.x]);
    do {
        state.moveMade = false;//Tells us whether a player has made a move, helps avoid computing the win condition a needless amount of times
        bool redraw = false;
        displayPlayer(game->player[state.playerTurn]);
        switch (getch()) {
            case KEY_UP:
                state.y--;
                redraw = checkValidUp(&state);
                break;
            case KEY_DOWN:
                state.y++;
                redraw = checkValidDown(&state);
                break;
            case KEY_LEFT:
                state.x--;
                redraw = checkValidLeft(&state);
                break;
            case KEY_RIGHT:
                state.x++;
                redraw = checkValidRight(&state);
                break;
            case 'f'  :
                if (state.selected == true) {
                    /*Unselects a piece*/
                    if (state.x == state.selectedX && state.y == state.selectedY) {
                        state.selected = false;
                        drawBoard(game->board, state);
                    } else if (validMove(game->board, state)) {
                        movePieces(game, &state);
                        updateGameState(&state);//Updates the current game state, used to switch players
                        redraw = true;
                    }
                } else {
                    /*Checks if the piece is owned by the current player
                     * If so, it will highlight that piece and record the coordinates*/
                    if (checkOwnedPlayer(game, &state) == true) {
                        drawBoard(game->board, state);
                    }
                }
                break;
            case 'g':
                /*Resurrects a piece from a players graveyard*/
                if (resurrectPiece(game, &state)) {
                    updateGameState(&state);
                    redraw = true;
                }
                break;
            case 'h':
                displayRules();
                redraw = true;
            default:
                break;
        }
        if (redraw) {
            drawBoard(game->board, state);
            drawStack(&game->board[state.y][state.x]);
        }
    } while (state.moveMade == false || continueGame(game,
                                                     state.playerTurn));
    updateGameState(&state);//Switches the turn to our winner

    /*Deletes all our previously created windows*/
    deleteWindows();

    drawWinner(game->player[state.playerTurn]);//Draws a screen with our winner

    endwin();
}