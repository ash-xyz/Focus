//
// Created by ashraf on 25/03/2020.
//
#include <ncurses.h>
void drawGame() {
    initscr();            /* Start curses mode 		  */
    printw("Hello World !!!");    /* Print Hello World		  */
    refresh();            /* Print it on to the real screen */
    getch();            /* Wait for user input */
    endwin();            /* End curses mode		  */
}