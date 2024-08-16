#ifndef TETRIS_LOGIC_H
#define TETRIS_LOGIC_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../types.h"

#define ROWS 20
#define COLUMNS 10

void copy_info(GameInfo_t *src, GameInfo_t *dst);
GameState_t *get_gamestate(GameState_t *state);
void init_gameinfo();
int **get_empty_field();
void copy_field(int **src, int **dst);
int **get_empty_piece();
void copy_piece(int **src, int **dst);
void clear_piece(int **piece);
void clear_field(int **field);
void clear_gameinfo();
void clear_gamestate();
void clear_memory();
int ***get_pieces_array();
void find_edges(int **piece, int *x1, int *x2, int *y);
int is_overlapping(int **field, Piece_t piece);
void ghost(int **field, Piece_t *piece);
void paint_piece(int **piece, int color);
int check_collision(Piece_t piece);
int draw_piece(int **field, Piece_t piece);
void spawn_piece(GameState_t *state);
int move_piece(GameState_t *state, int dir);
void rotate_odd(Piece_t *piece, int **result);
void rotate_even(Piece_t *piece, int **result);
void rotate(Piece_t *piece);
void read_highscore();
void shift_matrix_down(int start);
int check_lines();
void add_points(int lines);
void set_level();
void set_highscore();
void set_speed();
void drop_piece();
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif