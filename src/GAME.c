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

void run_game(Game *game) {
    GameState state;
    state.x = state.y = 4;
    state.player1Top = state.player2Top = 18;
    state.playerTurn = 0;

    drawBoard(game->board, state);
    drawStack(&game->board[state.y][state.x]);
    do {
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
                    //TODO: Check that the move is valid (Use coordinates to do so)
                    //TODO: move piece if it's valid,
                    //TODO: alter number of player tops
                    //TODO: change player turn
                } else {
                    /*Checks if the piece is owned by the current player
                     * If so, it will highlight that piece and record the coordinates*/
                    if (checkOwnedPlayer(game, &state) == true) {
                        drawBoard(game->board, state);
                    }
                }
                break;
                //TODO: Build Graveyard and give the ability to move pieces from the graveyard
            default:
                break;
        }
    } while (state.player2Top != 0);

    delwin(boardWin);
    delwin(stackWin);
    endwin();
}