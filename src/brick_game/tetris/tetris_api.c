#include "tetris_api.h"

static GameInfo_t current_state = {0};

void copy_info(GameInfo_t *src, GameInfo_t *dst) {
  dst->high_score = src->high_score;
  dst->level = src->level;
  dst->next = src->next;
  dst->score = src->score;
}

int **get_empty_field() {
  int **field = calloc(ROWS, sizeof(int *));
  for (int i = 0; i < ROWS; ++i) {
    field[i] = calloc(COLUMNS, sizeof(int));
  }
  return field;
}

void copy_field(int **src, int **dst) {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      dst[i][j] = src[i][j];
    }
  }
}

int **get_empty_piece() {
  int **piece = calloc(4, sizeof(int *));
  for (int i = 0; i < 4; ++i) {
    piece[i] = calloc(4, sizeof(int));
  }
  return piece;
}

void copy_piece(int **src, int **dst) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      dst[i][j] = src[i][j];
    }
  }
}

void clear_piece(int **piece) {
  for (int i = 0; i < 4; ++i) {
    free(piece[i]);
  }
  free(piece);
}

void clear_field(int **field) {
  for (int i = 0; i < ROWS; ++i) {
    free(field[i]);
  }
  free(field);
}

void clear_gameinfo() {
  if (current_state.field) {
    clear_field(current_state.field);
  }
  if (current_state.next) {
    clear_piece(current_state.next);
  }
}

void clear_gamestate() {
  GameState_t *state = get_gamestate(NULL);
  if (state->temp_field) {
    clear_field(state->temp_field);
  }
  if (state->backup) {
    clear_field(state->backup);
  }
  if (state->piece) {
    clear_piece(state->piece->piece);
    free(state->piece);
  }
  if (state->pieces) {
    for (int i = 0; i < 7; ++i) {
      clear_piece(state->pieces[i]);
    }
    free(state->pieces);
  }
  free(state);
}

int ***get_pieces_array() {
  FILE *file = fopen("pieces.yaml", "r");
  char *line = NULL;
  size_t len = 0;
  __ssize_t read;
  int n = 0;
  int ***pieces = calloc(7, sizeof(int *) * 4);
  for (int i = 0; i < 7; ++i) {
    pieces[i] = get_empty_piece();
  }
  while ((read = getline(&line, &len, file)) != -1) {
    getline(&line, &len, file);
    for (int i = 0; i < 4; ++i) {
      read = getline(&line, &len, file);
      for (int j = 0; j < 4; ++j) {
        pieces[n][i][j] = line[j + 4] - '0';
      }
    }
    ++n;
  }
  if (line != NULL) {
    free(line);
  }
  fclose(file);
  return pieces;
}

void find_edges(int **piece, int *x1, int *x2, int *y) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (piece[i][j] != 0) {
        *x1 = *x1 > j ? j : *x1;
        *x2 = *x2 < j ? j : *x2;
        *y = *y < i ? i : *y;
      }
    }
  }
}

int is_overlapping(int **field, Piece_t *piece) {
  int result = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (piece->piece[j][i] != 0 && ((j + piece->y) >= 0)) {
        result |= field[j + piece->y][i + piece->x] > 0;
      }
    }
  }
  return result;
}

void ghost(int **field, Piece_t *piece) {
  int x1 = 4;
  int x2 = 0;
  int y = 0;
  find_edges(piece->piece, &x1, &x2, &y);
  while (piece->y + y < ROWS && !is_overlapping(field, piece)) {
    piece->y++;
    find_edges(piece->piece, &x1, &x2, &y);
  }
  piece->y--;
}

void paint_piece(int **piece, int color) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (piece[i][j] != 0) {
        piece[i][j] = color;
      }
    }
  }
}

