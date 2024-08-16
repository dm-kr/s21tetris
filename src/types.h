/**
 * @file types.h
 * @author zolloalf
 * @brief A header file containing types for brickgame project.
 * @date 2024-08-16
 * @copyright Copyright (c) 2024
 */

#ifndef TYPES_H
#define TYPES_H

#include <time.h>

/**
 * @brief Enum, consisting of various actions user can perform.
 */
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

/**
 * @brief Enum, consisting of different states of the game.
 */
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

/**
 * @brief Enum, consisting of two types of tetromino.
 */
typedef enum { Odd, Even } PieceType_t;

/**
 * @brief Struct, containing game information to show on screen.
 * @param field 2D int array with colors of each square on the gamefield.
 * @param next 2D int array, containing current tetromino's shape.
 * @param score Score value.
 * @param high_score highscore value.
 * @param level Level value (max level is 10).
 * @param speed Current piece fall rate.
 * @param pause
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @brief Struct, containing information about tetromino.
 */
typedef struct {
  int **piece;
  PieceType_t type;
  int x;
  int y;
} Piece_t;

/**
 * @brief Struct, containing various informations of the current state of the
 * game.
 */
typedef struct {
  int ***pieces;
  int **backup;
  int **temp_field;
  Piece_t *piece;
  int next_index;
  FSM_t state;
  clock_t timer;
} GameState_t;

#endif