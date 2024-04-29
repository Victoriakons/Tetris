CFILES = $(shell find . -name "s21_backend.c")
# # OBJ = $(patsubst backend.c, backend.o, $(CFILES))
OBJ_FILE = s21_backend.o
# TARGET = SimpleTetris
CHECK:=$(shell pkg-config --cflags --libs check)
FLAG_COV = --coverage
# CC=gcc
FLAGS=-std=c11 -g -Wall -Werror -Wextra
S21_tetris=-L. s21_backend.a
# DEBUG =-g
CTESTFLAGS=-lcheck -lm -lpthread 
FIND_CHECK=$(shell pkg-config --cflags --libs check)
TEST = tests.c
LIBRARY = s21_backend.a



TARGET = SimpleTetris
CC = gcc

PREF_SRC = brick_game/tetris gui/cli
PREF_OBJ = brick_game/tetris gui/cli

SRC = $(shell find . -name "s21*.c")
OBJ = $(patsubst $(PREF_SRC)%.c, (PREF_OBJ)%.o, $(SRC)) 

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -lncurses -o $(TARGET)

$(PREF_OBJ)%.o : $(PREF_SRC)%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@


all : $(LIBRARY) 

$(LIBRARY): brick_game/tetris/s21_backend.h
	$(CC) $(CFILES) -c $(FLAGS)
	ar rc $(LIBRARY) $(OBJ_FILE)
	ranlib $(LIBRARY)
	# rm -f $(OBJ_FILE)

clean:
	rm -rf *.o *.a test *.gcda *.gcno *.info coverage

style:
	clang-format -style=google -i *.c
	clang-format -style=google -i *.h


checkstyle:
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h


de: $(TARGET)
  
gcov_report: $(LIBRARY)
	$(CC) $(FLAG_COV) $(FLAGS) $(CTESTFLAGS) $(TEST) $(CFILES) -o test $(CHECK) $(S21_tetris)
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o coverage test.info
	open coverage/index.html

test: clean $(LIBRARY)
	$(CC) $(FLAG_COV) $(FLAGS) $(CTESTFLAGS) $(FIND_CHECK) $(TEST) $(CFILES) -o test  $(S21_tetris)
	./test
