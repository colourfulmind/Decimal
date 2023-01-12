#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  if (dst) {
    *dst = 0;
    for (int bit = 0; bit < 3; ++bit) {
      for (int i = 0; i < 32; ++i) {
        if (s21_get_bit_2Dim(src, bit, i) == 1) {
          *dst += pow(2, i);
        }
      }
    }
    int sign = S21_GET_SIGN(src);
    if (sign) {
      *dst = -*dst;
    }
  } else {
    error = 1;
  }
  return error ? CONVERTATION_ERROR : CONVERTATION_OK;
}
