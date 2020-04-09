//
// Created by ashraf on 25/03/2020.
//
#include "UserInterface.h"

void drawLogo() {
    int maxScreenY, maxScreenX;
    getmaxyx(stdscr, maxScreenY, maxScreenX);
    WINDOW *logo = newwin(8, 50, 0, maxScreenX / 2 - 25);
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