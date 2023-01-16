#include "my_decimal.h"

int my_from_int_to_decimal(int src, my_decimal *dst) {
  int flag = CONVERTATION_OK;
  if (dst) {
    value_reset(dst);

    if (src < 0) {
      if (src == INT_MIN) {
        dst->bits[0] = src;
      } else {
        dst->bits[0] = -src;
      }
      SET_SIGN(dst, 1);
    } else {
      dst->bits[0] = src;
    }
  } else {
    flag = CONVERTATION_ERROR;
  }

  return flag;
}
