#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int _res = ARITHMETIC_OK;
  if (result) {
    if (s21_is_equal(value_1, value_2)) {
      s21_value_reset(result);
    } else {
      uint8 sign1 = S21_GET_SIGN(value_1);
      uint8 sign2 = S21_GET_SIGN(value_2);
      if (sign1 ^ sign2) {
        // -5 - 10 = -15
        // 5 - -10 = 15
        S21_SET_SIGN(&value_1, 0);
        S21_SET_SIGN(&value_2, 0);
        _res = s21_add(value_1, value_2, result);
        if (_res) {
          if (sign1) {
            _res = (_res == 1) ? 2 : 1;
          }
        }
        S21_SET_SIGN(result, sign1);
      } else {
        // 5 - 10 = -5
        // -5 - -10 = 5
        char strValue1[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
        char strValue2[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
        char *pointer = NULL;

        // приведение к одной разрядной десятиричной маске
        s21_decimal temp1, temp2;
        s21_copy_decimal(value_1, &temp1);
        s21_copy_decimal(value_2, &temp2);
        S21_SET_SIGN(&temp1, 0);
        S21_SET_SIGN(&temp2, 0);
        s21_decimalToString(strValue1, temp1);
        s21_decimalToString(strValue2, temp2);

        s21_preformatStringDecimal(strValue1, strValue2);

        if (strcmp(strValue1, strValue2) > 0) {
          s21_subStringDecimal(strValue1, strValue2);
          pointer = strValue1;
        } else {
          s21_subStringDecimal(strValue2, strValue1);
          pointer = strValue2;
          sign1 ^= 1;
        }
        s21_truncateZeros(pointer);
        _res = s21_processingMathResultAndWriteOutputRegister(result, pointer,
                                                              sign1);
      }
    }
  } else {
    _res = NULL_POINTER;
  }
  return _res;
}
