//
// Created by ashraf on 25/03/2020.
//
#include <ncurses.h>
#include <unistd.h>

#define DELAY 3000

void drawGame() {

    int x = 0, y = 0;
    int max_y = 0, max_x = 0;
    int next_x = 0;
    int direction = 1;

    initscr();
    noecho();
    curs_set(FALSE);

    // Global var `stdscr` is created by the call to `initscr()`
    getmaxyx(stdscr, max_y, max_x);

    while(1) {
        clear();
        mvprintw(y, x, "╀");
        refresh();

        usleep(DELAY);

    }

    endwin();
}