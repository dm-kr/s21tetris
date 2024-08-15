#include "brick_game/tetris/tetris_api.h"
#include "gui/cli/ui.h"

void gameloop() {
  int pause = 1;
  int start = 0;
  int old_score = 0;
  GameInfo_t info;
  GameInfo_t empty = {0};
  UserAction_t action = Pause;
  render(empty);
  draw_start_menu();
  refresh();
  while (action != Terminate) {
    while (start == 0) {
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
    if (pause == 0) {
      userInput(action, true);
      info = updateCurrentState();
      if (info.score != old_score) {
        old_score = info.score;
        clear();
      }
      render(info);
      refresh();
    }
    if (info.speed == 0) {
      pause = 1;
      copy_info(&info, &empty);
      render(empty);
      draw_gameover(info);
    }
    action = get_action(getch());
  }
  userInput(action, true);
}

int main() {
  init();
  gameloop();
  close();
  return 0;
}