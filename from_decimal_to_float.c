#include "my_decimal.h"

int my_from_decimal_to_float(my_decimal src, float *dst) {
  int err = 1;
  const int sign = get_bit_2Dim(src, BYTE_SIGN, BIT_SIGN);
  float res = 0;
  unsigned char exp = getDecimalExp(src);
  if (dst) {
    if (exp <= MAX_EXP) {
      for (int i = 0; i < MANTISSA_LEN; i++) {
        res += get_bit_byIndex(src, i) * pow(2, i);
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
