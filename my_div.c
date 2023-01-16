#include "my_decimal.h"

int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int _res = CALCULATION_OK;
  my_decimal zero;
  value_reset(&zero);
  if (my_is_equal(value_2, zero)) {
    if (result) {
      value_reset(result);
      _res = DIVISION_BY_0;
    } else {
      _res = NULL_POINTER;
    }
  } else {
    uint8 sign = GET_SIGN(value_1) ^ GET_SIGN(value_2);
    SET_SIGN(&value_1, 0);
    SET_SIGN(&value_2, 0);
    char x[MAX_STRING_CONVERTATION_LENGTH] = {0};
    char y[MAX_STRING_CONVERTATION_LENGTH] = {0};
    decimalToString(x, value_1);
    decimalToString(y, value_2);
    divideStringDecimal(x, y);
    _res = processingMathResultAndWriteOutputRegister(result, x, sign);
  }
  return _res;
}
