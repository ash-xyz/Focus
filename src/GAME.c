//
// Created by ashraf on 07/04/2020.
//
#include "GAME.h"
#include "UserInterface.h"

void run_game(Game *game) {
    int maxScreenX = getmaxx(stdscr);
    WINDOW *boardWin = newwin(BOARD_HEIGHT, BOARD_WIDTH, LOGO_HEIGHT + 1, maxScreenX / 2 - BOARD_WIDTH / 2);
    refresh();

    int x = 4, y = 4;
    drawBoard(boardWin, game->board, x, y);
    do {
        switch (getch()) {
            case KEY_UP:
                y--;
                drawBoard(boardWin, game->board, x, y);
                break;
            case KEY_DOWN:
                y++;
                drawBoard(boardWin, game->board, x, y);;
                break;
            case KEY_LEFT:
                x--;
                drawBoard(boardWin, game->board, x, y);
                break;
            case KEY_RIGHT:
                x++;
                drawBoard(boardWin, game->board, x, y);
                break;
            case KEY_ENTER  :
                x++;
                break;
            default:
                break;
        }
    } while (x != 0);

    delwin(boardWin);
}