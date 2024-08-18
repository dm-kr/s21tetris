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
 * @param speed Current tetromino fall rate.
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
 * @param piece 2D int array, containing tetromino's shape.
 * @param type Enum, defining type of the tetromino to choose rotation logic.
 * @param x Position of the tetromino by X axis.
 * @param y Position of the tetromino by Y axis.
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
 * @param pieces Array of all possible tetromino shapes.
 * @param backup 2D int array, containing field state before last tetromino was
 * placed.
 * @param temp_field 2D int array, contating current state of the field, which
 * is used for drawing a new position of moving tetromino and collision
 * checking.
 * @param piece Pointer to a struct, that contains information of current moving
 * tetromino.
 * @param next_index Random number in range [0, 6] used for determining a next
 * tetromino to appear.
 * @param state Enum, describing current state of the game.
 * @param timer Clock_t value, containint previous time when tetromino has
 * moved down.
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