#include "my_decimal.h"

int my_round(my_decimal value, my_decimal *result) {
  int res = CALCULATION_OK;
  if (result) {
    my_decimal one, zeroDotFive, mod_res;

    from_int_to_decimal(1, &one);
    from_int_to_decimal(5, &zeroDotFive);
    set_exp(&zeroDotFive, 1);

    my_mod(value, one, &mod_res);
    SET_SIGN(&mod_res, 0);
    SET_SIGN(&one, GET_SIGN(value));

    my_truncate(value, result);
    if (my_is_greater_or_equal(mod_res, zeroDotFive))
      my_add(*result, one, result);
  } else {
    res = CALCULATION_ERROR;
  }
  return res;
}
