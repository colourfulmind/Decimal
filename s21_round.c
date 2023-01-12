#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int res = CALCULATION_OK;
  if (result) {
    s21_decimal one, zeroDotFive, mod_res;

    s21_from_int_to_decimal(1, &one);
    s21_from_int_to_decimal(5, &zeroDotFive);
    s21_set_exp(&zeroDotFive, 1);

    s21_mod(value, one, &mod_res);
    S21_SET_SIGN(&mod_res, 0);
    S21_SET_SIGN(&one, S21_GET_SIGN(value));

    s21_truncate(value, result);
    if (s21_is_greater_or_equal(mod_res, zeroDotFive))
      s21_add(*result, one, result);
  } else {
    res = CALCULATION_ERROR;
  }
  return res;
}
