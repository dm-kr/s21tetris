CC = gcc
CFLAGS = -Wall -Wextra -Werror
API_DIR = brick_game/tetris/
API_SRC = $(patsubst $(API_DIR)%.c, %.c, $(wildcard $(API_DIR)*.c))
API_OBJ = $(patsubst %.c, %.o, $(API_SRC))
UI_DIR = gui/cli/
UI_SRC = $(patsubst $(UI_DIR)%.c, %.c, $(wildcard $(UI_DIR)*.c))
UI_OBJ = $(patsubst %.c, %.o, $(UI_SRC))
LIB_DIR = libs/
OBJ_DIR = objs/
APILIBNAME = tetris
APILIB = libtetris
UILIBNAME = ui
UILIB = libui

vpath %.c $(API_DIR) $(UI_DIR)

all: uninstall install

%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)$@

run: install
	@./game

install: $(APILIB).a $(UILIB).a
	@$(CC) $(CFLAGS) main.c -L$(LIB_DIR) -l$(APILIBNAME) -l$(UILIBNAME) -o game

uninstall:

$(APILIB).a: $(API_OBJ)
	@mkdir -p $(LIB_DIR)
	@ar rcs $(LIB_DIR)$@ $(patsubst %.o, $(OBJ_DIR)%.o, $<)
	@ranlib $(LIB_DIR)$@

$(UILIB).a: $(UI_OBJ)
	@mkdir -p $(LIB_DIR)
	@ar rcs $(LIB_DIR)$@ $(patsubst %.o, $(OBJ_DIR)%.o, $<)
	@ranlib $(LIB_DIR)$@

dvi:

dist:

test:

gcov_report:

clean:
	@rm -rf $(OBJ_DIR) $(LIB_DIR) game