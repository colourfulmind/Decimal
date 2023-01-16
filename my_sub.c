#include "my_decimal.h"

int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int _res = ARITHMETIC_OK;
  if (result) {
    if (my_is_equal(value_1, value_2)) {
      value_reset(result);
    } else {
      uint8 sign1 = GET_SIGN(value_1);
      uint8 sign2 = GET_SIGN(value_2);
      if (sign1 ^ sign2) {
        SET_SIGN(&value_1, 0);
        SET_SIGN(&value_2, 0);
        _res = my_add(value_1, value_2, result);
        if (_res) {
          if (sign1) {
            _res = (_res == 1) ? 2 : 1;
          }
        }
        SET_SIGN(result, sign1);
      } else {
        char strValue1[MAX_STRING_CONVERTATION_LENGTH] = {0};
        char strValue2[MAX_STRING_CONVERTATION_LENGTH] = {0};
        char *pointer = NULL;

        // приведение к одной разрядной десятиричной маске
        my_decimal temp1, temp2;
        copy_decimal(value_1, &temp1);
        copy_decimal(value_2, &temp2);
        SET_SIGN(&temp1, 0);
        SET_SIGN(&temp2, 0);
        decimalToString(strValue1, temp1);
        decimalToString(strValue2, temp2);

        preformatStringDecimal(strValue1, strValue2);

        if (strcmp(strValue1, strValue2) > 0) {
          subStringDecimal(strValue1, strValue2);
          pointer = strValue1;
        } else {
          subStringDecimal(strValue2, strValue1);
          pointer = strValue2;
          sign1 ^= 1;
        }
        truncateZeros(pointer);
        _res = processingMathResultAndWriteOutputRegister(result, pointer,
                                                              sign1);
      }
    }
  } else {
    _res = NULL_POINTER;
  }
  return _res;
}
