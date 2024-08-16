#include "brick_game/tetris/tetris_logic.h"
#include "gui/cli/ui.h"

void gameloop() {
  int pause = 1;
  int start = 0;
  int old_score = 0;
  GameInfo_t info;
  GameInfo_t empty = {0};
  UserAction_t action = Pause;
  draw_start_menu();
  while (action != Terminate) {
    while (start == 0 && action != Terminate) {
      if (action == Start) {
        start = 1;
        pause = 0;
      }
      action = get_action(getch());
      userInput(action, true);
    }
    if (action == Pause && start == 1) {
      pause = 1 - pause;
      draw_pause();
    }
    if (pause == 0 && start == 1) {
      userInput(action, true);
      info = updateCurrentState();
      if (info.score != old_score) {
        old_score = info.score;
        clear();
      }
      render(info);
      if (info.speed == 0) {
        pause = 1;
        start = 0;
        copy_info(&info, &empty);
        render(empty);
        draw_gameover(info);
      }
    }
    if (action != Terminate) {
      action = get_action(getch());
    }
  }
}

int main() {
  init();
  gameloop();
  close();
  return 0;
}