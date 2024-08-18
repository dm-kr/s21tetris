#include "tetris_tests.h"

START_TEST(rotate_test_1) {
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

Suite *suite_rotate(void) {
  Suite *s = suite_create("\033[42mROTATE\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, rotate_test_1);

  suite_add_tcase(s, tcase);
  return s;
}