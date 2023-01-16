#include "my_decimal.h"

// функция меньше
int my_is_less(my_decimal value_1, my_decimal value_2) {
  int _res = FALSE;
  my_decimal sub;
  if (my_is_equal(value_1, value_2)) {
    _res = FALSE;
  } else {
    int sign_1 = GET_SIGN(value_1);
    int sign_2 = GET_SIGN(value_2);
    if (sign_1 && !sign_2)
      _res = TRUE;
    else if (!sign_1 && sign_2)
      _res = FALSE;
    else {
      int res_sub = my_sub(value_1, value_2, &sub);
      if (res_sub == ARITHMETIC_OK && GET_SIGN(sub) == 1) _res = TRUE;
    }
  }
  return _res;
}

// функция меньше или равно
int my_is_less_or_equal(my_decimal value_1, my_decimal value_2) {
  int _res = FALSE;
  if (my_is_equal(value_1, value_2)) {
    _res = TRUE;
  } else {
    _res = my_is_less(value_1, value_2);
  }
  return _res;
}

// функция больше
int my_is_greater(my_decimal value_1, my_decimal value_2) {
  int _res = !my_is_less_or_equal(value_1, value_2);
  return _res;
}

// функция больше или равно
int my_is_greater_or_equal(my_decimal value_1, my_decimal value_2) {
  int _res = !my_is_less(value_1, value_2);
  return _res;
}
