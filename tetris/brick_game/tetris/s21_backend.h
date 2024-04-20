#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h> // for FILE
#include <stdbool.h> // for bool


/*
координата x преобразуется в координату ячейки путем добавления единицы. 
Так как координаты ячеек начинаются с 1, а не с 0.
 */
#define COORDINATE_TO_CELL(x) ((x)+1)

/*
  Strings for how you would print a tetris board.
 */
#define TC_EMPTY_STR " "
#define TC_BLOCK_STR "\u2588" //Символ \u2588 - это символ игральной кости в Юникоде, который часто используется для представления блоков

/*
  Questions about a tetris cell.
 */
#define TC_IS_EMPTY(x) ((x) == TC_EMPTY)
#define TC_IS_FILLED(x) (!TC_IS_EMPTY(x))

/*
  How many cells in a tetromino? - 4

  How many tetrominos? - 7

  How many orientations of a tetromino? - 4
*/

//Level constants.

#define MAX_LEVEL 6000
#define SCORES_PER_LEVEL 600

/*
  A "cell" is a 1x1 block within a tetris board.
 */
typedef enum {
  TC_EMPTY, TC_CELLI, TC_CELLJ, TC_CELLL, TC_CELLO, TC_CELLS, TC_CELLT, TC_CELLZ
} tetris_cell;

/*
  A "type" is a type/shape of a tetromino.  Not including orientation.
 */
typedef enum {
  TET_I, TET_J, TET_L, TET_O, TET_S, TET_T, TET_Z
} tetris_type;

/*
  A row,column pair.  Negative numbers allowed, because we need them for
  offsets.
 */
typedef struct {
  int row;
  int col;
} tetris_location;

/*
  A "block" is a struct that contains information about a tetromino.
  Specifically, what type it is, what orientation it has, and where it is.
 */
typedef struct {
  int a;
  int orientation;
  tetris_location loc;
} Block;

/*
  All possible moves to give as input to the game.
 */
typedef enum {
  TM_LEFT, TM_RIGHT, TM_CLOCK, TM_COUNTER, TM_DROP, TM_HOLD, TM_NONE
} tetris_move;

/*
  A game object!
 */
typedef struct GameStruct{

//Field
  int rows, cols;
  char *board;
  
  int points;
  int level;
  /*
    Falling block is the one currently going down.  Next block is the one that
    will be falling after this one.  Stored is the block that you can swap out.
   */
  Block falling;
  Block next;
  Block stored;
  /*
    Number of game ticks until the block will move down.
   */
  int ticks_till_gravity;
  /*
    Number of lines until you advance to the next level.
   */
  int lines_remaining;
  int scores_remaining;
} GameStruct;


extern tetris_location tet_templates[7][4][4]; //7 - кол-во фигур, 4 - позиции фигуры (при повороте), 4*4 - размер

/*
  This array tells you how many ticks per gravity by level.  Decreases as level
  increases, to add difficulty.
 */
extern int GRAVITY_LEVEL[MAX_LEVEL+1];

// Data structure manipulation.
void init(GameStruct *obj, int rows, int cols);
GameStruct *CreateGame(int rows, int cols);
void DestroyGame(GameStruct *obj);
void Delete(GameStruct *obj);
GameStruct *Load(FILE *f);
void Save(GameStruct *obj, FILE *f);

// Public methods not related to memory:
char GetBlock(GameStruct *obj, int row, int col);
bool CheckIfInsideTheBoard(GameStruct *obj, int row, int col);
bool PerformTick(GameStruct *obj, tetris_move move);
void Print(GameStruct *obj, FILE *f);

// static void SetBlock(GameStruct *obj, int row, int column, char value);



//static int random_tetromino(void);

#endif // TETRIS_H



