#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "optional.h"
#include "typedefs.h"

#pragma once
#ifndef SRC_MY_DECIMAL_H_
#define SRC_MY_DECIMAL_H_

#define BYTE_SIGN 3
#define BIT_SIGN 31
#define MANTISSA_LEN 96
#define EXP_LEN 8

#define SIZE_BYTES 16
#define SIZE_BITS 32

#define MAX_DECIMAL "79228162514264337593543950335"
#define MIN_DECIMAL "0.0000000000000000000000000001"

#define MAX_EXP 28
#define MIN_EXP 0

#define MY_INF 1.0 / 0.0
#define MY_NAN 0.0 / 0.0

typedef struct {
  int bits[4];
} my_decimal;

enum code_error_arithmetic_operators {
  ARITHMETIC_OK = 0,
  TOO_LARGE_OR_INF = 1,
  TOO_SMALL_OR_NEG_INF = 2,
  DIVISION_BY_0 = 3,
  NULL_POINTER = 4
};
int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_mod(my_decimal value_1, my_decimal value_2, my_decimal *result);

enum code_error_comparison_operators { FALSE = 0, TRUE = 1 };
int my_is_less(my_decimal value_1, my_decimal value_2);
int my_is_less_or_equal(my_decimal value_1, my_decimal value_2);
int my_is_greater(my_decimal value_1, my_decimal value_2);
int my_is_greater_or_equal(my_decimal value_1, my_decimal value_2);
int my_is_equal(my_decimal value_1, my_decimal value_2);
int my_is_not_equal(my_decimal value_1, my_decimal value_2);

enum code_error_converters { CONVERTATION_OK = 0, CONVERTATION_ERROR = 1 };
int from_int_to_decimal(int src, my_decimal *dst);
int from_float_to_decimal(float src,
                              my_decimal *dst);  // check - is broken
int from_decimal_to_int(my_decimal src, int *dst);
int from_decimal_to_float(my_decimal src, float *dst);

enum code_error_another { CALCULATION_OK = 0, CALCULATION_ERROR = 1 };
int my_floor(my_decimal value, my_decimal *result);
int my_round(my_decimal value, my_decimal *result);
int my_truncate(my_decimal value, my_decimal *result);
int my_negate(my_decimal value, my_decimal *result);

#endif  // SRC_MY_DECIMAL_H_
