#include "ui.h"

void init() {
  initscr();
  keypad(stdscr, TRUE);
  timeout(0);
  start_color();
  cbreak();
  noecho();
  curs_set(0);
  init_pair(-1, COLOR_BLACK, COLOR_WHITE);
  init_pair(0, COLOR_BLACK, COLOR_BLACK);
  init_pair(1, COLOR_BLACK, COLOR_RED);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  init_pair(3, COLOR_BLACK, COLOR_YELLOW);
  init_pair(4, COLOR_BLACK, COLOR_BLUE);
  init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(6, COLOR_BLACK, COLOR_CYAN);
  init_pair(8, COLOR_BLACK, 13);
  init_pair(9, COLOR_BLACK, 15);
}

UserAction_t get_action(int key) {
  UserAction_t action = 0;
  switch (key) {
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_UP:
      action = Up;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case ' ':
      action = Action;
      break;
    case 'p':
    case 'P':
      action = Pause;
      break;
    case 'q':
    case 'Q':
      action = Terminate;
      break;
    case 's':
    case 'S':
      action = Start;
      break;
    default:
      break;
  }
  return action;
}

void gameloop() {
  int key;
  int pause = 0;
  GameInfo_t info = updateCurrentState();
  render(info);
  refresh();
  do {
    UserAction_t action = get_action(key);
    if (action == Pause) {
      pause = 1 - pause;
    }
    userInput(action, true);
    if (pause == 0) {
      render(info);
      refresh();
      info = updateCurrentState();
    }
    if (info.speed == 0) {
      pause = 1;
    }
  } while ((key = getch()) != 'q');
}

void close() { endwin(); }

void draw_game_frame(int x, int y) {
  for (int i = 0; i < 21; ++i) {
    mvaddch(y + Y_START - 1, x + i + X_START, ACS_HLINE);
    mvaddch(y + 20 + Y_START, x + i + X_START, ACS_HLINE);
  }

  for (int i = 0; i < 20; ++i) {
    mvaddch(y + i + Y_START, x + X_START, ACS_VLINE);
    mvaddch(y + i + Y_START, x + 21 + X_START, ACS_VLINE);
  }

  mvaddch(y + Y_START - 1, x + X_START, ACS_ULCORNER);
  mvaddch(y + Y_START - 1, x + 21 + X_START, ACS_URCORNER);
  mvaddch(y + 20 + Y_START, x + X_START, ACS_LLCORNER);
  mvaddch(y + 20 + Y_START, x + 21 + X_START, ACS_LRCORNER);
}

void draw_menu_frame(int x, int y) {
  for (int i = 0; i < MENU_WIDTH; ++i) {
    mvaddch(y + Y_START - 1, x + i + X_START, ACS_HLINE);
    mvaddch(y + 20 + Y_START, x + i + X_START, ACS_HLINE);
  }

  for (int i = 0; i < 20; ++i) {
    mvaddch(y + i + Y_START, x + X_START, ACS_VLINE);
    mvaddch(y + i + Y_START, x + MENU_WIDTH + X_START, ACS_VLINE);
  }

  mvaddch(y + Y_START - 1, x + X_START, ACS_ULCORNER);
  mvaddch(y + Y_START - 1, x + MENU_WIDTH + X_START, ACS_URCORNER);
  mvaddch(y + 20 + Y_START, x + X_START, ACS_LLCORNER);
  mvaddch(y + 20 + Y_START, x + MENU_WIDTH + X_START, ACS_LRCORNER);
}

void draw_score(GameInfo_t info) {
  mvprintw(Y_START, GAME_WINDOW_WIDTH + X_START + 5, "SCORE:");
  mvprintw(Y_START + 1, GAME_WINDOW_WIDTH + X_START + 5, "%06d", info.score);
}

void draw_highscore(GameInfo_t info) {
  mvprintw(Y_START + 3, GAME_WINDOW_WIDTH + X_START + 3, "HIGHSCORE:");
  mvprintw(Y_START + 4, GAME_WINDOW_WIDTH + X_START + 5, "%06d",
           info.high_score);
}

void draw_next(GameInfo_t info) {
  mvprintw(Y_START + 6, GAME_WINDOW_WIDTH + X_START + 5, "NEXT:");
  for (int i = 1; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      draw_square(i + 7, j + 12, info.next[i][j]);
    }
  }
}

void draw_level(GameInfo_t info) {
  mvprintw(Y_START + 11, GAME_WINDOW_WIDTH + X_START + 5, "LEVEL:");
  mvprintw(Y_START + 12, GAME_WINDOW_WIDTH + X_START + 6, "%03d", info.level);
}

void draw_square(int y, int x, int color) {
  attron(COLOR_PAIR(color));
  mvprintw(y + Y_START, x * 2 + X_START + 1, "  ");
  attroff(COLOR_PAIR(color));
}

void draw_game_window(int x_start, int** field) {
  for (int i = 0; i < 20; ++i) {
    for (int j = x_start; j < 10 + x_start; ++j) {
      draw_square(i, j, field[i][j]);
    }
  }
}

void render(GameInfo_t info) {
  draw_game_window(0, info.field);
  draw_game_frame(0, 0);
  draw_score(info);
  draw_highscore(info);
  draw_next(info);
  draw_level(info);
  draw_menu_frame(X_MENU, 0);
}