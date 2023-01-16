#include "my_decimal.h"

int my_is_equal(my_decimal a, my_decimal b) {
  unsigned int expA = getDecimalExp(a);
  unsigned int expB = getDecimalExp(b);
  int res = TRUE;
  int zero = 0;
  if ((expA <= MAX_EXP) && (expB <= MAX_EXP)) {
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

int my_is_not_equal(my_decimal a, my_decimal b) {
  return !my_is_equal(a, b);
}
