#include "my_decimal.h"

int my_floor(my_decimal value, my_decimal *result) {
  int res = CALCULATION_OK;
  int sign = GET_SIGN(value);
  if (result) {
    value_reset(result);
    *result = value;
    int precision = getDecimalExp(value);
    my_truncate(value, result);
    if (sign && precision) {
      my_decimal one = {{1, 0, 0, 0}};
      res = my_sub(*result, one, result);
    }
  } else {
    res = CALCULATION_ERROR;
  }
  return res;
}
