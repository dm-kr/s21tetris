#include "tetris_tests.h"

void run_tests(int *number_all, int *number_failed) {
  Suite *list_cases[] = {suite_rotate(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase, number_all, number_failed);
  }
}

void run_testcase(Suite *testcase, int *number_all, int *number_failed) {
  static int counter_testcase = 1;
  int failed = 0;
  int all = 0;
  if (counter_testcase > 0) putchar('\n');
  counter_testcase++;

  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  failed = srunner_ntests_failed(sr);
  all = srunner_ntests_run(sr);
  *number_failed += failed;
  *number_all += all;

  srunner_free(sr);
}

int main(void) {
  int number_all = 0;
  int number_failed = 0;
  run_tests(&number_all, &number_failed);
  int number_succeess = number_all - number_failed;
  printf(
      "\n===============================\nAll: %d, "
      "\033[32mSuccess: %d\033[0m, \033[31mFailed: "
      "%d\033[0m\n===============================\n",
      number_all, number_succeess, number_failed);
  return 0;
}
