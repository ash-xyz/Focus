//
// Created by ashraf on 25/03/2020.
//
#include "UserInterface.h"
#include <string.h>

#define LOGO_HEIGHT 9
#define LOGO_WIDTH 50

#define PROMPT_HEIGHT 12
#define PROMPT_WIDTH 40

#define BOARD_WIDTH 65
#define BOARD_HEIGHT 33

#define STACK_WIDTH 10
#define STACK_HEIGHT 15

/*Used for the player and msg boxes*/
#define INFOBOX_HEIGHT 1
#define INFOBOX_WIDTH 50

#define RULE_WIDTH 68
#define RULE_HEIGHT 31

/*Global Variables that contain the windows for our board and stack*/
WINDOW *boardWin;
WINDOW *stackWin;
WINDOW *playerStatus;
WINDOW *messageBox;
WINDOW *logo;

/*Draws the Focus Logo to the screen*/
void drawLogo() {
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

/*Creates a window to draw the rules to*/
void drawRules() {
    int maxScreenX = getmaxx(stdscr);
    WINDOW *ruleWin = newwin(RULE_HEIGHT, RULE_WIDTH, 0, maxScreenX / 2 - RULE_WIDTH / 2);
    refresh();
    wprintw(ruleWin,
            "     _______________________________________________________\n"
            "    /\\                                                      \\\n"
            "(O)===)><><><><><><><><><><><><><><><><><><><><><><><><><><><)==(O)\n"
            "    \\/''''''''''''''''''''''''''''''''''''''''''''''''''''''/\n"
            "     )                   ___      _                         )\n"
            "    (                   | _ \\_  _| |___ ___                (\n"
            "     )                  |   / || | / -_|_-<                 )\n"
            "    (                   |_|_\\\\_,_|_\\___/__/                (\n"
            "                                                            \n"
            "     )                     How to play:                     )\n"
            "    (              Use the arrow keys to move              (\n"
            "     )    Press 'f' to select, unselect and place a piece   )\n"
            "    (   Press 'g' to resurrect a piece from your graveyard (\n"
            "\n"
            "     )   A stack can be moved if you own the topmost piece  )\n"
            "    (         When a stack lands on another stack,         (\n"
            "     )                the two stacks merge.                 )\n"
            "    (     If the new stack contains more than 5 pieces,    (\n"
            "     )            the bottom pieces are removed.            )\n"
            "\n"
            "    (         If a player's own piece is removed,          (\n"
            "     )   they are kept in a player's graveyard and may be   )\n"
            "    ( placed on the board later in lieu of moving a stack. (\n"
            "     )                                                      )\n"
            "\n"
            "    (   The last player who is able to move a stack wins.  (\n"
            "     )          Press 'h' to read the rules again.          )\n"
            "    (              Press any key to CONTINUE               (\n"
            "    /\\''''''''''''''''''''''''''''''''''''''''''''''''''''''\\    \n"
            "(O)===)><><><><><><><><><><><><><><><><><><><><><><><><><><><)==(O)\n"
            "    \\/______________________________________________________/");
    wrefresh(ruleWin);
    getch();

    werase(ruleWin);
    wrefresh(ruleWin);
    delwin(ruleWin);
}

/*Promps the player for their name*/
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
                       "    |          ~~~~~~~~          |.\n"
                       "    |                            |.\n"
                       "    |   _________________________|___\n"
                       "    |  /                            /.\n"
                       "    \\_/____________________________/.", i + 1);

    curs_set(1);// Turns on a cursor for the user to see where they are in the screen
    echo(); // Turns on the ability for the user to see what they typed
    wattron(promptWin, A_STANDOUT); // Makes the text the user enters standout

    mvwgetnstr(promptWin, 6, 15, playername, 8); // Takes input from the screen

    noecho(); // Turns off the ability for the user to see what they typed
    wattroff(promptWin, A_STANDOUT); // Turns off standout feature
    curs_set(0);//Turns off a cursor for the user to see where they are in the screen

    /*Deletes our window from the screen and memory*/
    werase(promptWin);
    wrefresh(promptWin);
    delwin(promptWin);
}

