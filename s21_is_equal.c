#include "s21_decimal.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  unsigned int expA = s21_getDecimalExp(a);
  unsigned int expB = s21_getDecimalExp(b);
  int res = TRUE;
  int zero = 0;
  if ((expA <= S21_MAX_EXP) && (expB <= S21_MAX_EXP)) {
    for (int i = 0; i < 4; i++) {
      res &= (a.bits[i] == b.bits[i]);
      if (i < 3 && a.bits[i] == 0 && b.bits[i] == 0) zero++;
    }
    if (zero == 3) res = TRUE;
  } else {
    res = FALSE;
  }
  return res;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_equal(a, b);
}
