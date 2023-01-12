#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = CALCULATION_OK;
  int sign = S21_GET_SIGN(value);
  if (result) {
    s21_value_reset(result);
    int scale = s21_getDecimalExp(value);
    if (scale > 28) {
      res = CALCULATION_ERROR;
    } else {
      char a[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
      char *pointer;
      s21_decimalToString(a, value);
      pointer = strtok(a, ".");

      if (pointer) {
        s21_stringToDecimal(&value, pointer);
      } else {
        s21_stringToDecimal(&value, a);
      }
    }
    s21_set_exp(&value, 0);
    S21_SET_SIGN(&value, sign);
    s21_copy_decimal(value, result);
  } else {
    res = CALCULATION_ERROR;
  }
  return res;
}
