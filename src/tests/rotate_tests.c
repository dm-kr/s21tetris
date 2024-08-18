#include "tetris_tests.h"

START_TEST(rotate_test_1) {
  userInput(Start, true);
  Piece_t *p = init_piece();
  p->type = Odd;
  int **expected = get_empty_matrix(4, 4);
  p->piece[1][1] = 1;
  p->piece[2][0] = 1;
  p->piece[2][1] = 1;
  p->piece[3][1] = 1;
  expected[1][1] = 1;
  expected[2][0] = 1;
  expected[2][1] = 1;
  expected[2][2] = 1;
  rotate(p);
  ck_assert_int_eq(1, matrix_eq(p->piece, expected, 4, 4));
  clear_matrix(expected, 4);
  clear_matrix(p->piece, 4);
  free(p);
}
END_TEST

START_TEST(rotate_test_2) {
  Piece_t *p = init_piece();
  p->type = Even;
  int **expected = get_empty_matrix(4, 4);
  p->piece[1][0] = 1;
  p->piece[1][1] = 1;
  p->piece[1][2] = 1;
  p->piece[1][3] = 1;
  expected[0][2] = 1;
  expected[1][2] = 1;
  expected[2][2] = 1;
  expected[3][2] = 1;
  rotate(p);
  ck_assert_int_eq(1, matrix_eq(p->piece, expected, 4, 4));
  clear_matrix(expected, 4);
  clear_matrix(p->piece, 4);
  free(p);
}
END_TEST

START_TEST(line_clear_test_1) {
  GameInfo_t info = get_info();
  GameState_t *state = get_gamestate(NULL);
  int start = 19;
  for (int i = start; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      info.field[i][j] = 1;
    }
  }
  state->state = Attaching;
  updateCurrentState();
  int result = 1;
  for (int i = start; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      result &= info.field[i][j] == 0 || info.field[i][j] == 100;
    }
  }
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(line_clear_test_2) {
  GameInfo_t info = get_info();
  GameState_t *state = get_gamestate(NULL);
  int start = 18;
  for (int i = start; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      info.field[i][j] = 1;
    }
  }
  state->state = Attaching;
  updateCurrentState();
  int result = 1;
  for (int i = start; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      result &= info.field[i][j] == 0 || info.field[i][j] == 100;
    }
  }
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(line_clear_test_3) {
  GameInfo_t info = get_info();
  GameState_t *state = get_gamestate(NULL);
  int start = 17;
  for (int i = start; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      info.field[i][j] = 1;
    }
  }
  state->state = Attaching;
  updateCurrentState();
  int result = 1;
  for (int i = start; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      result &= info.field[i][j] == 0 || info.field[i][j] == 100;
    }
  }
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(line_clear_test_4) {
  GameInfo_t info = get_info();
  GameState_t *state = get_gamestate(NULL);
  int start = 16;
  for (int i = start; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      info.field[i][j] = 1;
    }
  }
  state->state = Attaching;
  updateCurrentState();
  int result = 1;
  for (int i = start; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      result &= info.field[i][j] == 0 || info.field[i][j] == 100;
    }
  }
  updateCurrentState();
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(line_clear_test_5) {
  GameInfo_t info = get_info();
  GameState_t *state = get_gamestate(NULL);
  for (int k = 0; k < 9; ++k) {
    int start = 16;
    for (int i = start; i < ROWS; ++i) {
      for (int j = 0; j < COLUMNS; ++j) {
        info.field[i][j] = 1;
      }
    }
    state->state = Attaching;
    updateCurrentState();
  }
  info = get_info();
  ck_assert_int_eq(10, info.level);
}
END_TEST

START_TEST(line_clear_test_6) {
  GameInfo_t info = get_info();
  GameState_t *state = get_gamestate(NULL);
  int start = 19;
  drop_piece();
  state->state = Attaching;
  updateCurrentState();
  int result = 1;
  for (int i = start; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      result &= info.field[i][j] == 0 || info.field[i][j] == 100;
    }
  }
  updateCurrentState();
  ck_assert_int_eq(0, result);
}
END_TEST

START_TEST(gameloop_test_1) {
  clear_gamefield();
  GameState_t *state = get_gamestate(NULL);
  state->state = Moving;
  spawn_piece(state);
  GameInfo_t info = updateCurrentState();
  state = get_gamestate(NULL);
  int y = state->piece->y;
  while (clock() - state->timer <= info.speed) {
  }
  updateCurrentState();
  state = get_gamestate(NULL);
  ck_assert_int_eq(state->piece->y, y + 1);
}
END_TEST

START_TEST(gameloop_test_2) {
  clear_gamefield();
  GameState_t *state = get_gamestate(NULL);
  state->state = Moving;
  spawn_piece(state);
  updateCurrentState();
  state = get_gamestate(NULL);
  int y = state->piece->y;
  napms(1);
  updateCurrentState();
  state = get_gamestate(NULL);
  ck_assert_int_eq(state->piece->y, y);
}
END_TEST

