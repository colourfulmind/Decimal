#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int err = 1;
  const int sign = s21_get_bit_2Dim(src, S21_BYTE_SIGN, S21_BIT_SIGN);
  float res = 0;
  unsigned char exp = s21_getDecimalExp(src);
  if (dst) {
    if (exp <= S21_MAX_EXP) {
      for (int i = 0; i < S21_MANTISSA_LEN; i++) {
        res += s21_get_bit_byIndex(src, i) * pow(2, i);
      }
      res /= pow(10, exp);
      *dst = res * pow(-1, sign);
      err = 0;
    } else {
      *dst = 0;
    }
  }
  return (!err) ? CONVERTATION_OK : CONVERTATION_ERROR;
}
