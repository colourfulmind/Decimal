#include "my_decimal.h"

int my_from_float_to_decimal(float src, my_decimal *dst) {
  double dsrc = (double)src;
  int sign = 0;
  int error = 0;
  if (dst == NULL || src == -MY_INF || src == MY_INF || src != src) {
    error = 1;
  } else {
    value_reset(dst);
    if (dsrc < 0) {
      dsrc = -dsrc;
      sign = 1;
    }
    char strSrc[512];
    snprintf(strSrc, sizeof(strSrc), "%.7lf", dsrc);
    truncateZeros(strSrc);
    error = processingMathResultAndWriteOutputRegister(dst, strSrc, sign);
  }
  return error ? CONVERTATION_ERROR : CONVERTATION_OK;
}
