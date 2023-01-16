#include "my_decimal.h"

int my_mod(my_decimal x, my_decimal y, my_decimal *result) {
  int _res = ARITHMETIC_OK;
  if (result) {
    my_decimal zero, z, z2, a;
    value_reset(&zero);
    value_reset(&z);
    value_reset(&z2);
    value_reset(&a);
    if (my_is_equal(y, zero)) {
      _res = DIVISION_BY_0;
    } else {
      char xStr1[MAX_STRING_CONVERTATION_LENGTH] = {0};
      char xStr2[MAX_STRING_CONVERTATION_LENGTH] = {0};
      char yStr[MAX_STRING_CONVERTATION_LENGTH] = {0};

      uint8 sign = GET_SIGN(y);

      decimalToString(xStr1, x);
      decimalToString(yStr, y);
      strcpy(xStr2, xStr1);
      divideStringDecimal(xStr2, yStr);
      strtok(xStr2, ".");
      mulStringDecimal(xStr2, yStr);
      preformatStringDecimal(xStr1, xStr2);
      subStringDecimal(xStr1, xStr2);
      _res =
          processingMathResultAndWriteOutputRegister(result, xStr1, sign);
    }
  } else {
    _res = NULL_POINTER;
  }
  return _res;
}
