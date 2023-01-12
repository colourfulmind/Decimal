#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int _res = ARITHMETIC_OK;

  if (result) {
    char sign1 = S21_GET_SIGN(value_1);
    char sign2 = S21_GET_SIGN(value_2);
    if (sign1 ^ sign2) {
      S21_SET_SIGN(&value_1, 0);
      S21_SET_SIGN(&value_2, 0);
      char strValue1[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
      char strValue2[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
      s21_decimalToString(strValue1, value_1);
      s21_decimalToString(strValue2, value_2);
      _res = s21_sub(value_1, value_2, result);
      if (strcmp(strValue1, strValue2) > 0) {
        S21_SET_SIGN(result, sign1);
      } else if (strcmp(strValue1, strValue2) < 0) {
        S21_SET_SIGN(result, sign2);
      }
    } else {
      char strValue1[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
      char strValue2[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
      s21_decimalToString(strValue1, value_1);
      s21_decimalToString(strValue2, value_2);
      // приведение к одной разрядной десятиричной маске
      s21_preformatStringDecimal(strValue1, strValue2);
      s21_addStringDecimal(strValue1, strValue2);
      _res = s21_processingMathResultAndWriteOutputRegister(result, strValue1,
                                                            sign1);
    }
  } else {
    _res = NULL_POINTER;
  }
  return _res;
}
