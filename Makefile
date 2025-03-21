##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile configuration
##

SRC = \
	$(shell find . -name "*.cpp" \
		-not -path "./tests/*" \
		-not -path "./bonus/*"\
		-not -path "./resources/*")

NAME = nanotekspice

FLAGS = -std=c++20 -Wall -Wextra -Werror

all:
	g++ -o $(NAME) $(SRC) $(FLAGS)

clean:
	rm -f coding-style-reports.log
	rm -f *.gcda && rm -f *.gcno && rm -f *.gcov

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests

re: fclean all

tests_run:
	g++ -o unit_tests tests/*.cpp \
		Special/*.cpp Elementary/*.cpp Gates/*.cpp \
		Advanced/*.cpp Parsing/*.cpp Shell/*.cpp \
		Component.cpp Circuit.cpp -lcriterion --coverage
	./unit_tests

coverage: tests_run
	gcovr --exclude tests/
	gcovr --exclude tests/ --txt-metric branch
	make clean

.PHONY: all clean fclean re tests_run coverage
