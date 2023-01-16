#include "my_decimal.h"

int my_truncate(my_decimal value, my_decimal *result) {
  int res = CALCULATION_OK;
  int sign = GET_SIGN(value);
  if (result) {
    value_reset(result);
    int scale = getDecimalExp(value);
    if (scale > 28) {
      res = CALCULATION_ERROR;
    } else {
      char a[MAX_STRING_CONVERTATION_LENGTH] = {0};
      char *pointer;
      decimalToString(a, value);
      pointer = strtok(a, ".");

      if (pointer) {
        stringToDecimal(&value, pointer);
      } else {
        stringToDecimal(&value, a);
      }
    }
    set_exp(&value, 0);
    SET_SIGN(&value, sign);
    copy_decimal(value, result);
  } else {
    res = CALCULATION_ERROR;
  }
  return res;
}
