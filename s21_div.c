#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int _res = CALCULATION_OK;
  s21_decimal zero;
  s21_value_reset(&zero);
  if (s21_is_equal(value_2, zero)) {
    if (result) {
      s21_value_reset(result);
      _res = DIVISION_BY_0;
    } else {
      _res = NULL_POINTER;
    }
  } else {
    uint8 sign = S21_GET_SIGN(value_1) ^ S21_GET_SIGN(value_2);
    S21_SET_SIGN(&value_1, 0);
    S21_SET_SIGN(&value_2, 0);
    char x[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
    char y[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
    s21_decimalToString(x, value_1);
    s21_decimalToString(y, value_2);
    s21_divideStringDecimal(x, y);
    _res = s21_processingMathResultAndWriteOutputRegister(result, x, sign);
  }
  return _res;
}