int check_collision(Piece_t piece) {
  int error = 0;
  int x1 = 3;
  int x2 = 0;
  int y = 0;
  find_edges(piece.piece, &x1, &x2, &y);
  if (piece.x + x1 < 0 || piece.x + x2 >= COLUMNS || piece.y + y >= ROWS) {
    error = 1;
  } else {
    GameState_t *state = get_gamestate(NULL);
    copy_field(state->backup, state->temp_field);
    Piece_t *temp = calloc(1, sizeof(Piece_t));
    temp->piece = get_empty_piece();
    copy_piece(piece.piece, temp->piece);
    temp->x = piece.x;
    temp->y = piece.y;
    ghost(state->temp_field, temp);
    paint_piece(temp->piece, 100);
    error = draw_piece(state->temp_field, *temp);
    clear_piece(temp->piece);
    free(temp);
    error = draw_piece(state->temp_field, piece);
  }
  return error;
}

int draw_piece(int **field, Piece_t piece) {
  int overwrite = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (piece.piece[j][i] != 0 && ((j + piece.y) >= 0)) {
        int color = field[j + piece.y][i + piece.x];
        overwrite |= color > 0 && color < 100;
        field[j + piece.y][i + piece.x] = piece.piece[j][i];
      }
    }
  }
  return overwrite;
}

void spawn_piece(GameState_t *state) {
  int piece_index = state->next_index;
  state->piece->x = 3;
  state->piece->y = -2;
  copy_piece(state->pieces[piece_index], state->piece->piece);
  if (piece_index == 0 || piece_index == 3) {
    state->piece->type = Even;
  } else {
    state->piece->type = Odd;
  }
  copy_field(current_state.field, state->backup);
  int error = check_collision(*state->piece);
  if (error == 0) {
    state->next_index = (clock() * clock()) % 7;
    copy_piece(state->pieces[state->next_index], current_state.next);
    copy_field(state->temp_field, current_state.field);
  } else {
    current_state.speed = 0;
  }
}

int move_piece(GameState_t *state, int dir) {
  int error = 0;
  int x = state->piece->x;
  int y = state->piece->y;
  if (dir == 6) {
    state->piece->y++;
  } else if (dir == 3) {
    state->piece->x--;
  } else if (dir == 4) {
    state->piece->x++;
  }
  error = check_collision(*state->piece);
  if (error) {
    state->piece->x = x;
    state->piece->y = y;
  } else {
    copy_field(state->temp_field, current_state.field);
  }
  return error;
}

void rotate_odd(Piece_t *piece, int **new) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      new[i + 1][j] = piece->piece[3 - j][i];
    }
  }
}

void rotate_even(Piece_t *piece, int **new) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      new[i][j] = piece->piece[3 - j][i];
    }
  }
}

void rotate(Piece_t *piece) {
  int x1 = 4;
  int x2 = 0;
  int y = 0;
  Piece_t new;
  new.piece = get_empty_piece();
  new.x = piece->x;
  new.y = piece->y;
  new.type = piece->type;
  if (piece->type == Odd) {
    rotate_odd(piece, new.piece);
  } else {
    rotate_even(piece, new.piece);
  }
  find_edges(new.piece, &x1, &x2, &y);
  if (piece->x + x1 >= 0 && piece->x + x2 <= COLUMNS && piece->y + y <= ROWS) {
    GameState_t *state = get_gamestate(NULL);
    int error = check_collision(new);
    if (error == 0) {
      copy_field(state->temp_field, current_state.field);
      copy_piece(new.piece, piece->piece);
    }
  }
  clear_piece(new.piece);
}

void read_highscore() {
  FILE *fp = fopen("highscore.txt", "r");
  int hs = 0;
  fscanf(fp, "%d", &hs);
  fclose(fp);
  current_state.high_score = hs;
}

void init_gameinfo() {
  current_state.field = get_empty_field();
  current_state.next = get_empty_piece();
  current_state.speed = 500000;
  current_state.level = 1;
  read_highscore();
}

Piece_t *init_piece() {
  Piece_t *piece = calloc(1, sizeof(Piece_t));
  piece->piece = get_empty_piece();
  return piece;
}

