#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  double dsrc = (double)src;
  int sign = 0;
  int error = 0;
  if (dst == NULL || src == -S21_INF || src == S21_INF || src != src) {
    error = 1;
  } else {
    s21_value_reset(dst);
    if (dsrc < 0) {
      dsrc = -dsrc;
      sign = 1;
    }
    char strSrc[512];
    snprintf(strSrc, sizeof(strSrc), "%.7lf", dsrc);
    s21_truncateZeros(strSrc);
    error = s21_processingMathResultAndWriteOutputRegister(dst, strSrc, sign);
  }
  return error ? CONVERTATION_ERROR : CONVERTATION_OK;
}
