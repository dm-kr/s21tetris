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

#include "ui.h"

void init();
UserAction_t get_action(int key);
void gameloop();
void close();

void draw_gameover(GameInfo_t info);
void draw_start_menu();
void draw_pause();
void draw_frame(int x, int y, int width, int height);
void draw_score(GameInfo_t info);
void draw_highscore(GameInfo_t info);
void draw_next(GameInfo_t info);
void draw_level(GameInfo_t info);
void draw_square(int y, int x, int color);
void draw_game_window(int x_start, int** field);

void render(GameInfo_t info);

#endif