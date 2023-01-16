#include "my_decimal.h"

int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int _res = ARITHMETIC_OK;
  if (result) {
    char _strValue1[MAX_STRING_CONVERTATION_LENGTH] = {0};
    char _strValue2[MAX_STRING_CONVERTATION_LENGTH] = {0};

    decimalToString(_strValue1, value_1);
    decimalToString(_strValue2, value_2);
    mulStringDecimal(_strValue1, _strValue2);

    uint8 sign = GET_SIGN(value_1) ^ GET_SIGN(value_2);
    _res = processingMathResultAndWriteOutputRegister(result, _strValue1,
                                                          sign);
    if (!_res) SET_SIGN(result, sign);
  } else {
    _res = NULL_POINTER;
  }
  return _res;
}
