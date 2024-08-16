#include "ui.h"

void init() {
  initscr();
  keypad(stdscr, TRUE);
  timeout(0);
  start_color();
  cbreak();
  noecho();
  curs_set(0);
  init_pair(100, COLOR_BLACK, COLOR_WHITE);
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
  UserAction_t action = -1;
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

void close() { endwin(); }

void clear_screen() {
  attron(COLOR_PAIR(0));
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      mvprintw(i, j, "  ");
    }
  }
  attroff(COLOR_PAIR(0));
}

void draw_gameover(GameInfo_t info) {
  mvprintw(Y_START + 8, X_START + 6, "GAME OVER");
  mvprintw(Y_START + 10, X_START + 4, "SCORE: %06d", info.score);
  mvprintw(Y_START + 12, X_START + 3, "PRESS Q TO EXIT");
  draw_frame(2, 7, 16, 7);
}

void draw_start_menu() {
  GameInfo_t empty = {0};
  render(empty);
  mvprintw(Y_START + 8, X_START + 7, "PRESS S");
  draw_frame(4, 8, 12, 1);
}

void draw_pause() {
  mvprintw(Y_START + 8, X_START + 8, "PAUSE");
  draw_frame(5, 8, 10, 1);
}

void draw_frame(int x, int y, int width, int heigth) {
  for (int i = 0; i < width; ++i) {
    mvaddch(y + Y_START - 1, x + i + X_START, ACS_HLINE);
    mvaddch(y + heigth + Y_START, x + i + X_START, ACS_HLINE);
  }

  for (int i = 0; i < heigth; ++i) {
    mvaddch(y + i + Y_START, x + X_START, ACS_VLINE);
    mvaddch(y + i + Y_START, x + width + X_START, ACS_VLINE);
  }

  mvaddch(y + Y_START - 1, x + X_START, ACS_ULCORNER);
  mvaddch(y + Y_START - 1, x + width + X_START, ACS_URCORNER);
  mvaddch(y + heigth + Y_START, x + X_START, ACS_LLCORNER);
  mvaddch(y + heigth + Y_START, x + width + X_START, ACS_LRCORNER);
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

void draw_game_window(int x_start, int **field) {
  for (int i = 0; i < 20; ++i) {
    for (int j = x_start; j < 10 + x_start; ++j) {
      draw_square(i, j, field[i][j]);
    }
  }
}

void render(GameInfo_t info) {
  clear_screen();
  wbkgd(stdscr, COLOR_PAIR(0));
  if (info.field) {
    draw_game_window(0, info.field);
  }
  if (info.next) {
    draw_next(info);
  }
  draw_score(info);
  draw_highscore(info);
  draw_level(info);
  draw_frame(0, 0, 21, 20);
  draw_frame(X_MENU, 0, MENU_WIDTH, 20);
  refresh();
}