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
} GameState_t;

int **get_empty_field();
int **get_empty_piece();
void clear_gameinfo(GameInfo_t info);
void clear_pieces(int ***pieces);
int ***get_pieces_array();
int check_collision(Piece_t piece);
int draw_piece(int **field, Piece_t piece);
void spawn_piece(GameState_t *state);
int move_piece(GameState_t state, int dir);
void init_gameinfo();
GameState_t *get_gamestate();
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif