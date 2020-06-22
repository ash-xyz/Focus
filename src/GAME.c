//
// Created by ashraf on 07/04/2020.
//
#include "GAME.h"
#include "USER_INTERFACE.h"
#include <stdlib.h>

/*Checks if an upward move is valid*/
bool checkValidUp(GameState *state) {
    /*If the move is out of bounds it returns false*/
    if (state->y < 0 || (state->y == 0 && (state->x == 1 || state->x == 6)) ||
        (state->y == 1 && (state->x == 0 || state->x == 7))) {
        state->y++;
        return false;
    }
    return true;
}
/*Checks if a downward move is valid*/
bool checkValidDown(GameState *state) {
    /*If the move is out of bounds it returns false*/
    if (state->y > 7 || (state->y == 7 && (state->x == 1 || state->x == 6)) ||
        (state->y == 6 && (state->x == 0 || state->x == 7))) {
        state->y--;
        return false;
    }
    return true;
}
/*Checks if a rightward move is valid*/
bool checkValidRight(GameState *state) {
    /*If the move is out of bounds it returns false*/
    if (state->x > 7 || (state->x == 7 && (state->y == 1 || state->y == 6)) ||
        (state->x == 6 && (state->y == 0 || state->y == 7))) {
        state->x--;
        return false;
    }
    return true;
}

/*Checks if a leftward move is valid*/
bool checkValidLeft(GameState *state) {
    /*If the move is out of bounds it returns false*/
    if (state->x < 0 || (state->x == 0 && (state->y == 1 || state->y == 6)) ||
        (state->x == 1 && (state->y == 0 || state->y == 7))) {
        state->x++;
        return false;
    }
    return true;
}

/*Checks if a selected piece is owned by the player*/
bool checkOwnedPlayer(Game *game, GameState *state) {
    /*Checks if the square contains any pieces*/
    if (game->board[state->y][state->x].head == NULL) {
        displayMessage("You can't select a square with no pieces");
        return false;
    }
    /*If the player owns the piece, it is then marked as selected*/
    if (game->board[state->y][state->x].head->colour == game->player[state->playerTurn].colour) {
        state->selected = true;
        state->selectedX = state->x;
        state->selectedY = state->y;
        return true;
    }
    /*If the player doesn't control the square:*/
    displayMessage("You can't select a piece that isn't yours!");
    return false;
}

