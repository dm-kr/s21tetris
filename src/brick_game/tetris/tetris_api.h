#ifndef TETRIS_API_H
#define TETRIS_API_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROWS 20
#define COLUMNS 10

typedef enum user_action {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef enum fsm {
  Init,
  Paused,
  Spawn,
  Moving,
  Shifting,
  Rotation,
  Attaching,
  Termination
} FSM_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum { Odd, Even } PieceType_t;

typedef struct {
  int **piece;
  PieceType_t type;
  int x;
  int y;
} Piece_t;

typedef struct {
  int ***pieces;
  int **backup;
  int **temp_field;
  Piece_t *piece;
  int next_index;
  FSM_t state;
  clock_t timer;
} GameState_t;

void copy_info(GameInfo_t *src, GameInfo_t *dst);
int **get_empty_field(void);
void copy_field(int **src, int **dst);
int **get_empty_piece(void);
void clear_piece(int **piece);
void clear_field(int **field);
void clear_gameinfo(void);
void clear_gamestate(void);
int ***get_pieces_array(void);
void find_edges(int **piece, int *x1, int *x2, int *y);
int check_collision(Piece_t piece);
int draw_piece(int **field, Piece_t piece);
void spawn_piece(GameState_t *state);
int move_piece(GameState_t *state, int dir);
void rotate_odd(Piece_t *piece, int **new);
void rotate_even(Piece_t *piece, int **new);
void rotate(Piece_t *piece);
void read_highscore(void);
void init_gameinfo(void);
Piece_t *init_piece(void);
GameState_t *init_gamestate(void);
GameState_t *get_gamestate(GameState_t *state);
void userInput(UserAction_t action, bool hold);
void shift_matrix_down(int start);
int check_lines(void);
void add_points(int lines);
void set_level(void);
void set_highscore(void);
void set_speed(void);
GameInfo_t updateCurrentState(void);

#endif