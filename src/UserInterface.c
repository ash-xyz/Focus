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

void drawBoard(square board[BOARD_SIZE][BOARD_SIZE], GameState state) {
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
    colorCell(boardWin, 1 + 4 * state.y, 2 + 8 * state.x, COLOR_BLACK);// Colours the position our cursor is at
    if (state.selected == true) {
        colorCell(boardWin, 1 + 4 * state.selectedY, 2 + 8 * state.selectedX, BLUE);
    }
    wrefresh(boardWin);
}

void drawStack(square *piece) {
    wclear(stackWin);
    box(stackWin, 0, 0);
    piece_node *pointer = piece->head;

    for (int i = 2 * piece->height; i > 0; i -= 2) {
        wattron(stackWin, COLOR_PAIR(pointer->colour));
        mvwprintw(stackWin, STACK_HEIGHT - i, 1, "████████");
        wattroff(stackWin, COLOR_PAIR(pointer->colour));
        pointer = pointer->next;
    }
    wrefresh(stackWin);
}

void displayPlayer(Player currentPlayer) {
    wclear(playerStatus);
    wprintw(playerStatus, "Player: %s, ", currentPlayer.player_name);
    wattron(playerStatus, COLOR_PAIR(currentPlayer.colour));
    wprintw(playerStatus, "Colour: ████,");
    wattroff(playerStatus, COLOR_PAIR(currentPlayer.colour));
    wprintw(playerStatus, "Grave Size: %d", currentPlayer.graveyardPieces);
    wrefresh(playerStatus);
}

void displayMessage(char *msg) {
    wclear(messageBox);
    wprintw(messageBox, "%s", msg);
    wrefresh(messageBox);
}

void drawWinner(Player winner) {
    /*Gets screen Sizes*/
    int maxScreenX = getmaxx(stdscr);
    /*Declares screen*/
    WINDOW *winScreen = newwin(19, 40, LOGO_HEIGHT + 1, maxScreenX / 2 - 20);
    refresh();
    wprintw(winScreen, "         o  o   o  o\n"
                       "         |\\/ \\^/ \\/|\n"
                       "         |,-------.|\n"
                       "       ,-.(|)   (|),-.\n"
                       "       \\_*._ ' '_.* _/\n"
                       "        /`-.`--' .-'\\\n"
                       "   ,--./    `---'    \\,--.\n"
                       "   \\   |(  )     (  )|   /\n"
                       "    \\  | ||       || |  /\n"
                       "     \\ | /|\\     /|\\ | /\n"
                       "     /  \\-._     _,-/  \\\n"
                       "    //| \\\\  `---'  // |\\\\\n"
                       "   /,-.,-.\\       /,-.,-.\\\n"
                       "  o   o   o      o   o    o");
    wprintw(winScreen, "\nCongratulations %s!!\n", winner.player_name);
    wprintw(winScreen, "You're an absolute super star!\n"
                       "You took %d pieces from your opponent!\n", winner.capturedPieces);
    wprintw(winScreen, "All this ");
    wattron(winScreen, COLOR_PAIR(winner.colour));
    wprintw(winScreen, "████████");
    wattroff(winScreen, COLOR_PAIR(winner.colour));
    wprintw(winScreen, " coloured pieces");

    wrefresh(winScreen);
    getch();
    delwin(winScreen);
}