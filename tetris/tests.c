#include <check.h>
#include <assert.h>
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


//какая-то херня
START_TEST(putfigure_test) {
GameStruct *tg = NULL;
tg = CreateGame(20, 10);
PutFigure(tg, tg->falling);
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

//тут правильно?
START_TEST(removeblock_test) {
//char ch = '0';
GameStruct *tg = NULL;
tg = CreateGame(20, 10);
//SetBlock(tg, 5, 5, ch);
PutFigure(tg, tg->falling);
RemoveBlock(tg, tg->falling);
ck_assert_int_eq(tg->falling.a, 0);

}
END_TEST


START_TEST(random_tetromino_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10,20);
  tg->falling.a = random_tetromino();
  ck_assert_int_ne(tg->falling.a,0);
}
END_TEST

START_TEST(CheckIfBlockFits_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10,20);
  Block tet;
  tet.a = random_tetromino();
  tet.orientation = 1;
  // tetris_location cell = tet_templates[tet.a][tet.orientation][4];
  ck_assert_int_eq(CheckIfBlockFits(tg, tet), 0);

}
END_TEST


START_TEST(CheckIfLineIsFull_test) {
  GameStruct *tg = NULL;
  tg = CreateGame(10,20);
  int i = 5;
  ck_assert_int_eq(CheckIfLineIsFull(tg, i), 0);
}
END_TEST

// START_TEST(test_s21_sub_matrix_3) {
//   matrix_t temp;
//   matrix_t temp2;
//   matrix_t result;
//   s21_create_matrix(3, 2, &temp);
//   s21_create_matrix(2, 2, &temp2);
//   s21_gen_matrix(&temp);
//   s21_gen_matrix(&temp2);
//   ck_assert_int_eq(s21_sub_matrix(&temp, &temp2, &result), 1);
//   s21_remove_matrix(&temp);
//   s21_remove_matrix(&temp2);
//   // if (s21_sub_matrix(&temp, &temp2, &result)) s21_remove_matrix(&result);
// }
// END_TEST

// START_TEST(test_s21_mult_number) {
//   matrix_t temp;
//   matrix_t temp2;
//   matrix_t result;
//   matrix_t result_defolt;
//   double num = 777.777;
//   s21_create_matrix(3, 3, &temp);
//   s21_create_matrix(3, 3, &temp2);
//   s21_create_matrix(3, 3, &result_defolt);
//   s21_gen_matrix(&temp);
//   s21_gen_matrix(&temp2);
//   for (int i = 0; (i < temp.rows); i++) {
//     for (int j = 0; j < temp.columns; j++) {
//       result_defolt.matrix[i][j] = temp.matrix[i][j] * 777.777;
//     }
//   }
//   ck_assert_int_eq(s21_mult_number(&temp, num, &result), 0);
//   ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
//   s21_remove_matrix(&temp);
//   s21_remove_matrix(&temp2);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&result_defolt);
// }
// END_TEST

// START_TEST(test_s21_mult_number_2) {
//   matrix_t temp;
//   matrix_t temp2;
//   matrix_t result;
//   matrix_t result_defolt;
//   double num = 777.777;
//   s21_create_matrix(3, 3, &temp);
//   s21_create_matrix(3, 3, &temp2);
//   s21_create_matrix(3, 3, &result_defolt);
//   s21_gen_matrix(&temp);
//   s21_gen_matrix(&temp2);
//   for (int i = 0; i < temp.rows; i++) {
//     for (int j = 0; j < temp.columns; j++) {
//       result_defolt.matrix[i][j] = temp.matrix[i][j] * 777.777;
//     }
//   }
//   ck_assert_int_eq(s21_mult_number(&temp, num, &result), 0);
//   ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
//   s21_remove_matrix(&temp);
//   s21_remove_matrix(&temp2);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&result_defolt);
// }
// END_TEST

// START_TEST(test_s21_mult_matrix) {
//   matrix_t A;
//   matrix_t B;
//   matrix_t result;
//   s21_create_matrix(1, 1, &A);
//   s21_create_matrix(1, 1, &B);
//   A.matrix[0][0] = 1;
//   B.matrix[0][0] = 2;
//   ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), 0);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&B);
//   s21_remove_matrix(&result);
//   if (s21_mult_matrix(&A, &B, &result)) {
//     s21_remove_matrix(&result);
//   }
// }
// END_TEST

// START_TEST(test_s21_mult_matrix_2) {
//   matrix_t temp;
//   matrix_t temp2;
//   matrix_t result;
//   matrix_t result_defolt;
//   s21_create_matrix(3, 2, &temp);
//   s21_create_matrix(2, 3, &temp2);
//   s21_create_matrix(3, 3, &result_defolt);
//   s21_gen_matrix(&temp);
//   s21_gen_matrix(&temp2);
//   result_defolt.matrix[0][0] = 9;
//   result_defolt.matrix[0][1] = 12;
//   result_defolt.matrix[0][2] = 15;
//   result_defolt.matrix[1][0] = 19;
//   result_defolt.matrix[1][1] = 26;
//   result_defolt.matrix[1][2] = 33;
//   result_defolt.matrix[2][0] = 29;
//   result_defolt.matrix[2][1] = 40;
//   result_defolt.matrix[2][2] = 51;
//   ck_assert_int_eq(s21_mult_matrix(&temp, &temp2, &result), 0);
//   ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
//   s21_remove_matrix(&temp);
//   s21_remove_matrix(&temp2);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&result_defolt);
// }
// END_TEST




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
  tcase_add_test(tc_1, CheckIfLineIsFull_test);
//   tcase_add_test(tc_1, test_s21_sub_matrix_3);
//   tcase_add_test(tc_1, test_s21_mult_number);
//   tcase_add_test(tc_1, test_s21_mult_number_2);
//   tcase_add_test(tc_1, test_s21_mult_matrix);
//   tcase_add_test(tc_1, test_s21_mult_matrix_2);
//   tcase_add_test(tc_1, test_s21_mult_matrix_4);
//   tcase_add_test(tc_1, test_s21_mult_matrix_3);
//   tcase_add_test(tc_1, test_s21_transpose);
//   tcase_add_test(tc_1, test_s21_transpose_2);
//   tcase_add_test(tc_1, test_s21_determinant);
//   tcase_add_test(tc_1, test_s21_determinant_2);
//   tcase_add_test(tc_1, test_s21_determinant_3);
//   tcase_add_test(tc_1, test_s21_determinant_5);
//   tcase_add_test(tc_1, test_s21_determinant_6);
//   tcase_add_test(tc_1, test_s21_determinant_7);
//   tcase_add_test(tc_1, test_s21_calc_complements);
//   tcase_add_test(tc_1, test_s21_calc_complements_2);
//   tcase_add_test(tc_1, test_s21_calc_complements_3);
//   tcase_add_test(tc_1, test_s21_inverse_matrix);
//   tcase_add_test(tc_1, test_s21_inverse_matrix_2);
//   tcase_add_test(tc_1, test_s21_inverse_matrix_3);
//   tcase_add_test(tc_1, test_s21_inverse_matrix_4);


  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  a = srunner_ntests_failed(sr);
  srunner_free(sr);

  return a == 0 ? 0 : 1;
}
