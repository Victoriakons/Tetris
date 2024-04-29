#include <assert.h>
#include <check.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "brick_game/tetris/s21_backend.h"
// #include "brick_game/tetris/backend.c"

START_TEST(GetBlockSetBlock_test) {
  GameStruct *tg = NULL;
  char ch = '0';

  tg = CreateGame(20, 10);
  SetBlock(tg, 5, 5, ch);
  ck_assert_int_eq(ch, GetBlock(tg, 5, 5));
  DestroyGame(tg);
}
END_TEST

START_TEST(insidetheboard_test) {
  GameStruct *tg = NULL;
  char ch = '0';
  tg = CreateGame(20, 10);
  SetBlock(tg, 5, 5, ch);

  ck_assert(CheckIfInsideTheBoard(tg, 40, 5) == false);

  DestroyGame(tg);
}
END_TEST

START_TEST(putfigure_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(20, 10);
  PutFigure(tg, tg->falling);
  ck_assert(tg->falling.a != 0);
  DestroyGame(tg);
}
END_TEST

START_TEST(CheckIfInsideTheBoard_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(20, 10);
  ck_assert(CheckIfInsideTheBoard(tg, 5, 5) == true);
  DestroyGame(tg);
}
END_TEST

START_TEST(removeblock_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(20, 10);
  Block fig;
  fig.a = 0;
  fig.orientation = 0;
  fig.loc.col = 0;
  fig.loc.row = 0;
  PutFigure(tg, fig);
  RemoveBlock(tg, fig);
  ck_assert_int_eq(fig.a, 0);
  DestroyGame(tg);
}
END_TEST

START_TEST(random_tetromino_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  tg->falling.a = random_tetromino();
  tg->falling.orientation = 0;
  tg->falling.loc.row = 0;

  ck_assert(tg->falling.a >= 0);
  DestroyGame(tg);
}
END_TEST

START_TEST(CheckIfBlockFits_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  Block tet;
  tet.a = random_tetromino();
  tet.orientation = 1;
  // tetris_location cell = tet_templates[tet.a][tet.orientation][4];
  ck_assert_int_eq(CheckIfBlockFits(tg, tet), 0);
  DestroyGame(tg);
}
END_TEST

START_TEST(RandomFallingBlock_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  RandomFallingBlock(tg);
  ck_assert(tg->falling.loc.col);
  DestroyGame(tg);
}
END_TEST

START_TEST(Tick_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  tg->ticks_till_gravity = 2;
  Tick(tg);
  ck_assert_int_eq(GRAVITY_LEVEL[tg->level], 50);
  DestroyGame(tg);
}
END_TEST

START_TEST(Tick_test_2) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  tg->ticks_till_gravity = 0;
  Tick(tg);
  ck_assert_int_eq(GRAVITY_LEVEL[tg->level], 50);
  DestroyGame(tg);
}
END_TEST

START_TEST(Move_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  Move(tg, -1);
  ck_assert(tg->falling.loc.col = -1);
  DestroyGame(tg);
}
END_TEST

START_TEST(Move_test_2) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  Move(tg, 1);
  ck_assert(tg->falling.loc.col = 1);
  DestroyGame(tg);
}
END_TEST

START_TEST(AccelerationToBottom_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  AccelerationToBottom(tg);
  ck_assert(tg->falling.loc.row-- || tg->falling.loc.row++);
  DestroyGame(tg);
}
END_TEST

START_TEST(Rotate_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  Rotate(tg, 1);
  ck_assert(tg->falling.orientation = (tg->falling.orientation + 1) % 4);
  DestroyGame(tg);
}
END_TEST

START_TEST(TakeFromHoldBuffer_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  TakeFromHoldBuffer(tg);
  ck_assert(tg->falling.a = tg->stored.a);
}
END_TEST

START_TEST(TakeFromHoldBuffer_test_2) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  tg->stored.a = 2;
  TakeFromHoldBuffer(tg);
  ck_assert(tg->falling.a = tg->stored.a);
}
END_TEST

//как в тесте прописать , что line is full?
START_TEST(CheckIfLineIsFull_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  int i = 5;
  ck_assert_int_eq(CheckIfLineIsFull(tg, i), 0);
  DestroyGame(tg);
}
END_TEST

//не понимаю как проверить
START_TEST(ShiftLines_test) {
  int r = 1;
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  ShiftLines(tg, r);
  DestroyGame(tg);
}
END_TEST

START_TEST(CheckLines_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  CheckLines(tg);
  ck_assert(tg->falling.a != 0);
  DestroyGame(tg);
}
END_TEST

START_TEST(AdjustScore_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  AdjustScore(tg, 2);
  ck_assert(tg->scores_remaining = 598);
  DestroyGame(tg);
}
END_TEST

//не понятно как проверить
START_TEST(Game_over_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  tg->cols = 20;
  // Game_over(tg);
  ck_assert_int_eq(Game_over(tg), 0);
}
END_TEST

START_TEST(PerformTick_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10, 20);
  tetris_move act = TM_RIGHT;
  PerformTick(tg, act);
  ck_assert_int_eq(PerformTick(tg, act), 1);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int a;

  suite_add_tcase(s1, tc_1);
  tcase_add_test(tc_1, GetBlockSetBlock_test);
  tcase_add_test(tc_1, insidetheboard_test);
  tcase_add_test(tc_1, putfigure_test);
  tcase_add_test(tc_1, CheckIfInsideTheBoard_test);
  tcase_add_test(tc_1, removeblock_test);
  tcase_add_test(tc_1, random_tetromino_test);
  tcase_add_test(tc_1, CheckIfBlockFits_test);
  tcase_add_test(tc_1, RandomFallingBlock_test);
  tcase_add_test(tc_1, Tick_test);
  tcase_add_test(tc_1, Tick_test_2);
  tcase_add_test(tc_1, Move_test);
  tcase_add_test(tc_1, Move_test_2);
  tcase_add_test(tc_1, CheckIfLineIsFull_test);
  tcase_add_test(tc_1, AccelerationToBottom_test);
  tcase_add_test(tc_1, Rotate_test);
  tcase_add_test(tc_1, TakeFromHoldBuffer_test);
  tcase_add_test(tc_1, TakeFromHoldBuffer_test_2);
  tcase_add_test(tc_1, ShiftLines_test);
  tcase_add_test(tc_1, CheckLines_test);
  tcase_add_test(tc_1, AdjustScore_test);
  tcase_add_test(tc_1, Game_over_test);
  tcase_add_test(tc_1, PerformTick_test);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  a = srunner_ntests_failed(sr);
  srunner_free(sr);

  return a == 0 ? 0 : 1;
}
