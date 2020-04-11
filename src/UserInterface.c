//
// Created by ashraf on 25/03/2020.
//
#include "UserInterface.h"

void drawLogo() {
    int maxScreenX = getmaxx(stdscr);

    WINDOW *logo = newwin(LOGO_HEIGHT, LOGO_WIDTH, 0, maxScreenX / 2 - LOGO_WIDTH / 2);
    refresh();

    wprintw(logo, " /$$$$$$$$                                     \n"
                  "| $$_____/                                     \n"
                  "| $$     /$$$$$$   /$$$$$$$ /$$   /$$  /$$$$$$$\n"
                  "| $$$$$ /$$__  $$ /$$_____/| $$  | $$ /$$_____/\n"
                  "| $$__/| $$  \\ $$| $$      | $$  | $$|  $$$$$$ \n"
                  "| $$   | $$  | $$| $$      | $$  | $$ \\____  $$\n"
                  "| $$   |  $$$$$$/|  $$$$$$$|  $$$$$$/ /$$$$$$$/\n"
                  "|__/    \\______/  \\_______/ \\______/ |_______/");
    wrefresh(logo);
}

void promptName(char playername[], int i) {

    /*Gets screen Sizes*/
    int maxScreenX = getmaxx(stdscr);
    /*Declares screen*/
    WINDOW *promptWin = newwin(PROMPT_HEIGHT, PROMPT_WIDTH, LOGO_HEIGHT + 1, maxScreenX / 2 - PROMPT_WIDTH / 2);

    refresh();
    wrefresh(promptWin);
    wprintw(promptWin, "   ______________________________\n"
                       " / \\                             \\.\n"
                       "|   |     Welcome, player %d!     |.\n"
                       " \\_ |                            |.\n"
                       "    |      Enter your name:      |.\n"
                       "    |                            |.\n"
                       "    |      ~~~~~~~~~~~~~~~~~     |.\n"
                       "    |                            |.\n"
                       "    |   _________________________|___\n"
                       "    |  /                            /.\n"
                       "    \\_/____________________________/.", i + 1);


    echo();
    wattron(promptWin, A_STANDOUT);

    mvwgetnstr(promptWin, 6, 11, playername, 19);

    noecho();
    wattroff(promptWin, A_STANDOUT);

    werase(promptWin);
    wrefresh(promptWin);
    delwin(promptWin);
}

void colorCell(WINDOW *win, int locX, int locY, Colour colour) {

    wattron(win, COLOR_PAIR(colour));
    for (int i = 0; i < 3; i++) {

        //mvwhline(win, locY + i, locX, '#', 5);
        mvwprintw(win, locY + i, locX, "█████");
    }
    wattroff(win, COLOR_PAIR(colour));
}

void drawBoard(WINDOW *boardWin, square board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    wclear(boardWin);

    wprintw(boardWin,
            "                ╔═══════╦═══════╦═══════╦═══════╗                "
            "                ║       ║       ║       ║       ║                "
            "                ║       ║       ║       ║       ║                "
            "                ║       ║       ║       ║       ║                "
            "        ╔═══════╬═══════╬═══════╬═══════╬═══════╬═══════╗        "
            "        ║       ║       ║       ║       ║       ║       ║        "
            "        ║       ║       ║       ║       ║       ║       ║        "
            "        ║       ║       ║       ║       ║       ║       ║        "
            "╔═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╗"
            "║       ║       ║       ║       ║       ║       ║       ║       ║"
            "║       ║       ║       ║       ║       ║       ║       ║       ║"
            "║       ║       ║       ║       ║       ║       ║       ║       ║"
            "╠═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╣"
            "║       ║       ║       ║       ║       ║       ║       ║       ║"
            "║       ║       ║       ║       ║       ║       ║       ║       ║"
            "║       ║       ║       ║       ║       ║       ║       ║       ║"
            "╠═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╣"
            "║       ║       ║       ║       ║       ║       ║       ║       ║"
            "║       ║       ║       ║       ║       ║       ║       ║       ║"
            "║       ║       ║       ║       ║       ║       ║       ║       ║"
            "╠═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╣"
            "║       ║       ║       ║       ║       ║       ║       ║       ║"
            "║       ║       ║       ║       ║       ║       ║       ║       ║"
            "║       ║       ║       ║       ║       ║       ║       ║       ║"
            "╚═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╝"
            "        ║       ║       ║       ║       ║       ║       ║        "
            "        ║       ║       ║       ║       ║       ║       ║        "
            "        ║       ║       ║       ║       ║       ║       ║        "
            "        ╚═══════╬═══════╬═══════╬═══════╬═══════╬═══════╝        "
            "                ║       ║       ║       ║       ║                "
            "                ║       ║       ║       ║       ║                "
            "                ║       ║       ║       ║       ║                "
            "                ╚═══════╩═══════╩═══════╩═══════╝                ");

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].type == VALID && board[i][j].head != NULL) {
                colorCell(boardWin, 2 + 8 * i, 1 + 4 * j, board[i][j].head->colour);
            }
        }
    }
    colorCell(boardWin, 2 + 8 * x, 1 + 4 * y, COLOR_BLACK);
    wrefresh(boardWin);
}