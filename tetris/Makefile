CFILES = $(shell find . -name "backend.c")
# OBJ = $(patsubst backend.c, backend.o, $(CFILES))
OBJ = backend.o
TARGET = SimpleTetris
#CHECK:=$(shell pkg-config --cflags --libs check)
FLAG_COV = --coverage
CC=gcc
FLAGS=-std=c11 -g -Wall -Werror -Wextra
S21_tetris=-L. backend.a
DEBUG =-g
CTESTFLAGS=-lcheck -lm -lpthread 
FIND_CHECK=$(shell pkg-config --cflags --libs check)
TEST = tests.c
LIBRARY = backend.a


all: $(LIBRARY) 

$(LIBRARY): brick_game/tetris/backend.h
	$(CC) $(CFILES) -c $(FLAGS)
	ar rc $(LIBRARY) $(OBJ)
	ranlib $(LIBRARY)
	# rm -f $(OBJ)

clean:
	rm -rf *.o *.a test *.gcda *.gcno *.info coverage

style:
	clang-format -style=google -i *.c
	clang-format -style=google -i *.h
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h

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
