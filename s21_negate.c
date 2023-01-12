#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result) {
    s21_copy_decimal(value, result);
    S21_GET_SIGN(value) ? S21_SET_SIGN(result, 0) : S21_SET_SIGN(result, 1);
  }
  return (result) ? CALCULATION_OK : CALCULATION_ERROR;
}
