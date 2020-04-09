//
// Created by ashraf on 25/03/2020.
//

#ifndef FOCUS_USERINTERFACE_H
#define FOCUS_USERINTERFACE_H

#include <ncurses.h>
#include "GAME_SETUP.h"

#define LOGO_HEIGHT 8
#define LOGO_WIDTH 50

#define PROMPT_HEIGHT 5
#define PROMPT_WIDTH 40

void drawLogo();
void promptName(char playername[], int i);

#endif //FOCUS_USERINTERFACE_H