GameState_t *init_gamestate() {
  GameState_t *state = (GameState_t *)calloc(1, sizeof(GameState_t));
  state->next_index = (clock() * clock()) % 7;
  state->state = Init;
  state->temp_field = get_empty_field();
  state->backup = get_empty_field();
  state->pieces = get_pieces_array();
  state->piece = init_piece();
  state->timer = clock();
  return state;
}

GameState_t *get_gamestate(GameState_t *state) {
  static GameState_t *state_;
  if (state != NULL) {
    state_ = state;
  }
  return state_;
}

void clear_memory() {
  clear_gameinfo();
  clear_gamestate();
}

void shift_matrix_down(int start) {
  for (int j = ROWS - start; j > 0; --j) {
    for (int k = 0; k < COLUMNS; ++k) {
      current_state.field[j][k] = current_state.field[j - 1][k];
      current_state.field[0][k] = 0;
    }
  }
}

int check_lines() {
  int counter = 0;
  for (int i = 0; i < ROWS; ++i) {
    int check = 1;
    for (int j = 0; j < COLUMNS; ++j) {
      if (current_state.field[i][j] == 0) {
        check = 0;
      }
    }
    if (check) {
      shift_matrix_down(ROWS - i);
      counter++;
    }
  }
  GameState_t *state = get_gamestate(NULL);
  copy_field(current_state.field, state->backup);
  return counter;
}

void add_points(int lines) {
  int points = 0;
  switch (lines) {
    case 1:
      points = 100;
      break;
    case 2:
      points = 300;
      break;
    case 3:
      points = 700;
      break;
    case 4:
      points = 1500;
      break;
    default:
      points = 0;
      break;
  }
  current_state.score += points;
}

void set_level() {
  if (current_state.level < 10) {
    current_state.level = 1 + (current_state.score / 600);
  }
  if (current_state.level > 10) {
    current_state.level = 10;
  }
}

void set_highscore() {
  FILE *fp = fopen("highscore.txt", "w");
  fprintf(fp, "%d", current_state.high_score);
  fclose(fp);
}

void set_speed() { current_state.speed = 500000 - current_state.level * 30000; }

void drop_piece() {
  GameState_t *state = get_gamestate(NULL);
  int x = state->piece->x;
  int y = state->piece->y;
  while (move_piece(state, 6) == 0);
  state->piece->x = x;
  state->piece->y = y;
}

void userInput(UserAction_t action, bool hold) {
  GameState_t *state = get_gamestate(NULL);
  if (state == NULL && action != Start) {
    action = -1;
  }
  switch (action) {
    case Start:
      init_gameinfo();
      state = get_gamestate(init_gamestate());
      state->state = Init;
      break;
    case Pause:
      state->state = Paused;
      break;
    case Terminate:
      state->state = Termination;
      clear_memory();
      break;
    case Left:
    case Right:
      state->state = Shifting;
      move_piece(state, action * hold);
      break;
    case Down:
      state->state = Attaching;
      drop_piece();
      break;
    case Up:
      break;
    case Action:
      state->state = Rotation;
      rotate(state->piece);
      state->state = Moving;
      break;
    default:
      break;
  }
}

GameInfo_t updateCurrentState() {
  GameState_t *state = get_gamestate(NULL);
  int error = 0;
  if (clock() - state->timer > current_state.speed) {
    error = move_piece(state, 6);
    if (error != 0) {
      state->state = Attaching;
    } else {
      state->state = Moving;
    }
    state->timer = clock();
  }
  if (state->state == Init || state->state == Attaching) {
    int lines = check_lines();
    if (lines > 0) {
      add_points(lines);
      set_level();
      set_speed();
      if (current_state.score > current_state.high_score) {
        current_state.high_score = current_state.score;
        set_highscore();
      }
    }
    state->state = Spawn;
    spawn_piece(state);
  }
  return current_state;
}