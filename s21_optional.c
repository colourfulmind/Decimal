#include "s21_optional.h"

// заполняет структуру 0
void s21_value_reset(s21_decimal *dst) {
  if (dst) {
    char *pdst = (char *)dst;
    for (int i = 0; i < S21_SIZE_BYTES; i++, pdst++) *pdst = 0;
  }
}

// копирует одну структуру в другую
void s21_copy_decimal(s21_decimal value, s21_decimal *result) {
  if (result) {
    char *pval = (char *)&value, *pres = (char *)result;
    for (int i = 0; i < S21_SIZE_BYTES; i++, pval++, pres++) *pres = *pval;
  }
}

// устанавливает bit бит 32-битного слова word значением value
void s21_set_bit(s21_decimal *src, unsigned char word, unsigned char bit,
                 unsigned char value) {
  if (src) {
    int res = 0;
    res = (value) ? (src->bits[word] |= (1 << bit))
                  : (src->bits[word] &= ~(1 << bit));
    src->bits[word] = res;
  }
}

// выводит на экран весь децимал в 2чной системе
void s21_print_decimal_bits(s21_decimal dst) {
  printf("=========\n");
  printf("s21_print_decimal_bits:\nmastissa mask: \n");
  printf("N word  |  %3i%3c  |  %3i%3c  |  %3i%3c  |  %3i%3c  |\n", 3, ' ', 2,
         ' ', 1, ' ', 0, ' ');
  for (int i = 0; i < 4; i++) {
    printf("u32[%i]: |", 3 - i);
    for (int j = 0; j < 4; j++) {
      printf(" ");
      for (int k = 0; k < 8; k++) {
        printf("%u", s21_get_bit_2Dim(dst, 3 - i, (3 - j) * 8 + 7 - k));
      }
      printf(" |");
    }
    printf("\n");
  }
  char strValue[100] = {0};
  char strValue1[100] = {0};

  char _exp = s21_getDecimalExp(dst);
  s21_decimalToString(strValue, dst);
  char *sign = (S21_GET_SIGN(dst)) ? "-" : "";
  strcpy(strValue1, strValue);
  for (int i = 0; i < 8; i++) {
    s21_set_bit(&dst, 3, i + 16, 0);
  }
  s21_decimalToString(strValue1, dst);
  printf("mantissa value: %s\n", strValue1);
  printf("exponenta: 10^(-%i)\n", _exp);
  // printf("\n\n");
  printf("\nvalue: %s%s\n========\n\n", sign, strValue);
}

// устанавливает в структуру нужную степень
void s21_set_exp(s21_decimal *src, int powsrc) {
  if (src) {
    src->bits[3] = src->bits[3] & (~0u << 24);  // обнуляем биты с 0 до 23
    int num = powsrc;
    for (int i = 112; i < 119; i++) {
      if (num % 2 == 1) {
        s21_set_bit(src, i / 32, i % 32, 1);
      }
      num = num / 2;
    }
  }
}

// извлечение значения указанного бита (от 0 до 31) для указанного 32-битного
// слова (от 0 до 3)
int s21_get_bit_2Dim(s21_decimal value, uint8 nWord, int nBit) {
  int res = -1;  // значение -1 означает ошибку допустимых значений индексов
  if (nWord < (uint8)(sizeof(s21_decimal) / sizeof(value.bits[0])) &&
      (nBit >= 0) &&
      (nBit < (int)(sizeof(value.bits[0]) * S21_BYTE_BIT_LENGTH))) {
    unsigned int temp = value.bits[nWord] & (1 << nBit);
    res = temp >> nBit;
  }
  return res;
}

// извлечение значения указанного бита по индексу бита в структуре (от 0 до 127)
int s21_get_bit_byIndex(s21_decimal value, int nBit) {
  int res = -1;  // -1 означает ошибку допустимых значений индексов
  if ((nBit >= 0) || (nBit < (int)(sizeof(s21_decimal) * sizeof(char) *
                                   S21_BYTE_BIT_LENGTH))) {
    int _nWord = nBit / (int)(sizeof(value.bits[0]) * S21_BYTE_BIT_LENGTH);
    int _nBit = nBit % (int)(sizeof(value.bits[0]) * S21_BYTE_BIT_LENGTH);
    res = s21_get_bit_2Dim(value, _nWord, _nBit);
  }
  return res;
}

