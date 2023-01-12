#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = CALCULATION_OK;
  int sign = S21_GET_SIGN(value);
  if (result) {
    s21_value_reset(result);
    *result = value;
    int precision = s21_getDecimalExp(value);
    s21_truncate(value, result);
    if (sign && precision) {
      s21_decimal one = {{1, 0, 0, 0}};
      res = s21_sub(*result, one, result);
    }
  } else {
    res = CALCULATION_ERROR;
  }
  return res;
}
