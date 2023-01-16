#include "my_decimal.h"

int my_negate(my_decimal value, my_decimal *result) {
  if (result) {
    copy_decimal(value, result);
    GET_SIGN(value) ? SET_SIGN(result, 0) : SET_SIGN(result, 1);
  }
  return (result) ? CALCULATION_OK : CALCULATION_ERROR;
}
