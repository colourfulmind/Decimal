#---------------Опции-----------------------
# Компилятор
CC=gcc

# Дополнительные флаги сборки
CFLAGS=-Wextra -Wall -Werror# -fsanitize=address -Wextra -Wall -Werror #-Wall -Werror -Wextra -std=c11

# Используемый стандарт Си
CSTANDARD=-std=c11 -pedantic

# Флаг для отладки
DEBUG=-g

# Исходные файлы
SRC_FILES=s21_*.c

# Заголовочные файлы
HDR_FILES=s21_*.h

# Имя собираемой статической библиотеки
LIBNAME=s21_decimal.a

# Тип операционной системы
TYPE_OS=$(shell uname -s);

# Флаги для покрытияs
GCOV_FLAGS=-fprofile-arcs -ftest-coverage #-lgcov

#Флаги для тестов
CHECK_FLAGS_MACOS=-lcheck -lm -lpthread

#Флаги для тестов линукс
CHECK_FLAGS_LINUX=-lpthread -lcheck_pic -lrt -lm -lsubunit

#Названия переменых
NAME = test
REPORT_NAME = report

#-------------------------------------------

SRCS = s21_add.c\
	s21_sub.c\
	s21_mul.c\
	s21_div.c\
	s21_mod.c\
	s21_is_less.c\
	s21_is_equal.c\
	s21_from_int_to_decimal.c\
	s21_from_float_to_decimal.c\
	s21_from_decimal_to_int.c\
	s21_from_decimal_to_float.c\
	s21_floor.c\
	s21_round.c\
	s21_truncate.c\
	s21_negate.c\
	s21_optional.c

TEST_FILE = test.c

OBJST = $(SRCS:.c=.o)

all: clean s21_decimal.a test gcov_report

objs: $(SRCS)
	$(CC) $(CFLAGS) $(CSTANDARD) -c $(SRCS)

checkmk:
	checkmk test.mkcheck > $(TEST_FILE)

s21_decimal.a: objs
	ar rc $(LIBNAME) $(OBJST)
	ranlib $(LIBNAME)

# Тесты
test: checkmk test_$(TYPE_OS)

test_Darwin: $(OBJS) $(TEST_FILE)
	$(CC) $(DEBUG) $(CSTANDARD) $(SRCS) $(TEST_FILE) $(CHECK_FLAGS_MACOS)  -coverage -o $(NAME)
	./$(NAME)

test_Linux:
	$(CC) $(DEBUG) $(CSTANDARD) $(SRCS) $(TEST_FILE) $(CHECK_FLAGS_LINUX)  -coverage -o $(NAME)
	./$(NAME)

# отчет по покрытию тестами
gcov_report: gcov_$(TYPE_OS)

gcov_Darwin:
	$(CC) $(DEBUG) $(CSTANDARD) $(SRCS) $(TEST_FILE) $(CHECK_FLAGS_MACOS) $(GCOV_FLAGS) -o $(NAME)
	./$(NAME)
	lcov -t "gcov_report" -o tests.info -c -d .
	genhtml -o $(REPORT_NAME) tests.info
	open report/src/index.html
	rm $(NAME)

gcov_Linux:
	$(CC) $(DEBUG) $(CSTANDARD) $(SRCS) $(TEST_FILE) $(CHECK_FLAGS_LINUX) $(GCOV_FLAGS) -o $(NAME)
	./$(NAME)
	lcov -t "gcov_report" -o tests.info -c -d .
	genhtml -o $(REPORT_NAME) tests.info
	open report/src/index.html
	rm $(NAME)

# проверка на утечки памяти
test_leaks: test_leaks_$(TYPE_OS)

test_leaks_Darwin: test
	leaks -atExit -- ./$(NAME) | grep LEAK:

test_leaks_Linux: test
	valgrind --log-file="out_valgrind.txt" --leak-check=full -v ./$(NAME) 

# Проверка стиля
style_check:
	clang-format -n *.c* *.h*

clean:
	rm -rf *.o *.a test *.html *.css *.out *.gcda *.gcno *.gcov *.log *.dSYM *.info
	rm -rf $(REPORT_NAME) $(OBJST)
	rm -rf $(TEST_FILE)

rebuild:
	clean all
