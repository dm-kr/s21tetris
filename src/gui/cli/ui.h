/**
 * @file ui.h
 * @author zolloalf
 * @brief A header file containing graphic defines and graphic function
 * declarations.
 * @date 2024-08-16
 * @copyright Copyright (c) 2024
 */

#ifndef UI_H
#define UI_H

#include <ncurses.h>

#include "../../brick_game/tetris/tetris_logic.h"
#include "../../types.h"

/**
 * @brief Leftmost coordinate of the playfield.
 */
#define X_START 1
/**
 * @brief Upmost coordinate of the playfield.
 */
#define Y_START 1
/**
 * @brief Width of the game window.
 */
#define GAME_WINDOW_WIDTH 21
/**
 * @brief X start position of the game info panel.
 */
#define X_MENU 22
/**
 * @brief Width of the game info panel.
 */
#define MENU_WIDTH 13

#include "ui.h"

/**
 * @brief Initialize game window (including setting of all needed window
 * settings).
 */
void init();

/**
 * @brief Get UserAction_t enum value depending on the pressed key.
 * @param key Pressed key.
 */
UserAction_t get_action(int key);

/**
 * @brief Run game process loop.
 */
void gameloop();

/**
 * @brief Close game window.
 */
void close();

/**
 * @brief Draw final game information.
 * @param info Struct with the game information.
 */
void draw_gameover(GameInfo_t info);

/**
 * @brief Draw frame with instructions to start a game.
 */
void draw_start_menu();

/**
 * @brief Draw "PAUSE" text and frame.
 */
void draw_pause();

/**
 * @brief Draw frame at given coordinates.
 * @param x Start coordinate of X axis.
 * @param y Start coordinate of Y axis.
 * @param width Width of frame.
 * @param height Height of frame.
 */
void draw_frame(int x, int y, int width, int height);

/**
 * @brief Draw current game score count.
 * @param info Struct with the game information.
 */
void draw_score(GameInfo_t info);

/**
 * @brief Draw current highscore value.
 * @param info Struct with the game information.
 */
void draw_highscore(GameInfo_t info);

/**
 * @brief Draw image of the next piece to appear.
 * @param info Struct with the game information.
 */
void draw_next(GameInfo_t info);

/**
 * @brief Draw current level of difficulty value.
 * @param info Struct with the game information.
 */
void draw_level(GameInfo_t info);

/**
 * @brief Draw single square of given color.
 * @param y Y coordinate of the square.
 * @param x X coordinate of the square.
 * @param color Color of the square.
 */
void draw_square(int y, int x, int color);

/**
 * @brief Draw current state of the game.
 * @param x_start Start coordinate of X axis.
 * @param field 2D int array with colors of each square on the gamefield.
 */
void draw_game_window(int x_start, int** field);

/**
 * @brief Draw all the components of the playfield and sidebar with game
 * information.
 * @param info Struct with the game information.
 */
void render(GameInfo_t info);

#endif