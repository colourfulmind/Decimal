#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int _res = ARITHMETIC_OK;
  if (result) {
    char _strValue1[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
    char _strValue2[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

    s21_decimalToString(_strValue1, value_1);
    s21_decimalToString(_strValue2, value_2);
    s21_mulStringDecimal(_strValue1, _strValue2);

    uint8 sign = S21_GET_SIGN(value_1) ^ S21_GET_SIGN(value_2);
    _res = s21_processingMathResultAndWriteOutputRegister(result, _strValue1,
                                                          sign);
    if (!_res) S21_SET_SIGN(result, sign);
  } else {
    _res = NULL_POINTER;
  }
  return _res;
}
