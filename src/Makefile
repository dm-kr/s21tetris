CC = gcc
CFLAGS = 
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L$(LIB_DIR) -l$(APILIBNAME) -l$(UILIBNAME) -lncurses -lcheck -lsubunit -lm
BRANCHES = --rc lcov_branch_coverage=1
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
GCOV_DIR = test_info
APILIBNAME = tetris
APILIB = libtetris
UILIBNAME = ui
UILIB = libui
APPNAME = s21tetris
SUPPRESS = >> /dev/null 2>&1

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
	@mkdir -p $(GCOV_DIR)
	@$(CC) $(CFLAGS) tests/*.c $(API_DIR)*.c $(LFLAGS) -lpthread -lrt --coverage -o $(GCOV_DIR)/test
	@$(GCOV_DIR)/test

valtest: install
	@$(CC) $(CFLAGS) tests/*.c $(LFLAGS) -o tests/test
	@valgrind --tool=memcheck --leak-check=full --track-origins=yes -s tests/test

gcov_report: clean test
	@mkdir -p $(GCOV_DIR)
	@lcov --capture --directory $(GCOV_DIR) --output-file $(GCOV_DIR)/test.info $(BRANCHES) $(SUPPRESS)
	@lcov --remove $(GCOV_DIR)/test.info '/usr/include/*' '*/tests/*' --output-file $(GCOV_DIR)/test.info $(BRANCHES) $(SUPPRESS) 
	@genhtml $(GCOV_DIR)/test.info --output-directory coverage_report $(BRANCHES) > $(GCOV_DIR)/genhtml.log 2>&1
	@bash tests/coverage.sh $(GCOV_DIR)
	@xdg-open coverage_report/index.html $(SUPPRESS)

valgrind: install
	@valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./$(APPNAME)

clang:
	@clang-format -n *.c -style=Google
	@clang-format -n **/**/*.c -style=Google

fix-clang:
	@clang-format -i *.c -style=Google
	@clang-format -i **/**/*.c -style=Google

clean:
	@rm -rf $(OBJ_DIR) $(LIB_DIR) $(DIST_DIR) $(DOXY_DIR) $(APPNAME) $(GCOV_DIR) coverage_report tests/test highscore.txt