START_TEST(gameloop_test_3) {
  clear_gamefield();
  GameState_t *state = get_gamestate(NULL);
  state->state = Moving;
  spawn_piece(state);
  for (int i = 0; i < 4; ++i) {
    add_points(4);
  }
  GameInfo_t info = updateCurrentState();
  for (int i = 0; i < 20; ++i) {
    while (clock() - state->timer <= info.speed) {
    }
    if (state->state == Attaching) {
      add_points(1);
    }
    info = updateCurrentState();
  }
  ck_assert_int_ne(info.score, 0);
}
END_TEST

START_TEST(spawn_test_1) {
  clear_gamefield();
  GameState_t *state = get_gamestate(NULL);
  spawn_piece(state);
  int error = spawn_piece(state);
  userInput(Start, true);
  state = get_gamestate(NULL);
  ck_assert_int_eq(error, 1);
  state->state = Moving;
}

START_TEST(move_test_1) {
  clear_gamefield();
  GameState_t *state = get_gamestate(NULL);
  state->state = Moving;
  state->next_index = 1;
  spawn_piece(state);
  int move_error = 0;
  int rotate_error = 0;
  for (int i = 0; i < 10; ++i) {
    move_error |= move_piece(state, 3);
    rotate_error |= rotate(state->piece);
  }
  ck_assert_int_eq(move_error, 1);
  ck_assert_int_eq(rotate_error, 1);
  state->state = Moving;
}
END_TEST

START_TEST(move_test_2) {
  clear_gamefield();
  GameState_t *state = get_gamestate(NULL);
  state->state = Moving;
  state->next_index = 0;
  spawn_piece(state);
  int move_error = 0;
  int rotate_error = 0;
  for (int i = 0; i < 10; ++i) {
    move_error |= move_piece(state, 4);
    rotate_error |= rotate(state->piece);
  }
  ck_assert_int_eq(move_error, 1);
  ck_assert_int_eq(rotate_error, 1);
  state->state = Moving;
}
END_TEST

START_TEST(action_test_0) {
  GameState_t *state = get_gamestate(NULL);
  userInput(Start, true);
  ck_assert_int_ne(state->state, Init);
}
END_TEST

START_TEST(action_test_1) {
  userInput(Pause, true);
  GameInfo_t info = get_info();
  userInput(Pause, true);
  ck_assert_int_eq(info.pause, 1);
}
END_TEST

START_TEST(action_test_2) {
  userInput(Left, true);
  GameState_t *state = get_gamestate(NULL);
  ck_assert_int_eq(state->state, Moving);
}
END_TEST

START_TEST(action_test_3) {
  userInput(Right, true);
  GameState_t *state = get_gamestate(NULL);
  ck_assert_int_eq(state->state, Moving);
}
END_TEST

START_TEST(action_test_4) {
  userInput(Down, true);
  GameState_t *state = get_gamestate(NULL);
  ck_assert_int_eq(state->state, Attaching);
}
END_TEST

START_TEST(action_test_5) {
  userInput(Action, true);
  GameState_t *state = get_gamestate(NULL);
  ck_assert_int_eq(state->state, Moving);
}
END_TEST

START_TEST(action_test_6) {
  GameInfo_t info = get_info();
  userInput(Terminate, true);
  info = get_info();
  ck_assert_int_eq(info.score, 0);
}
END_TEST

START_TEST(copy_info_test_1) {
  GameInfo_t info1 = {0};
  GameInfo_t info2 = {0};
  info1.level = 4;
  info1.pause = 0;
  info1.score = 0;
  info1.speed = 0;
  copy_info(&info1, &info2);
  ck_assert_int_eq(info1.level, info2.level);
}
END_TEST

START_TEST(clear_state_test_1) {
  GameState_t *state = calloc(1, sizeof(GameState_t));
  state->backup = NULL;
  state->piece = NULL;
  state->temp_field = NULL;
  state->pieces = NULL;
  GameState_t *state2 = get_gamestate(state);
  clear_gamestate(state2);
}
END_TEST

Suite *suite_general(void) {
  Suite *s = suite_create("\033[42mTETRIS LOGIC\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, rotate_test_1);
  tcase_add_test(tcase, rotate_test_2);
  tcase_add_test(tcase, line_clear_test_1);
  tcase_add_test(tcase, line_clear_test_2);
  tcase_add_test(tcase, line_clear_test_3);
  tcase_add_test(tcase, line_clear_test_4);
  tcase_add_test(tcase, line_clear_test_5);
  tcase_add_test(tcase, line_clear_test_6);
  tcase_add_test(tcase, gameloop_test_1);
  tcase_add_test(tcase, gameloop_test_2);
  tcase_add_test(tcase, gameloop_test_3);
  tcase_add_test(tcase, spawn_test_1);
  tcase_add_test(tcase, move_test_1);
  tcase_add_test(tcase, move_test_2);
  tcase_add_test(tcase, action_test_0);
  tcase_add_test(tcase, action_test_1);
  tcase_add_test(tcase, action_test_2);
  tcase_add_test(tcase, action_test_3);
  tcase_add_test(tcase, action_test_4);
  tcase_add_test(tcase, action_test_5);
  tcase_add_test(tcase, action_test_6);
  tcase_add_test(tcase, copy_info_test_1);
  tcase_add_test(tcase, clear_state_test_1);

  suite_add_tcase(s, tcase);
  return s;
}