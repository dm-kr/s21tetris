/**
 * @file tetris_logic.h
 * @author zolloalf
 * @brief A header file containing gamefield size defines and game logic
 * function declarations.
 * @date 2024-08-16
 * @copyright Copyright (c) 2024
 */

#ifndef TETRIS_LOGIC_H
#define TETRIS_LOGIC_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../types.h"

/**
 * @brief Number of rows in matrix, containing gamefield.
 */
#define ROWS 20
/**
 * @brief Number of columns in matrix, containing gamefield.
 */
#define COLUMNS 10

/**
 * @brief Copy all values from one GameInfo_t to another besides pointers.
 * @param src Value to copy.
 * @param dst Value where to copy.
 */
void copy_info(GameInfo_t *src, GameInfo_t *dst);

/**
 * @brief Get static GameState_t value or fill it with data from state param.
 * @param state Data to fill current gamestate (pass NULL to get existing data).
 */
GameState_t *get_gamestate(GameState_t *state);

/**
 * @brief Initialize a static GameInfo_t struct.
 */
void init_gameinfo();

/**
 * @brief Allocate memory for empty 2D array.
 * @param rows Number of rows.
 * @param cols Number of columns.
 */
int **get_empty_matrix(int rows, int cols);

/**
 * @brief Clear memory from 2D array.
 * @param matrix Matrix to clear.
 * @param rows Number of rows.
 */
void clear_matrix(int **matrix, int rows);

/**
 * @brief Copy values from one 2D array to another.
 * @param src Matrix to copy from.
 * @param dst Matrix to copy where.
 * @param rows Number of rows.
 * @param cols Number of columns.
 */
void copy_matrix(int **src, int **dst, int rows, int cols);

/**
 * @brief Clear memory from GameInfo_t struct.
 */
void clear_gameinfo();

/**
 * @brief Clear memory from GameState_t struct.
 */
void clear_gamestate();

/**
 * @brief Read tetromino shapes from yaml file to array of shapes.
 */
int ***get_pieces_array();

/**
 * @brief Find leftmost, rightmost and downmost coordinates of current tetromino
 * from upper left corner.
 * @param piece Tetromino to find edges.
 * @param x1 Pointer where to save leftmost coordinate.
 * @param x2 Pointer where to save rightmost coordinate.
 * @param y Pointer where to save downmost coordinate.
 */
void find_edges(int **piece, int *x1, int *x2, int *y);

/**
 * @brief Check if current position of tetromino is overlapping other tetrominos
 * or field edges.
 * @param field 2D array to check overlap with.
 * @param piece Tetromino to check overlap with.
 */
int is_overlapping(int **field, Piece_t piece);

/**
 * @brief Create projection of current piece at its lowest possible position.
 * @param field 2D array, containing gamefield to draw a projection.
 * @param piece Tetromino to draw.
 */
void ghost(int **field, Piece_t *piece);

/**
 * @brief Change color of the tetromino.
 * @param piece Tetromino to change color.
 * @param color New color.
 */
void paint_piece(int **piece, int color);

/**
 * @brief Draw next frame of the game if it's possible.
 * @param piece Current moving tetromino.
 */
int draw_next_frame(Piece_t piece);

/**
 * @brief Draw tetromino on the given field.
 * @param field 2D array to draw piece on.
 * @param piece Tetromino to draw.
 */
int draw_piece(int **field, Piece_t piece);

/**
 * @brief Spawn a new tetromino.
 * @param state Current state of the game.
 */
void spawn_piece(GameState_t *state);

/**
 * @brief Move piece in given direction if possible.
 * @param state Current state of the game.
 * @param dir Direction where to move piece (numbers are based on values of
 * corresponding user actions).
 */
int move_piece(GameState_t *state, int dir);

/**
 * @brief Rotate algorithm for 3x3 tetrominos.
 * @param piece Tetromino to rotate.
 * @param result Pointer to store rotated tetromino.
 */
void rotate_odd(Piece_t *piece, int **result);

/**
 * @brief Rotate algorithm for O and I tetrominos.
 * @param piece Tetromino to rotate.
 * @param result Pointer to store rotated tetromino.
 */
void rotate_even(Piece_t *piece, int **result);

/**
 * @brief Rotate given tetromino.
 * @param piece Tetromino to rotate.
 */
void rotate(Piece_t *piece);

/**
 * @brief Read hghscore from file.
 */
void read_highscore();

/**
 * @brief Initialize Piece_t struct.
 */
Piece_t *init_piece();

/**
 * @brief Initialize GameState_t struct.
 */
GameState_t *init_gamestate();

/**
 * @brief Clear all memory used by game.
 */
void clear_memory();

/**
 * @brief Shift gamefield 1 row down from given position.
 * @param start Row that needs to be overwritten.
 */
void shift_matrix_down(int start);

/**
 * @brief Check how many rows is filled.
 */
int check_lines();

/**
 * @brief Add points to game score based on filled rows count.
 * @param lines Number of filled rows.
 */
void add_points(int lines);

/**
 * @brief Set new level of difficulty based on current game score.
 */
void set_level();

/**
 * @brief Set new highscore if current score is biggen than highscore.
 */
void set_highscore();

/**
 * @brief Set new game speed based on level.
 */
void set_speed();

/**
 * @brief Drop tetromino to the lowest possible position.
 */
void drop_piece();

/**
 * @brief Perform operation based on player's action.
 * @param action Action, performed by user.
 * @param hold Indicator that button was holded, not pressed.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Update GameInfo_t static struct with new state of the game.
 */
GameInfo_t updateCurrentState();

#endif