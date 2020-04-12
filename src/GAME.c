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

void run_game(game *game) {
    int maxScreenX = getmaxx(stdscr);
    WINDOW *boardWin = newwin(BOARD_HEIGHT, BOARD_WIDTH, LOGO_HEIGHT + 1, maxScreenX / 2 - BOARD_WIDTH / 2);
    WINDOW *stackWin = newwin(STACK_HEIGHT, STACK_WIDTH, (LOGO_HEIGHT + 1) + (BOARD_HEIGHT / 2 - STACK_HEIGHT / 2),
                              maxScreenX / 2 + BOARD_WIDTH / 2 + 2);
    refresh();

    GameState state;
    state.x = state.y = 4;
    state.player1Top = state.player2Top = 18;

    drawBoard(boardWin, game->board, state);
    drawStack(stackWin, &game->board[state.y][state.x]);
    do {
        switch (getch()) {
            case KEY_UP:
                state.y--;
                if (checkValidUp(&state)) {
                    drawBoard(boardWin, game->board, state);
                    drawStack(stackWin, &game->board[state.y][state.x]);
                }
                printw("x:%d y:%d", state.x, state.y);
                break;
            case KEY_DOWN:
                state.y++;
                if (checkValidDown(&state)) {
                    drawBoard(boardWin, game->board, state);
                    drawStack(stackWin, &game->board[state.y][state.x]);
                }
                break;
            case KEY_LEFT:
                state.x--;
                if (checkValidLeft(&state)) {
                    drawBoard(boardWin, game->board, state);
                    drawStack(stackWin, &game->board[state.y][state.x]);
                }
                break;
            case KEY_RIGHT:
                state.x++;
                if (checkValidRight(&state)) {
                    drawBoard(boardWin, game->board, state);
                    drawStack(stackWin, &game->board[state.y][state.x]);
                }
                break;
            case 'f'  :
                state.selectedX = state.x;
                state.selectedY = state.y;
                state.selected = true;
                drawBoard(boardWin, game->board, state);
                break;
            default:
                break;
        }
    } while (state.player2Top != 0);

    delwin(boardWin);
    delwin(stackWin);
    endwin();
}