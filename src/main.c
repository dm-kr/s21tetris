#include "brick_game/tetris/tetris_api.h"
#include "gui/cli/ui.h"

int main() {
  GameInfo_t info = updateCurrentState();
  init();
  gameloop(info);
  close();
  // printf("%d", info.level);
  return 0;
}