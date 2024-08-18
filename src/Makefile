CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L$(LIB_DIR) -l$(APILIBNAME) -l$(UILIBNAME) -lncurses -lcheck  -lsubunit -lm
API_DIR = brick_game/tetris/
API_SRC = $(patsubst $(API_DIR)%.c, %.c, $(wildcard $(API_DIR)*.c))
API_OBJ = $(patsubst %.c, %.o, $(API_SRC))
UI_DIR = gui/cli/
UI_SRC = $(patsubst $(UI_DIR)%.c, %.c, $(wildcard $(UI_DIR)*.c))
UI_OBJ = $(patsubst %.c, %.o, $(UI_SRC))
LIB_DIR = libs/
OBJ_DIR = objs/
DIST_DIR = dist
DOXY_DIR = doxy
APILIBNAME = tetris
APILIB = libtetris
UILIBNAME = ui
UILIB = libui
APPNAME = s21tetris

vpath %.c $(API_DIR) $(UI_DIR)

all: reinstall

%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)$@

run: install
	@./$(APPNAME)

install: $(APILIB).a $(UILIB).a main.o
	@$(CC) $(CFLAGS) $(OBJ_DIR)main.o $(LFLAGS) -o $(APPNAME)
	@if [ ! -f highscore.txt ]; then \
        touch highscore.txt;\
				echo 0 > highscore.txt;\
	 fi

uninstall:
	@rm -rf $(OBJ_DIR) $(LIB_DIR) $(APPNAME) highscore.txt

reinstall: uninstall install

$(APILIB).a: $(API_OBJ)
	@mkdir -p $(LIB_DIR)
	@ar rcs $(LIB_DIR)$@ $(patsubst %.o, $(OBJ_DIR)%.o, $<)
	@ranlib $(LIB_DIR)$@

$(UILIB).a: $(UI_OBJ)
	@mkdir -p $(LIB_DIR)
	@ar rcs $(LIB_DIR)$@ $(patsubst %.o, $(OBJ_DIR)%.o, $<)
	@ranlib $(LIB_DIR)$@

dvi:
	mkdir -p $(DOXY_DIR)
	doxygen
	open $(DOXY_DIR)/html/index.html

dist: clean install
	@mkdir -p $(DIST_DIR)
	@tar -cf $(DIST_DIR)/$(APPNAME).tar $(OBJ_DIR)*.o

test: install
	@$(CC) $(CFLAGS) tests/*.c $(LFLAGS) -o tests/test
	@tests/test

gcov_report:

valgrind: install
	@valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./$(APPNAME)

clean:
	@rm -rf $(OBJ_DIR) $(LIB_DIR) $(DIST_DIR) $(DOXY_DIR) $(APPNAME) tests/test highscore.txt