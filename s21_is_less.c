#include "s21_decimal.h"

// функция меньше
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int _res = FALSE;
  s21_decimal sub;
  if (s21_is_equal(value_1, value_2)) {
    _res = FALSE;
  } else {
    int sign_1 = S21_GET_SIGN(value_1);
    int sign_2 = S21_GET_SIGN(value_2);
    if (sign_1 && !sign_2)
      _res = TRUE;
    else if (!sign_1 && sign_2)
      _res = FALSE;
    else {
      int res_sub = s21_sub(value_1, value_2, &sub);
      if (res_sub == ARITHMETIC_OK && S21_GET_SIGN(sub) == 1) _res = TRUE;
    }
  }
  return _res;
}

// функция меньше или равно
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int _res = FALSE;
  // s21_decimal sub;
  if (s21_is_equal(value_1, value_2)) {
    _res = TRUE;
  } else {
    _res = s21_is_less(value_1, value_2);
  }
  return _res;
}

// функция больше
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int _res = !s21_is_less_or_equal(value_1, value_2);
  return _res;
}

// функция больше или равно
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int _res = !s21_is_less(value_1, value_2);
  return _res;
}
