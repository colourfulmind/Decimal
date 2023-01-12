#include "s21_decimal.h"

int s21_mod(s21_decimal x, s21_decimal y, s21_decimal *result) {
  int _res = ARITHMETIC_OK;
  if (result) {
    s21_decimal zero, z, z2, a;
    s21_value_reset(&zero);
    s21_value_reset(&z);
    s21_value_reset(&z2);
    s21_value_reset(&a);
    if (s21_is_equal(y, zero)) {
      _res = DIVISION_BY_0;
    } else {
      char xStr1[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
      char xStr2[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
      char yStr[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

      uint8 sign = S21_GET_SIGN(y);

      s21_decimalToString(xStr1, x);
      s21_decimalToString(yStr, y);
      strcpy(xStr2, xStr1);
      s21_divideStringDecimal(xStr2, yStr);
      strtok(xStr2, ".");
      s21_mulStringDecimal(xStr2, yStr);
      s21_preformatStringDecimal(xStr1, xStr2);
      s21_subStringDecimal(xStr1, xStr2);
      _res =
          s21_processingMathResultAndWriteOutputRegister(result, xStr1, sign);
    }
  } else {
    _res = NULL_POINTER;
  }
  return _res;
}