/*Colours the pieces in the baord*/
void colourCell(WINDOW *win, int locY, int locX, Colour colour, int height) {

    /*Outputs height of stack*/
    mvwprintw(win, locY, locX - 1, "%d", height);
    wattron(win, COLOR_PAIR(colour));
    /*Outputs the top piece of colour*/
    for (int i = 0; i < 3; i++) {
        mvwprintw(win, locY + i, locX, "█████");
    }
    wattroff(win, COLOR_PAIR(colour));
}

void drawBoard(square board[BOARD_SIZE][BOARD_SIZE], GameState state) {
    wclear(boardWin);//Clears the board screen
    wmove(boardWin, 0, 0);//Moves the cursor to 0,0
    /*Stores the template to our board*/
    const char *boardTemplate[] = {"                ╔═══════╦═══════╦═══════╦═══════╗                "
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
                                   "                ╚═══════╩═══════╩═══════╩═══════╝                "};
    /*Prints out the board line by line*/
    const int lineCount = sizeof(boardTemplate) / sizeof(boardTemplate[0]);
    for (int i = 0; i < lineCount; i++) {
        mvwprintw(boardWin, i, 0, boardTemplate[i]);
    }
    /*Colours each piece in the board*/
    for (int locY = 0; locY < BOARD_SIZE; locY++) {
        for (int locX = 0; locX < BOARD_SIZE; locX++) {
            if (board[locY][locX].type == VALID && board[locY][locX].head != NULL) {
                colourCell(boardWin, 1 + 4 * locY, 2 + 8 * locX, board[locY][locX].head->colour,
                           board[locY][locX].height);
            }
        }
    }
    /*Colours the square the player is currently at*/
    colourCell(boardWin, 1 + 4 * state.y, 2 + 8 * state.x, COLOR_BLACK,
               board[state.y][state.x].height);// Colours the position our cursor is at
    /*Colours the selected piece blue*/
    if (state.selected == true) {
        colourCell(boardWin, 1 + 4 * state.selectedY, 2 + 8 * state.selectedX, BLUE,
                   board[state.selectedY][state.selectedX].height);
    }
    wrefresh(boardWin);
}

/*Draws the stack of the current square*/
void drawStack(square *piece) {
    /*Clears teh stack window*/
    wclear(stackWin);
    wmove(boardWin, 0, 0);
    box(stackWin, 0, 0);// Draws a box around the window

    /*Goes through the stack one by one and prints out each piece*/
    piece_node *pointer = piece->head;
    for (int i = 2 * piece->height; i > 0; i -= 2) {
        wattron(stackWin, COLOR_PAIR(pointer->colour));
        mvwprintw(stackWin, STACK_HEIGHT - i, 1, "████████");
        wattroff(stackWin, COLOR_PAIR(pointer->colour));
        pointer = pointer->next;
    }
    wrefresh(stackWin);
}

/*Displays current player*/
void displayPlayer(Player currentPlayer) {
    wclear(playerStatus);
    int startOfString = INFOBOX_WIDTH / 2 - (38 + strlen(currentPlayer.player_name)) /
                                            2; //Calculates where to place our string in the window so that it's centered

    mvwprintw(playerStatus, 0, startOfString, "Player: %s, ", currentPlayer.player_name); // Prints the player name
    /*Prints the player colour*/
    wattron(playerStatus, COLOR_PAIR(currentPlayer.colour));
    wprintw(playerStatus, "Colour: ████,");
    wattroff(playerStatus, COLOR_PAIR(currentPlayer.colour));
    /*Prints the number of pieces each player has in their graveyard*/
    wprintw(playerStatus, "Grave Size: %d", currentPlayer.graveyardPieces);

    wrefresh(playerStatus);
}

