#include "s21_backend.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

tetris_location tet_templates[7][4][4] = {
    // I
    {{{1, 0}, {1, 1}, {1, 2}, {1, 3}},
     {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
     {{3, 0}, {3, 1}, {3, 2}, {3, 3}},
     {{0, 1}, {1, 1}, {2, 1}, {3, 1}}},
    // J
    {{{0, 0}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
     {{0, 1}, {1, 1}, {2, 0}, {2, 1}}},
    // L
    {{{0, 2}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
     {{0, 0}, {0, 1}, {1, 1}, {2, 1}}},
    // O
    {{{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}}},
    // S
    {{{0, 1}, {0, 2}, {1, 0}, {1, 1}},
     {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
     {{1, 1}, {1, 2}, {2, 0}, {2, 1}},
     {{0, 0}, {1, 0}, {1, 1}, {2, 1}}},
    // T
    {{{0, 1}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {1, 2}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 1}}},
    // Z
    {{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
     {{0, 2}, {1, 1}, {1, 2}, {2, 1}},
     {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 0}}},
};

int GRAVITY_LEVEL[MAX_LEVEL + 1] = {
    // 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    50, 48, 46, 44, 42, 40, 38, 36, 34, 32,
    // 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    30};

//Возвращает блок на определенных кооориднатах

char GetBlock(GameStruct *obj, int row, int column) {
  int res = obj->board[obj->cols * row + column];
  return res;
}

// проверяет находится ли фигура на игровом поле
bool CheckIfInsideTheBoard(GameStruct *obj, int row, int col) {
  if (0 <= row && row < obj->rows && 0 <= col && col < obj->cols) return true;
  return false;
}

//ставит фигуру на игровое поле
void PutFigure(GameStruct *obj, Block block) {
  int i;
  for (i = 0; i < 4; i++) {
    tetris_location cell = tet_templates[block.a][block.orientation][i];
    SetBlock(obj, block.loc.row + cell.row, block.loc.col + cell.col,
             COORDINATE_TO_CELL(block.a));
  }
}

//удаляет блок (фигуру)
void RemoveBlock(GameStruct *obj, Block block) {
  int i;
  for (i = 0; i < 4; i++) {
    tetris_location cell = tet_templates[block.a][block.orientation][i];
    SetBlock(obj, block.loc.row + cell.row, block.loc.col + cell.col, TC_EMPTY);
  }
}

//проверяет может ли каждая клетка блока (фигуры) поместиться на игровом поле
bool CheckIfBlockFits(GameStruct *obj, Block block) {
  int SIZE, r, c;
  for (SIZE = 0; SIZE < 4; SIZE++) {
    tetris_location cell = tet_templates[block.a][block.orientation][SIZE];
    r = block.loc.row + cell.row;
    c = block.loc.col + cell.col;
    if (!CheckIfInsideTheBoard(obj, r, c) ||
        TC_IS_FILLED(GetBlock(obj, r, c))) {
      return false;
    }
  }
  return true;
}

int random_tetromino(void) { return rand() % 7; }

//Случайная фигура, падающая на игровон поле сверху
void RandomFallingBlock(GameStruct *obj) {
  obj->falling = obj->next;  // next - новый падающий объект
  obj->next.a = random_tetromino();
  obj->next.orientation = 0;  //всего 4
  obj->next.loc.row = 0;      //падает сверху
  obj->next.loc.col =
      obj->cols / 2 - 2;  //чтобы новая фигура появлялась с середины
}

/*
  Tick gravity: в зависимости от значения в счетчике , проверяет может ли фигура
  упасть (Если ticks_till_gravity = 0 или меньше - процесс падения блока
  начинается). Если может, то блок убирается со своей настоящей позиции,
  спускается вниз по row, далее проверяется помещается ли фигура на поле. Если
  помещается, то обновляем GRAVITY_LEVEL и продолжаем падение блока (фигуры),
  если фигура не помещается - поставить ее обратно на прежнюю позицию и
  сгенерировать новый падающий блок (фигуру).
 */
void Tick(GameStruct *obj) {
  obj->ticks_till_gravity--;
  if (obj->ticks_till_gravity <= 0) {
    RemoveBlock(obj, obj->falling);
    obj->falling.loc.row++;
    if (CheckIfBlockFits(obj, obj->falling)) {
      obj->ticks_till_gravity = GRAVITY_LEVEL[obj->level];
    } else {
      obj->falling.loc.row--;
      PutFigure(obj, obj->falling);

      RandomFallingBlock(obj);
    }
    PutFigure(obj, obj->falling);
  }
}

// left (-1) or right (+1)

void Move(GameStruct *obj, int direction) {
  RemoveBlock(obj, obj->falling);
  obj->falling.loc.col += direction;
  if (!CheckIfBlockFits(obj, obj->falling)) {
    obj->falling.loc.col -= direction;
  }
  PutFigure(obj, obj->falling);
}

//ускорить падение вниз по row: сначала удаляем блок с его настоящей позиции,
//проверяем помещается ли  он на поле, если помещается - ускоряем падение вниз.
//Когда блок перестанет помещаться, нужно поставить его в позицию до и схаранить

void AccelerationToBottom(GameStruct *obj) {
  RemoveBlock(obj, obj->falling);
  while (CheckIfBlockFits(obj, obj->falling)) {
    obj->falling.loc.row++;
  }
  obj->falling.loc.row--;
  PutFigure(obj, obj->falling);
  RandomFallingBlock(obj);
}

//повернуть фигуру (+/-1).

void Rotate(GameStruct *obj, int direction) {
  RemoveBlock(obj, obj->falling);

  while (true) {
    obj->falling.orientation = (obj->falling.orientation + direction) % 4;

    if (CheckIfBlockFits(obj, obj->falling)) break;
    obj->falling.loc.col--;  //если фигура выходит за рамки, двигаем влево
    if (CheckIfBlockFits(obj, obj->falling)) break;

    // двигаем вправо, чтобы фигура вошла в рамки
    obj->falling.loc.col += 2;
    if (CheckIfBlockFits(obj, obj->falling)) break;

    // вернуть в прежнее положение
    obj->falling.loc.col--;
  }

  PutFigure(obj, obj->falling);
}

//Поменять фигуру в окне с падающей (stored block -> falling block)
void TakeFromHoldBuffer(GameStruct *obj) {
  RemoveBlock(obj, obj->falling);
  if (obj->stored.a == -1) {
    obj->stored = obj->falling;
    RandomFallingBlock(obj);
  } else {
    int a = obj->falling.a, orientation = obj->falling.orientation;
    obj->falling.a = obj->stored.a;
    obj->falling.orientation = obj->stored.orientation;
    obj->stored.a = a;
    obj->stored.orientation = orientation;
    while (!CheckIfBlockFits(obj, obj->falling)) {
      obj->falling.loc.row--;
    }
  }
  PutFigure(obj, obj->falling);
}

static void PerformAction(GameStruct *obj, tetris_move move) {
  switch (move) {
    case TM_LEFT:
      Move(obj, -1);
      break;
    case TM_RIGHT:
      Move(obj, 1);
      break;
    case TM_DROP:
      AccelerationToBottom(obj);
      break;
    case TM_CLOCK:
      Rotate(obj, 1);
      break;
    case TM_COUNTER:
      Rotate(obj, -1);
      break;
    case TM_HOLD:
      TakeFromHoldBuffer(obj);
      break;
    default:
      break;
  }
}

bool CheckIfLineIsFull(GameStruct *obj, int i) {
  int j;
  for (j = 0; j < obj->cols; j++) {
    if (TC_IS_EMPTY(GetBlock(obj, i, j))) return false;
  }
  return true;
}

/*
  Shift every row above r down one.
 */
void ShiftLines(GameStruct *obj, int r) {
  int i, j;
  for (i = r - 1; i >= 0; i--) {
    for (j = 0; j < obj->cols; j++) {
      SetBlock(obj, i + 1, j, GetBlock(obj, i, j));
      SetBlock(obj, i, j, TC_EMPTY);
    }
  }
}

/*
  Находит заполненые ряды и удаляет их (возвращает кол-во удаленных рядов)
 */
int CheckLines(GameStruct *obj) {
  int i, nlines = 0;
  RemoveBlock(obj, obj->falling);  // don't want to mess up falling block

  for (i = obj->rows - 1; i >= 0; i--) {
    if (CheckIfLineIsFull(obj, i)) {
      ShiftLines(obj, i);
      i++;  // do this line over again since they're shifted
      nlines++;
    }
  }

  PutFigure(obj, obj->falling);  // replace
  return nlines;
}

/*
  Score = кол-во удаленных рядов
 */
void AdjustScore(GameStruct *obj, int lines_cleared) {
  static int line_multiplier[] = {0, 100, 300, 700, 1500};
  obj->points += line_multiplier[lines_cleared] + (obj->level);
  if (obj->points == 600) {
    obj->level = MIN(MAX_LEVEL, obj->level + 1);
    lines_cleared -= obj->scores_remaining;
    obj->scores_remaining = SCORES_PER_LEVEL - lines_cleared;
  } else {
    obj->lines_remaining -= lines_cleared;
  }
}

/*
Возвращает True, если игра закончега
 */
bool Game_over(GameStruct *obj) {
  int i, j;
  bool over = false;
  RemoveBlock(obj, obj->falling);
  for (i = 0; i < 2; i++) {
    for (j = 0; j < obj->cols; j++) {
      if (TC_IS_FILLED(GetBlock(obj, i, j))) {
        over = true;
      }
    }
  }
  PutFigure(obj, obj->falling);
  return over;
}

/*
  Do a single game tick: process gravity, user input, and score.  Return true if
  the game is still running, false if it is over.
 */
bool PerformTick(GameStruct *obj, tetris_move move) {
  int lines_cleared;
  // Handle gravity.
  Tick(obj);

  // Handle input.
  PerformAction(obj, move);

  // Check for cleared lines
  lines_cleared = CheckLines(obj);

  AdjustScore(obj, lines_cleared);

  // Return whether the game will continue (NOT whether it's over)
  return !Game_over(obj);
}

void init(GameStruct *obj, int rows, int cols) {
  // Initialization logic
  obj->rows = rows;
  obj->cols = cols;
  obj->board = malloc(rows * cols);
  memset(obj->board, TC_EMPTY, rows * cols);
  obj->points = 0;
  obj->level = 0;
  obj->ticks_till_gravity = GRAVITY_LEVEL[obj->level];
  obj->lines_remaining = SCORES_PER_LEVEL;
  srand(time(NULL));
  RandomFallingBlock(obj);
  RandomFallingBlock(obj);
  obj->stored.a = -1;
  obj->stored.orientation = 0;
  obj->stored.loc.row = 0;
  obj->next.loc.col = obj->cols / 2 - 2;
  printf("%d", obj->falling.loc.col);
}

GameStruct *CreateGame(int rows, int cols) {
  GameStruct *obj = malloc(sizeof(GameStruct));
  init(obj, rows, cols);
  return obj;
}

void DestroyGame(GameStruct *obj) { free(obj->board); }

void Delete(GameStruct *obj) {
  DestroyGame(obj);
  free(obj);
}

/*
  Load a game from a file.
 */
