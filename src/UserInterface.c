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

void colorCell(WINDOW *win, int locY, int locX, Colour colour) {

    wattron(win, COLOR_PAIR(colour));
    for (int i = 0; i < 3; i++) {
        mvwprintw(win, locY + i, locX, "█████");
    }
    wattroff(win, COLOR_PAIR(colour));
}

void drawBoard(WINDOW *boardWin, square board[BOARD_SIZE][BOARD_SIZE], int y, int x) {
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

    for (int locY = 0; locY < BOARD_SIZE; locY++) {
        for (int locX = 0; locX < BOARD_SIZE; locX++) {
            if (board[locY][locX].type == VALID && board[locY][locX].head != NULL) {
                colorCell(boardWin, 1 + 4 * locY, 2 + 8 * locX, board[locY][locX].head->colour);
            }
        }
    }
    colorCell(boardWin, 1 + 4 * y, 2 + 8 * x, COLOR_BLACK);
    wrefresh(boardWin);
}

void drawStack(WINDOW *stackWin, square *piece) {
    wclear(stackWin);
    box(stackWin, 0, 0);
    piece_node *pointer = piece->head;
    for (int i = piece->height; i > 0; i--) {
        wattron(stackWin, COLOR_PAIR(pointer->colour));
        mvwprintw(stackWin, i, 1, "█████");
        wattroff(stackWin, COLOR_PAIR(pointer->colour));
        pointer = pointer->next;
    }
    wrefresh(stackWin);
}