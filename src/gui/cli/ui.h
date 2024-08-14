#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include <time.h>

#include "../../brick_game/tetris/tetris_api.h"

#define X_START 1
#define Y_START 1
#define GAME_WINDOW_WIDTH 21

#define X_MENU 22
#define MENU_WIDTH 13

void init();
void gameloop();
void close();
void draw_square(int start_x, int start_y, int color);
void render(GameInfo_t info);

#endif