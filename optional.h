#pragma once
#ifndef SRC_OPTIONAL_H_
#define SRC_OPTIONAL_H_
#include "my_decimal.h"
#include "typedefs.h"

#define BYTE_BIT_LENGTH 8
#define MAX_STRING_CONVERTATION_LENGTH 1000

#define GET_SIGN(x) get_bit_byIndex(x, 127)
#define SET_SIGN(x, sign) set_bit(x, 3, 31, sign)
#define SET_MINUS(x) my_set_bit(x, 3, 31, 1)

#define MAX_UINT 4294967295

// заполняет структуру 0
void value_reset(my_decimal *dst);

// копирует одну структуру в другую
void copy_decimal(my_decimal value, my_decimal *result);

// устанавливает bit бит 32-битного слова word значением value
void set_bit(my_decimal *src, unsigned char word, unsigned char bit,
                 unsigned char value);

// выводит на экран весь децимал в 2чной системе
void print_decimal_bits(my_decimal dst);

// устанавливает в структуру нужную степень
void set_exp(my_decimal *src, int powsrc);

// извлечение значения указанного бита (от 0 до 31) для указанного 32-битного
// слова (от 0 до 3)
int get_bit_2Dim(my_decimal value, uint8 nByte, int nBit);

// извлечение значения указанного бита по индексу бита в структуре (от 0 до 127)
int get_bit_byIndex(my_decimal value, int nBit);

// установка значения указанного бита по индексу бита в структуре (от 0 до 127)
void set_bit_byIndex(my_decimal *value, int nBit, unsigned char bitValue);

// извлечение значения степени при основании 10
unsigned char getDecimalExp(my_decimal value);

// преобразование числа decimal к строковому виду, для читабельного вывода и
// арифметики
void decimalToString(char *strValue, my_decimal value);

// инвертирование строки
void stringReverse(const char *source, char *destination);

// вставка десятичной точки в строковое представление числа
void setPoint(char *strValue, char pointPosition);

// сложение двух чисел в форме строк и сохранение результата в value1
char *addStringDecimal(char *value1, char *value2);

// разность двух чисел в форме строк и сохранение результата в value1
char *subStringDecimal(char *strValue1, const char *strValue2);

// деление двух числе в форме строк и сохранение резултата в x
char *divideStringDecimal(char *x, const char *y);

// предварительное форматирование для выполнения математических операций
void preformatStringDecimal(char *value1, char *value2);

// перевод децимальной строки в число
void stringToDecimal(my_decimal *value, const char *strValue);

// функция отбрасывания нулей после значащих цифр в дробной части
void truncateZeros(char *strValue);

// получение информации о текущей точности числа
int extractPrecision(const char *value);

// удаление точки дробной составляющей
char *dropPrecisionPoint(char *destination, const char *src);

// уменьшаем степень числа
void div_10(my_decimal *d);

// функция проверки значения на допустимый диапазон и экпорт значения из строки
// в децимал
int processingMathResultAndWriteOutputRegister(my_decimal *targetRegister,
                                                   const char *sourceStr,
                                                   uint8 sign);

// произведение двух чисел в форме строк и сохранение результата в value1
int mulStringDecimal(char *strValue1, char *strValue2);

#endif  // SRC_OPTIONAL_H_
