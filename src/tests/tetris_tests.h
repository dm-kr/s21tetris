#ifndef TETRIS_TESTS_H
#define TETRIS_TESTS_H

#include <check.h>
#include <stdio.h>

#include "../brick_game/tetris/tetris_logic.h"
#include "../gui/cli/ui.h"

int matrix_eq(int **A, int **B, int x, int y);

Suite *suite_general(void);

void run_tests(int *number_all, int *number_failed);
void run_testcase(Suite *testcase, int *number_all, int *number_failed);

#endif