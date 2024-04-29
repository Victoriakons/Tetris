#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


#include "s21_frontend.h"



/*
  NCURSES initialization for color blocks.
 */
void init_colors(void)
{
  start_color();
  //init_color(COLOR_ORANGE, 1000, 647, 0);
  init_pair(TC_CELLI, COLOR_CYAN, COLOR_BLACK);
  init_pair(TC_CELLJ, COLOR_BLUE, COLOR_BLACK);
  init_pair(TC_CELLL, COLOR_WHITE, COLOR_BLACK);
  init_pair(TC_CELLO, COLOR_YELLOW, COLOR_BLACK);
  init_pair(TC_CELLS, COLOR_GREEN, COLOR_BLACK);
  init_pair(TC_CELLT, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(TC_CELLZ, COLOR_RED, COLOR_BLACK);
}


void display_board(WINDOW *w, GameStruct *obj)
{
  int i, j;
  box(w, 0, 0);
  for (i = 0; i < obj->rows; i++) {
    wmove(w, 1 + i, 1);
    for (j = 0; j < obj->cols; j++) {
      if (TC_IS_FILLED(GetBlock(obj, i, j))) {
        ADD_BLOCK(w,GetBlock(obj, i, j));
      } else {
        ADD_EMPTY(w);
      }
    }
  }
  wnoutrefresh(w);
}

void display_piece(WINDOW *w, Block block)
{
  int b;
  tetris_location c;
  wclear(w);
  box(w, 0, 0);
  if (block.a == -1) {
    wnoutrefresh(w);
    return;
  }
  for (b = 0; b < 4; b++) {
    c = tet_templates[block.a][block.orientation][b];
    wmove(w, c.row + 1, c.col * COLS_PER_CELL + 1);
    ADD_BLOCK(w, COORDINATE_TO_CELL(block.a));
  }
  wnoutrefresh(w);
}


void display_score(WINDOW *w, GameStruct *tg)
{
  wclear(w);
  box(w, 0, 0);
  wprintw(w, "Score\n%d\n", tg->points);
  wprintw(w, "Level\n%d\n", tg->level);
  wprintw(w, "Lines\n%d\n", tg->lines_remaining);
  wnoutrefresh(w);
}

