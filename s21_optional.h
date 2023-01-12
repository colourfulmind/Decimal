#pragma once
#ifndef SRC_S21_OPTIONAL_H_
#define SRC_S21_OPTIONAL_H_
#include "s21_decimal.h"
#include "s21_typedefs.h"

#define S21_BYTE_BIT_LENGTH 8
#define S21_MAX_STRING_CONVERTATION_LENGTH 1000

#define S21_GET_SIGN(x) s21_get_bit_byIndex(x, 127)
#define S21_SET_SIGN(x, sign) s21_set_bit(x, 3, 31, sign)
#define S21_SET_MINUS(x) s21_set_bit(x, 3, 31, 1)

#define S21_MAX_UINT 4294967295

// заполняет структуру 0
void s21_value_reset(s21_decimal *dst);

// копирует одну структуру в другую
void s21_copy_decimal(s21_decimal value, s21_decimal *result);

// устанавливает bit бит 32-битного слова word значением value
void s21_set_bit(s21_decimal *src, unsigned char word, unsigned char bit,
                 unsigned char value);

// выводит на экран весь децимал в 2чной системе
void s21_print_decimal_bits(s21_decimal dst);

// устанавливает в структуру нужную степень
void s21_set_exp(s21_decimal *src, int powsrc);

// извлечение значения указанного бита (от 0 до 31) для указанного 32-битного
// слова (от 0 до 3)
int s21_get_bit_2Dim(s21_decimal value, uint8 nByte, int nBit);

// извлечение значения указанного бита по индексу бита в структуре (от 0 до 127)
int s21_get_bit_byIndex(s21_decimal value, int nBit);

// установка значения указанного бита по индексу бита в структуре (от 0 до 127)
void s21_set_bit_byIndex(s21_decimal *value, int nBit, unsigned char bitValue);

// извлечение значения степени при основании 10
unsigned char s21_getDecimalExp(s21_decimal value);

// преобразование числа decimal к строковому виду, для читабельного вывода и
// арифметики
void s21_decimalToString(char *strValue, s21_decimal value);

// инвертирование строки
void s21_stringReverse(const char *source, char *destination);

// вставка десятичной точки в строковое представление числа
void s21_setPoint(char *strValue, char pointPosition);

// сложение двух чисел в форме строк и сохранение результата в value1
char *s21_addStringDecimal(char *value1, char *value2);

// разность двух чисел в форме строк и сохранение результата в value1
char *s21_subStringDecimal(char *strValue1, const char *strValue2);

// деление двух числе в форме строк и сохранение резултата в x
char *s21_divideStringDecimal(char *x, const char *y);

// предварительное форматирование для выполнения математических операций
void s21_preformatStringDecimal(char *value1, char *value2);

// перевод децимальной строки в число
void s21_stringToDecimal(s21_decimal *value, const char *strValue);

// функция отбрасывания нулей после значащих цифр в дробной части
void s21_truncateZeros(char *strValue);

// получение информации о текущей точности числа
int s21_extractPrecision(const char *value);

// удаление точки дробной составляющей
char *s21_dropPrecisionPoint(char *destination, const char *src);

// уменьшаем степень числа
void s21_div_10(s21_decimal *d);

// функция проверки значения на допустимый диапазон и экпорт значения из строки
// в децимал
int s21_processingMathResultAndWriteOutputRegister(s21_decimal *targetRegister,
                                                   const char *sourceStr,
                                                   uint8 sign);

// произведение двух чисел в форме строк и сохранение результата в value1
int s21_mulStringDecimal(char *strValue1, char *strValue2);

#endif  // SRC_S21_OPTIONAL_H_
