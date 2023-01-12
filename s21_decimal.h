#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_optional.h"
#include "s21_typedefs.h"

#pragma once
#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#define S21_BYTE_SIGN 3
#define S21_BIT_SIGN 31
#define S21_MANTISSA_LEN 96
#define S21_EXP_LEN 8

#define S21_SIZE_BYTES 16
#define S21_SIZE_BITS 32

#define S21_MAX_DECIMAL "79228162514264337593543950335"
#define S21_MIN_DECIMAL "0.0000000000000000000000000001"

#define S21_MAX_EXP 28
#define S21_MIN_EXP 0

#define S21_INF 1.0 / 0.0
#define S21_NAN 0.0 / 0.0

typedef struct {
  int bits[4];
} s21_decimal;

enum code_error_arithmetic_operators {
  ARITHMETIC_OK = 0,
  TOO_LARGE_OR_INF = 1,
  TOO_SMALL_OR_NEG_INF = 2,
  DIVISION_BY_0 = 3,
  NULL_POINTER = 4
};
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

enum code_error_comparison_operators { FALSE = 0, TRUE = 1 };
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

enum code_error_converters { CONVERTATION_OK = 0, CONVERTATION_ERROR = 1 };
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src,
                              s21_decimal *dst);  // check - is broken
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

enum code_error_another { CALCULATION_OK = 0, CALCULATION_ERROR = 1 };
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  // SRC_S21_DECIMAL_H_
