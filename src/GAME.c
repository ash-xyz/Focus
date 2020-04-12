//
// Created by ashraf on 07/04/2020.
//
#include "GAME.h"
#include "UserInterface.h"
#include <stdlib.h>
void run_game(game *game) {
    int maxScreenX = getmaxx(stdscr);
    WINDOW *boardWin = newwin(BOARD_HEIGHT, BOARD_WIDTH, LOGO_HEIGHT + 1, maxScreenX / 2 - BOARD_WIDTH / 2);
    WINDOW *stackWin = newwin(STACK_HEIGHT, STACK_WIDTH, (LOGO_HEIGHT + 1) + (BOARD_HEIGHT / 2 - STACK_HEIGHT / 2),
                              maxScreenX / 2 + BOARD_WIDTH / 2 + 2);
    refresh();

    GameState state;
    state.x = 4;
    state.y = 4;
    state.player1Top = 18;
    state.player2Top = 18;
    drawBoard(boardWin, game->board, state);
    drawStack(stackWin, &game->board[state.y][state.x]);
    do {
        switch (getch()) {
            case KEY_UP:
                state.y--;
                drawBoard(boardWin, game->board, state);
                drawStack(stackWin, &game->board[state.y][state.x]);
                break;
            case KEY_DOWN:
                state.y++;
                drawBoard(boardWin, game->board, state);;
                drawStack(stackWin, &game->board[state.y][state.x]);
                break;
            case KEY_LEFT:
                state.x--;
                drawBoard(boardWin, game->board, state);
                drawStack(stackWin, &game->board[state.y][state.x]);
                break;
            case KEY_RIGHT:
                state.x++;
                drawBoard(boardWin, game->board, state);
                drawStack(stackWin, &game->board[state.y][state.x]);
                break;
            case KEY_ENTER  :
                state.x++;
                break;
            default:
                break;
        }
    } while (state.player2Top != 0);

    delwin(boardWin);
    delwin(stackWin);
    endwin();
}