/*Checks if a piece move is valid(within bounds)*/
bool validMove(square board[BOARD_SIZE][BOARD_SIZE], GameState state) {
    /*Ensures that you are within bounds*/
    int height = board[state.selectedY][state.selectedX].height;//Gets the height of the selected square
    int numOfMoves = abs(state.selectedX - state.x) + abs(state.selectedY -
                                                          state.y);//Retrieves the distance between the selected square and current square
    /*If the height of the selected square is less than the distance between the two squares, we can't move*/
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
    /*Updates the number of moveable pieces*/
    /*If the receiving square is empty, there is no change in moveable pieces*/
    if (game->board[state->y][state->x].head != NULL) {
        /*If the receiving square is a different colour than the source square, the next player has less available pieces to move*/
        if (game->board[state->selectedY][state->selectedX].head->colour !=
            game->board[state->y][state->x].head->colour) {
            int nextPlayer = (state->playerTurn + 1) % 2;
            state->moveablePieces[nextPlayer]--;
        }
            /*If the player has moved a piece into a stack they control, the number of moveable pieces they have decreases*/
        else {
            state->moveablePieces[state->playerTurn]--;
        }
    }

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
void updateGameState(GameState *state, Game *game) {
    /*Changes player turn*/
    state->playerTurn++;
    state->playerTurn %= 2;
    /*Tells us that we have indeed made a move*/
    state->moveMade = true;
    /*Makes selected pieces invalid*/
    state->selected = false;
    /*Updates the player turn visuals*/
    displayPlayer(game->player[state->playerTurn]);
}

/*Resurrects a piece from a players graveyard*/
bool resurrectPiece(Game *game, GameState *state) {
    /*Updates number of moveable pieces */
    /*If we place a piece in an empty square, the number of moveable pieces increases*/
    if (game->board[state->y][state->x].head == NULL) {
        state->moveablePieces[state->playerTurn]++;
        printw("First");
    } else {
        /*If the receiving square is not owned by the player, we increase the  current player's moveable pieces and decrease the opponents*/
        if (game->board[state->y][state->x].head->colour != game->player[state->playerTurn].colour) {
            state->moveablePieces[state->playerTurn]++;
            int nextPlayer = (state->playerTurn + 1) % 2;
            state->moveablePieces[nextPlayer]--;
            printw("Second");
        }
    }
    printw("Moves %d %d", state->moveablePieces[0], state->moveablePieces[1]);
    /*Check if you have any graveyard pieces*/
    if (game->player[state->playerTurn].graveyardPieces > 0) {
        /*Initialises a piece of the players colour*/
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
bool continueGame(Game *game, GameState state) {
    //If we have pieces in the graveyard than we can still play
    if (game->player[state.playerTurn].graveyardPieces > 0)
        return true;
    /*If there are any moveable pieces on the baord then the game continues*/
    if (state.moveablePieces[state.playerTurn] > 0)
        return true;

    //If we don't have any pieces in the graveyard and we can't move any pieces in the board, we have lost :(
    return false;
}

// Frees any remaining pieces on the board
void freePieces(square board[BOARD_SIZE][BOARD_SIZE]) {
    /*Iterates through the board square by square */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            /*Only frees valid pieces on the board*/
            if (board[i][j].type == VALID) {
                /*Goes through stack one by one to free pieces*/
                while (board[i][j].head != NULL) {
                    piece_node *curPiece = board[i][j].head;
                    board[i][j].head = board[i][j].head->next;
                    free(curPiece);
                }
            }
        }
    }
}

void run_game(Game *game) {
    /*Initialises a variable to store the current state of our game */
    GameState state;
    state.x = state.y = 4; //Stores where the player is currently at
    state.playerTurn = 0; //Stores the player turn, 0 for player 1, 1 for player 2
    state.moveablePieces[0] = state.moveablePieces[1] = 18; //Stores the number of moveable pieces each player has

    /*Initially draws our UI*/
    drawBoard(game->board, state);
    drawStack(&game->board[state.y][state.x]);
    displayPlayer(game->player[state.playerTurn]);
    /*Loop that runs our game until it has terminated*/
    do {
        state.moveMade = false;//Tells us whether a player has made a move, helps avoid computing the win condition a needless amount of times
        bool redraw = false;//Tells us whether or not to redraw the board and screen
        /*Gets input from the keyboard*/
        switch (getch()) {
            /*Acts on player movement in a given direction*/
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
                /*Button to select, unselect and place  a piece down*/
            case 'f'  :
                if (state.selected == true) {
                    /*Unselect functionality - if you select a selected piece, it is unselected*/
                    if (state.x == state.selectedX && state.y == state.selectedY) {
                        state.selected = false;
                        drawBoard(game->board, state);
                    }
                        /*Checks whether placing a piece down is valid*/
                    else if (validMove(game->board, state)) {
                        /*IF it's valid it moves the stack to said the current square*/
                        movePieces(game, &state);
                        updateGameState(&state, game);//Updates the current game state, used to switch players
                        redraw = true;
                    }
                }
                    /*Selects a square*/
                else {
                    /*Checks if the selected piece is owned by the current player*/
                    if (checkOwnedPlayer(game, &state) == true) {
                        drawBoard(game->board, state);
                    }
                }
                break;
                /*Graveyard Functionality*/
            case 'g':
                /*Resurrects a piece from a players graveyard*/
                if (resurrectPiece(game, &state)) {
                    updateGameState(&state, game);
                    redraw = true;
                }
                break;
                /*Help button - Prints rules and instructions*/
            case 'h':
                displayRules();
                displayPlayer(game->player[state.playerTurn]);
                redraw = true;
            default:
                break;
        }
        /*Redraws the UI upon a valid key press*/
        if (redraw) {
            drawBoard(game->board, state);
            drawStack(&game->board[state.y][state.x]);
        }
    } while (state.moveMade == false || continueGame(game,
                                                     state));
    updateGameState(&state, game);//Switches the turn to our winner

    /*Deletes all our previously created windows*/
    deleteWindows();
    /*Frees allocated memory for the pieces*/
    freePieces(game->board);
    /*Draws the winner alongside their current info*/
    drawWinner(game->player[state.playerTurn]);//Draws a screen with our winner
    /*Ends ncurses screen*/
    endwin();
}