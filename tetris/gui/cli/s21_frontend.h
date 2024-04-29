#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../brick_game/tetris/s21_backend.h"
#include "../../brick_game/tetris/s21_util.h"

//для лучг=шей визуализации
#define COLS_PER_CELL 2

// Macro to print a cell of a specific type to a window.

#define ADD_BLOCK(w, x)                         \
  waddch((w), ' ' | A_REVERSE | COLOR_PAIR(x)); \
  waddch((w), ' ' | A_REVERSE | COLOR_PAIR(x))
#define ADD_EMPTY(w) \
  waddch((w), ' ');  \
  waddch((w), ' ')

void init_colors(void);
// Print the tetris board onto the ncurses window.
void display_board(WINDOW *w, GameStruct *obj);
//  Display a tetris piece in a dedicated window.
void display_piece(WINDOW *w, Block block);
// Display score information in a dedicated window.
void display_score(WINDOW *w, GameStruct *tg);
