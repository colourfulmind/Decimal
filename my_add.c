#include "my_decimal.h"

int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int _res = ARITHMETIC_OK;

  if (result) {
    char sign1 = GET_SIGN(value_1);
    char sign2 = GET_SIGN(value_2);
    if (sign1 ^ sign2) {
      SET_SIGN(&value_1, 0);
      SET_SIGN(&value_2, 0);
      char strValue1[MAX_STRING_CONVERTATION_LENGTH] = {0};
      char strValue2[MAX_STRING_CONVERTATION_LENGTH] = {0};
      decimalToString(strValue1, value_1);
      decimalToString(strValue2, value_2);
      _res = my_sub(value_1, value_2, result);
      if (strcmp(strValue1, strValue2) > 0) {
        SET_SIGN(result, sign1);
      } else if (strcmp(strValue1, strValue2) < 0) {
        SET_SIGN(result, sign2);
      }
    } else {
      char strValue1[MAX_STRING_CONVERTATION_LENGTH] = {0};
      char strValue2[MAX_STRING_CONVERTATION_LENGTH] = {0};
      decimalToString(strValue1, value_1);
      decimalToString(strValue2, value_2);
      // приведение к одной разрядной десятиричной маске
      preformatStringDecimal(strValue1, strValue2);
      addStringDecimal(strValue1, strValue2);
      _res = processingMathResultAndWriteOutputRegister(result, strValue1,
                                                            sign1);
    }
  } else {
    _res = NULL_POINTER;
  }
  return _res;
}