/*Displays a message, usually a warning to the screen*/
void displayMessage(char *msg) {
    wclear(messageBox);
    int startOfString =
            INFOBOX_WIDTH / 2 - strlen(msg) / 2; // Calculates where to place the message so that it's centered
    mvwprintw(messageBox, 0, startOfString, "%s", msg);//Prints string to our messageBox window
    wrefresh(messageBox);
}

/*Deletes and clears windows from the screen, Windows: messageBox, playerStatus, boardWin, stackWin*/
void deleteWindows() {
    wclear(messageBox);
    wrefresh(messageBox);
    delwin(messageBox);
    wclear(playerStatus);
    wrefresh(playerStatus);
    delwin(playerStatus);
    wclear(boardWin);
    wrefresh(boardWin);
    delwin(boardWin);
    wclear(stackWin);
    wrefresh(stackWin);
    delwin(stackWin);
}

void drawWinner(Player winner) {
    /*Gets screen Sizes*/
    int maxScreenX = getmaxx(stdscr);
    /*Declares screen*/
    WINDOW *winScreen = newwin(19, 40, LOGO_HEIGHT + 1, maxScreenX / 2 - 20);
    refresh();
    /*Prints ascii art of a king frog*/
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
    /*Prints the details of the winning player*/
    wprintw(winScreen, "\nCongratulations %s!!\n", winner.player_name);
    wprintw(winScreen, "You're an absolute super star!\n"
                       "You took %d pieces from your opponent!\n", winner.capturedPieces);
    wprintw(winScreen, "All this ");
    /*Prints the winning player colour*/
    wattron(winScreen, COLOR_PAIR(winner.colour));
    wprintw(winScreen, "████████");
    wattroff(winScreen, COLOR_PAIR(winner.colour));
    wprintw(winScreen, " coloured pieces");

    wrefresh(winScreen);
    getch();
    delwin(winScreen);
}

/*Initialises our ncurses screens*/
void init_screens() {
    stdscr = initscr();//Initialises the large screen
    noecho();//Turns off echoing(Printing anything the user enters)
    cbreak();
    start_color();//Starts color functionality for the user
    curs_set(0);//Turns off the cursor
    keypad(stdscr, true);// Allows for special character input, e.g KEY_UP

    init_pair(RED, COLOR_RED, COLOR_BLACK);// Initialises the RED colour graphically
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);//Initialises the GREEN colour graphically
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);// Initialises the BLUE colour graphically

    int maxScreenX = getmaxx(stdscr);//Gets the max width of our screen,
    /*Initialises our various screens*/
    boardWin = newwin(BOARD_HEIGHT, BOARD_WIDTH, LOGO_HEIGHT + 2, maxScreenX / 2 - BOARD_WIDTH / 2);
    stackWin = newwin(STACK_HEIGHT, STACK_WIDTH, (LOGO_HEIGHT + 2) + (BOARD_HEIGHT / 2 - STACK_HEIGHT / 2),
                      maxScreenX / 2 + BOARD_WIDTH / 2 + 2);
    playerStatus = newwin(INFOBOX_HEIGHT, 50, LOGO_HEIGHT, maxScreenX / 2 - INFOBOX_WIDTH / 2);
    messageBox = newwin(INFOBOX_HEIGHT, 50, LOGO_HEIGHT + 1, maxScreenX / 2 - INFOBOX_WIDTH / 2);
    logo = newwin(LOGO_HEIGHT, LOGO_WIDTH, 0, maxScreenX / 2 - LOGO_WIDTH / 2);

    refresh();
}

/*Clears the windows to make room for the Rules*/
void displayRules() {
    werase(boardWin);
    werase(stackWin);
    werase(logo);
    wrefresh(logo);
    wrefresh(boardWin);
    wrefresh(stackWin);
    drawRules();
    drawLogo();
}