void s21_set_bit_byIndex(s21_decimal *value, int nBit, unsigned char bitValue) {
  if (value) {
    if ((nBit >= 0) || (nBit < (int)(sizeof(s21_decimal) * sizeof(char) *
                                     S21_BYTE_BIT_LENGTH))) {
      int _nWord = nBit / (int)(sizeof(value->bits[0]) * S21_BYTE_BIT_LENGTH);
      int _nBit = nBit % (int)(sizeof(value->bits[0]) * S21_BYTE_BIT_LENGTH);
      s21_set_bit(value, _nWord, _nBit, bitValue);
    }
  }
}

// извлечение значения степени при основании 10 из числа decimal
unsigned char s21_getDecimalExp(s21_decimal value) {
  unsigned char res = 0;
  for (int i = 0; i < S21_EXP_LEN; i++) {
    res += s21_get_bit_byIndex(value, i + 112) * pow(2, i);
  }
  return res;
}

// преобразование числа decimal к строковому виду, для читабельного вывода и
// арифметики
void s21_decimalToString(char *strValue, s21_decimal value) {
  if (strValue) {
    unsigned char _exp = s21_getDecimalExp(value);

    // для расчета знчения степени двойки
    char powerOfTwoString[S21_MAX_STRING_CONVERTATION_LENGTH] =
        "1";  // инициализация стартового значением результатом 2^0 = 1
    char powerOfTwoStringInverse[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

    // для расчета итогового значения
    char tempString[S21_MAX_STRING_CONVERTATION_LENGTH] = "0";

    // char tempStringInverse[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

    // подготовка регистра к новой итерации расчета степени двойки
    strcpy(tempString, "0");

    // перебор целочисленной части числа децимал
    for (int i = 0; i < S21_MANTISSA_LEN; i++) {
      uint8 overflowNumber = 0;

      char shortMultiplicator = 2;  // число, на которое производится умножение

      // умножение на 2 предыдущего значения 2^(n-1)

      // перебор десятичных разрядов числа, рассчитанного на предыдущем шаге и
      // умножение на цифру (число одного разряда)
      for (int j = strlen(powerOfTwoString), k = 0; --j >= 0; k++) {
        char decimalSymbol =
            (powerOfTwoString[j] - '0') * ((i) ? shortMultiplicator : 1) +
            overflowNumber;
        overflowNumber = decimalSymbol / 10;
        powerOfTwoStringInverse[k] = (decimalSymbol % 10) + '0';
      }

      // учет переполнения на последнем шаге сложения
      int len = (int)strlen(powerOfTwoStringInverse);
      if (overflowNumber) powerOfTwoStringInverse[len++] = overflowNumber + '0';
      powerOfTwoStringInverse[len] = 0;

      // чтение результата с конца строки
      s21_stringReverse(powerOfTwoStringInverse, powerOfTwoString);

      // если в битовой маске числа, анализируемый бит равен 1, то к
      // накопленному результату прибавить её вес.
      if (s21_get_bit_byIndex(value, i))
        s21_addStringDecimal(tempString, powerOfTwoString);
    }

    // установка точки на нужное место
    s21_setPoint(tempString, _exp);
    s21_truncateZeros(tempString);
    strcpy(strValue, tempString);
  }
}

// переворачивание строки (предназначен для оперирования только символами из
// ASCII таблицы)
void s21_stringReverse(const char *source, char *destination) {
  if (source && destination) {
    int i = (int)strlen(source) - 1;
    int k = 0;
    while (i >= 0 && source[i] && k < S21_MAX_STRING_CONVERTATION_LENGTH - 1) {
      destination[k++] = source[i];
      i--;
    }
    destination[k] = '\0';
  }
}

// установка десятичной точки на требуемую поозицию
void s21_setPoint(char *strValue, char pointPosition) {
  char tempString[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
  if (strValue) {
    if ((int)strlen(strValue) > pointPosition) {
      if (pointPosition > 0) {
        // перепись целой части
        strncpy(tempString, strValue, strlen(strValue) - pointPosition);
        strcat(tempString, ".");

        // перепись дробной части
        strcat(tempString, strValue + strlen(strValue) - pointPosition);
        strcpy(strValue, tempString);

      } else if (pointPosition < 0) {
        // добавить завершающие нули
        strcpy(tempString, strValue);
        for (int i = pointPosition; i < 0; i++) {
          tempString[strlen(tempString) + 1] = 0;
          tempString[strlen(tempString)] = '0';
        }
        strcpy(strValue, tempString);
      }

    } else {
      // добавить ведущие нули
      if (strlen(strValue)) {
        strcpy(tempString, "0.");
        int i = 0;
        for (; i < (int)(pointPosition - strlen(strValue)); i++) {
          tempString[i + 2] = '0';
        }
        strcat(tempString, strValue);
        strcpy(strValue, tempString);
      }
    }
  }
}

// сумма только положительных чисел
char *s21_addStringDecimal(char *value1, char *value2) {
  if (value1 && value2) {
    if (!strcmp(value1, "0")) {
      strcpy(value1, value2);
    } else if (!strcmp(value2, "0")) {
      strcpy(value2, value1);
    } else {
      char value2copy[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
      strcpy(value2copy, value2);
      s21_preformatStringDecimal(value1, value2copy);
      int index = 0;
      while (value1[index] && value1[index] != '.') {
        index++;
      }

      char resultReverseString[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

      uint8 _overflow = 0;
      for (int i = strlen(value1), j = 0; --i >= 0;) {
        if (value1[i] != '.') {
          uint8 temp = ((value1[i] + value2copy[i] - 2 * '0') + _overflow);
          resultReverseString[j] = temp % 10 + '0';
          _overflow = temp / 10;
        } else {
          resultReverseString[j] = '.';
        }
        j++;
      }
      int len = (int)strlen(resultReverseString);
      if (_overflow) {
        resultReverseString[len++] = _overflow + '0';
      }
      resultReverseString[len] = 0;
      s21_stringReverse(resultReverseString, value1);
      s21_truncateZeros(value1);
    }
  }
  return value1;
}

// todo приведение к одной длине целочисленной и дробной частей без учета знака
void s21_preformatStringDecimal(char *value1, char *value2) {
  char t_value[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

  if (value1 && value2) {
    char *p_forIncreasePart = NULL;

    char integerPartValue1[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
    char integerPartValue2[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
    char fractionalPartValue1[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
    char fractionalPartValue2[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

    strcpy(integerPartValue1, strtok(value1, "."));
    char *_fractionalPartValue1 = strtok(NULL, ".");
    if (_fractionalPartValue1)
      strcpy(fractionalPartValue1, _fractionalPartValue1);
    strcpy(integerPartValue2, strtok(value2, "."));
    char *_fractionalPartValue2 = strtok(NULL, ".");
    if (_fractionalPartValue2)
      strcpy(fractionalPartValue2, _fractionalPartValue2);

    int lenIntPrtV1 = strlen(integerPartValue1);
    int lenIntPrtV2 = strlen(integerPartValue2);
    int lenFrcPrtV1 = strlen(fractionalPartValue1);
    int lenFrcPrtV2 = strlen(fractionalPartValue2);

    // приведение целой части числа к одной длине строки
    if (lenIntPrtV1 > lenIntPrtV2) {
      p_forIncreasePart = integerPartValue2;
    } else if (lenIntPrtV1 < lenIntPrtV2) {
      p_forIncreasePart = integerPartValue1;
    }

    if (p_forIncreasePart) {
      for (int i = 0; i < abs(lenIntPrtV1 - lenIntPrtV2); i++) {
        t_value[i] = '0';
        t_value[i + 1] = 0;
      }
    }

    if (p_forIncreasePart) {
      strcat(t_value, p_forIncreasePart);

      strcpy(p_forIncreasePart, t_value);
    }

    strcpy(t_value, "");

    p_forIncreasePart = NULL;

    // приведение дробной части числа к одной длине строки
    if (lenFrcPrtV1 > lenFrcPrtV2) {
      p_forIncreasePart = fractionalPartValue2;
    } else if (lenFrcPrtV1 < lenFrcPrtV2) {
      p_forIncreasePart = fractionalPartValue1;
    }

    if (p_forIncreasePart) {
      for (int i = 0; i < abs(lenFrcPrtV1 - lenFrcPrtV2); i++) {
        t_value[i] = '0';
        t_value[i + 1] = 0;
      }
    }

    if (p_forIncreasePart) {
      strcat(p_forIncreasePart, t_value);
    }

    strcpy(value1, integerPartValue1);
    if (strlen(fractionalPartValue1)) {
      strcat(value1, ".");
      strcat(value1, fractionalPartValue1);
    }

    strcpy(value2, integerPartValue2);
    if (strlen(fractionalPartValue2)) {
      strcat(value2, ".");
      strcat(value2, fractionalPartValue2);
    }
  }
}

// перевод децимальной строки в число (заведомо корректное число, фильтрация на
// уровень выше)
void s21_stringToDecimal(s21_decimal *value, const char *strValue) {
  if (strValue && value) {
    char _strValue[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
    strcpy(_strValue, strValue);
    s21_truncateZeros(_strValue);
    if (!strcmp(_strValue, "0")) {
      s21_value_reset(value);
    } else {
      // извлечения точности во входном числе
      int precision = s21_extractPrecision(_strValue);

      int _sign = 0;
      int index = 0;
      char _temp[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
      char _temp2[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
      char _tempReg[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
      // удаление точки -> перевод к целому числу
      s21_dropPrecisionPoint(_temp, _strValue);
      if (_temp[0] == '-') {
        _sign = 1;
        index++;
      }

      strcpy(_temp2, _temp + index);

      int commonLen = (int)strlen(_temp2);

      int integerPart = (int)strlen(_temp2) - precision;

      if (integerPart > S21_MAX_EXP + 1) {
        strcpy(_tempReg, S21_MAX_DECIMAL);
      } else {
        if (commonLen > S21_MAX_EXP) {
          precision = S21_MAX_EXP - integerPart + 1;
          strncpy(_tempReg, _temp2, S21_MAX_EXP + 1);
          if (_temp2[S21_MAX_EXP + 1] > '4') {
            s21_addStringDecimal(_tempReg, "1");
          }
          if (strcmp(_tempReg, S21_MAX_DECIMAL) > 0) {
            if (precision) {
              char _tempRound[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
              char integer[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
              char *pInteger = &integer[0];
              char fractional[2] = {0};
              char *pFractional = &fractional[0];
              precision--;
              s21_dropPrecisionPoint(_tempRound, _tempReg);
              s21_setPoint(_tempRound, 1);
              pInteger = strtok(_tempRound, ".");
              pFractional = strtok(NULL, ".");
              if (*pFractional - '0' >= 5) {
                s21_addStringDecimal(pInteger, "1");
              }
              strcpy(_tempReg, pInteger);
              s21_setPoint(_tempRound, precision);
            } else {
              strcpy(_tempReg, S21_MAX_DECIMAL);
            }
          }
          s21_truncateZeros(_tempReg);
        } else {
          strcpy(_tempReg, _temp2);
        }
        char _bitmaskRev[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
        char _bitmask[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

        // данные в _temp и index больше не нужны, переменные отдаются на
        // управление сборjv битовой маски
        index = 0;
        while (strcmp(_tempReg, "0")) {  // циклическое деление на 2, до тех
                                         // пор, пока не придем к нулю
          strcpy(_temp, "");
          uint8 remainder = 0;
          for (unsigned long int i = 0; i < strlen(_tempReg);
               i++) {  // перебор десятичных знаков для деления (слева направо)
            uint8 sum = (remainder * 10 + _tempReg[i] - '0');
            uint8 integer = (remainder * 10 + _tempReg[i] - '0') / 2;
            remainder = (integer) ? sum % 2 : sum;
            _temp[i] = integer + '0';
            _temp[i + 1] = 0;
          }

          s21_truncateZeros(_temp);
          strcpy(_tempReg, _temp);
          _bitmaskRev[index++] = (remainder) ? '1' : '0';
        }

        s21_value_reset(value);
        s21_stringReverse(_bitmaskRev, _bitmask);
        strncpy(_bitmask, _bitmaskRev, S21_MANTISSA_LEN);
        for (unsigned long int i = 0; i < strlen(_bitmaskRev);) {
          s21_set_bit_byIndex(value, i, _bitmaskRev[i] - '0');
          i++;
        }
        s21_set_exp(value, precision);
        S21_SET_SIGN(value, _sign);
      }
    }
  }
}

// удаление оконечных нулей (предназначено для работы с числом, у которого есть
// дробная часть)
void s21_truncateZeros(char *strValue) {
  char _tempReversed[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
  char _temp[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
  if (strValue) {
    char *addr;
    if (strchr(strValue, '.')) {
      s21_stringReverse(strValue, _tempReversed);
      addr = &_tempReversed[0];
      // усечение дробной составляющей
      while (*addr && ((*addr == '0') || (*addr == '.'))) {
        if (*addr++ == '.') break;
      }
      strcpy(_temp, addr);
      strcpy(_tempReversed, "");
      s21_stringReverse(_temp, _tempReversed);
      strcpy(strValue, _tempReversed);

      if (strchr(strValue, '.')) {
      } else {
      }
      addr = strValue;
    } else {
      addr = strValue;
    }
    // усечение целочисленной составляющей
    if (strchr(strValue, '.')) {
      while (*addr && ((*addr == '0') || (*addr == '.'))) {
        if (*addr++ == '.') {
          addr -= 2;
          break;
        }
      }
    } else {
      while (*addr && (*addr == '0')) addr++;
      if (!*addr) addr--;
    }

    strcpy(_temp, addr);
    strcpy(strValue, _temp);
  }
}

// получение информации о текущей точности числа
int s21_extractPrecision(const char *value) {
  int precision = 0;
  if (value && strchr(value, '.'))
    precision = (int)strlen(value) - (int)(strchr(value, '.') - value) - 1;
  return precision;
}

// удаление точки дробной составляющей
char *s21_dropPrecisionPoint(char *destination, const char *src) {
  if (destination && src) {
    char _temp[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
    char *pointer = &_temp[0];
    strcpy(_temp, src);
    pointer = strtok(_temp, ".");
    strcpy(destination, pointer);
    pointer = strtok(NULL, ".");
    if (pointer) strcat(destination, pointer);
  }
  return destination;
}

char *s21_divideStringDecimal(char *x, const char *y) {
  // используется, чтобы привести к одному положению десятичной точки (число с
  // плавающей запятой)
  char _x[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
  char _y[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

  // используется, чтобы хранить мантиссу (целочисленное значение)
  char _x2[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
  char _y2[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

  if (x && y) {
    strcpy(_x, x);
    strcpy(_y, y);

    // приводим к одной десятиричной маске
    s21_preformatStringDecimal(_x, _y);

    // удаляем точку, делаем значение целочисленным
    s21_dropPrecisionPoint(_x2, _x);
    s21_dropPrecisionPoint(_y2, _y);

    // отбрасываем лишние нули слева (не нужны при делении и умножении)
    s21_truncateZeros(_x2);
    s21_truncateZeros(_y2);

    // считаем длину мантиссы для делимого и делителя (в символах)
    int lenX = (int)strlen(_x2);
    int lenY = (int)strlen(_y2);

    // длина пересекающейся части мантисс (минимум из двух длин), для поэтапного
    // деления "в столбик"
    int startLen = (lenY > lenX) ? lenX : lenY;

    // индекс последнего символа, соответствующего длине пересекающейся части
    // мантисс
    int index = startLen - 1;

    // индекс символа в результате (с учетом вхождения точки)
    int _resIndex = 0;

    // результат деления
    char _res[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

    // часть числа, соответствующая остатку с предыдущего шага с добавлением
    // следующего десятичного разряда
    char _part[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

    // инициализация _part куском от X, для которого будет вычисляться остаток
    // при делении на _y
    strncpy(_part, _x2, startLen);

    // флаг для однократного добавления точки разделителя в результат
    uint32 pointFlag = 0;

    // пока {не набралось достаточное количество десятичных символов в выводе}
    // && {результат не равен 0}
    while ((index < lenX) || (((int)strlen(_res) <
                               S21_MAX_EXP + 3) /*&& (strcmp(_part, "0"))*/)) {
      char _sub[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
      char _y3[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

      // копирование очередного остатка предыдущего шага с добавлением соседнего
      // разряда
      strcpy(_sub, _part);

      // копирование мантиссы числа Y, для предотвращения ее искажения
      strcpy(_y3, _y2);

      // исключение лишних нулей
      s21_truncateZeros(_y3);
      s21_truncateZeros(_sub);

      // приводим к одной десятиричной маске
      s21_preformatStringDecimal(_sub, _y3);

      // если первое число больше или равно второму, то выполнить деление
      if (strcmp(_sub, _y3) >= 0) {
        // деление
        uint32 divisor = 0;

        // последовательное приближение, начиная со старших разрядов 4-хбитного
        // числа x00-x0F
        for (char i = 3; i >= 0; i--) {
          uint32 step = 1 << i;

          // получение очередного делителя, и оценка его соответствия
          divisor += step;

          // регистры, чтобы не затереть _part и _y2 в результате последующих
          // преобразований
          char _tempX[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
          char _tempY[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
          strcpy(_tempX, _sub);
          strcpy(_tempY, _y3);

          // строковое представление делителя
          char strDivisor[3] = {0};
          snprintf(strDivisor, 3, "%d", divisor);

          // оценка делителя
          s21_mulStringDecimal(_tempY, strDivisor);
          s21_preformatStringDecimal(_tempX, _tempY);
          if (strcmp(_tempX, _tempY) >= 0) {
            // данный делитель подходит, разряд текущей итерации оставляем
          } else {
            divisor -= step;
          }
        }
        _res[_resIndex++] = divisor + '0';
        char strDivisor[3] = {0};
        strcpy(_y3, _y2);
        snprintf(strDivisor, 2, "%d", divisor);
        s21_mulStringDecimal(_y3, strDivisor);
        s21_subStringDecimal(_part, _y3);
      } else {
        _res[_resIndex++] = '0';
      }
      if ((++index >= lenX) && !pointFlag) {
        _res[_resIndex++] = '.';
        pointFlag = 1;
      }
      char nextSymbolForConcatenate = (index < lenX) ? _x2[index] : '0';

      int len = (int)strlen(_part);
      _part[len++] = nextSymbolForConcatenate;
      _part[len] = '\0';
      s21_truncateZeros(_part);
    }
    strcpy(x, _res);
  }
  return x;
}

char *s21_subStringDecimal(char *strValue1, const char *strValue2) {
  // strValue1 всегда больше strValue2. Числа всегда полжоительные
  // отсечка знака идет на уровень выше, как и сортировка чисел при подаче в эту
  // функцию

  if (strValue1 && strValue2) {
    char _temp[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
    strcpy(_temp, strValue2);
    if (!((strlen(strValue1) == strlen(_temp)) &&
          (s21_extractPrecision(strValue1) == s21_extractPrecision(_temp)))) {
      s21_preformatStringDecimal(strValue1, _temp);
    }
    char _tempRev[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
    uint8 overflowSymbol = 0;
    for (int i = strlen(strValue1), k = 0; --i >= 0; k++) {
      char symbol = 0;
      if (strValue1[i] != '.') {
        if (strValue1[i] >= (_temp[i] + overflowSymbol)) {
          symbol = strValue1[i] - _temp[i] - overflowSymbol;
          overflowSymbol = 0;
        } else {
          symbol = 10 + strValue1[i] - _temp[i] - overflowSymbol;
          overflowSymbol = 1;
        }
        _tempRev[k] = symbol + '0';
        _tempRev[k + 1] = '\0';
      } else {
        _tempRev[k] = '.';
        _tempRev[k + 1] = '\0';
      }
    }
    strcpy(strValue1, "");
    s21_stringReverse(_tempRev, strValue1);
  }
  return strValue1;
}

// функция проверки значения на допустимый диапазон и экпорт значения из строки
// в децимал
int s21_processingMathResultAndWriteOutputRegister(s21_decimal *targetRegister,
                                                   const char *sourceStr,
                                                   uint8 sign) {
  int _res = CALCULATION_OK;
  char temp1[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
  char temp2[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
  char temp3[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
  char tempMax[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
  char tempMin[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};

  // проверка на сверхбольшое число по модулю
  strcpy(temp1, sourceStr);
  strcpy(temp2, sourceStr);
  strcpy(temp3, sourceStr);
  strcpy(tempMax, S21_MAX_DECIMAL);
  strcpy(tempMin, S21_MIN_DECIMAL);

  s21_preformatStringDecimal(temp1, tempMax);
  s21_truncateZeros(temp2);
  s21_preformatStringDecimal(temp3, tempMin);
  if (strcmp(temp1, tempMax) > 0) {
    // превышено максимальное возможное значение
    _res = (sign) ? TOO_SMALL_OR_NEG_INF : TOO_LARGE_OR_INF;
    strcpy(temp1, S21_MAX_DECIMAL);
    if (targetRegister) {
      s21_stringToDecimal(targetRegister, temp1);
      S21_SET_SIGN(targetRegister, sign);
    }
  } else if (!strcmp(temp2, "0")) {
    // равно нулю
    strcpy(temp1, "0");
    if (targetRegister) s21_stringToDecimal(targetRegister, temp1);
  } else if (strcmp(temp3, tempMin) < 0) {
    // превышено минимальное возможное значение
    _res = TOO_SMALL_OR_NEG_INF;
    strcpy(temp1, "0");
    if (targetRegister) s21_stringToDecimal(targetRegister, temp1);
  }
  if (targetRegister && !_res) {
    s21_stringToDecimal(targetRegister, temp1);  // todo
    s21_set_bit(targetRegister, 3, 31, sign);
  }
  return _res;
}

int s21_mulStringDecimal(char *strValue1, char *strValue2) {
  int _res = CALCULATION_OK;
  char _strTemp1[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
  char _strTemp2[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
  if (strValue1 && strValue2) {
    char precisionValue1 = s21_extractPrecision(strValue1);
    char precisionValue2 = s21_extractPrecision(strValue2);
    s21_dropPrecisionPoint(_strTemp1, strValue1);
    s21_dropPrecisionPoint(_strTemp2, strValue2);
    s21_truncateZeros(_strTemp1);
    s21_truncateZeros(_strTemp2);
    strcpy(strValue1, "0");

    if (strcmp(_strTemp1, "0") && strcmp(_strTemp2, "0")) {
      // перебор разрядов, начиная с младшего, второго множителя; k - счетчик
      // сдвигающих нулей
      for (int j = strlen(_strTemp2), k = 0; --j >= 0; k++) {
        if (_strTemp2[j] != '0') {
          uint8 overflowNumber = 0;
          char tempRegisterRev[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
          char tempRegister[S21_MAX_STRING_CONVERTATION_LENGTH] = {0};
          // перебор разрядов, начиная с младшего, первого множителя
          for (int i = strlen(_strTemp1), m = 0; --i >= 0; m++) {
            char decimalSymbol =
                (_strTemp1[i] - '0') * (_strTemp2[j] - '0') + overflowNumber;
            overflowNumber = decimalSymbol / 10;
            tempRegisterRev[m] = (decimalSymbol % 10) + '0';
          }
          // учет переполнения на последнем шаге сложения
          int len = (int)strlen(tempRegisterRev);
          if (overflowNumber) tempRegisterRev[len++] = overflowNumber + '0';
          tempRegisterRev[len] = 0;

          // чтение результата с конца строки
          s21_stringReverse(tempRegisterRev, tempRegister);

          for (int n = 0; n < k; n++) {
            strcat(tempRegister, "0");
          }

          s21_addStringDecimal(strValue1, tempRegister);
        }
      }
      s21_setPoint(strValue1, precisionValue1 + precisionValue2);
      s21_truncateZeros(strValue1);
    }
  }
  return _res;
}
