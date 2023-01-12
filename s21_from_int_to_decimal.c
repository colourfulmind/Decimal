#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = CONVERTATION_OK;
  if (dst) {
    s21_value_reset(dst);

    if (src < 0) {
      if (src == INT_MIN) {
        dst->bits[0] = src;
      } else {
        dst->bits[0] = -src;
      }
      S21_SET_SIGN(dst, 1);
    } else {
      dst->bits[0] = src;
    }
  } else {
    flag = CONVERTATION_ERROR;
  }

  return flag;
}
