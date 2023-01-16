#include "my_decimal.h"

int my_from_decimal_to_int(my_decimal src, int *dst) {
  int error = 0;
  if (dst) {
    *dst = 0;
    for (int bit = 0; bit < 3; ++bit) {
      for (int i = 0; i < 32; ++i) {
        if (get_bit_2Dim(src, bit, i) == 1) {
          *dst += pow(2, i);
        }
      }
    }
    int sign = GET_SIGN(src);
    if (sign) {
      *dst = -*dst;
    }
  } else {
    error = 1;
  }
  return error ? CONVERTATION_ERROR : CONVERTATION_OK;
}
