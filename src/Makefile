CXX = g++
STD = -std=c++17 -g
CXXFLAGS = -Wall -Werror -Wextra
LINKER_OPTIONS = -lgtest
TEST_CC_FILES = ./tests/tests_*.cc
TEST_OBJ_FILES =  tests_*.o
TRASH = $(wildcard *.o *.a *.gc* *.out tests_exe test.info report .clang-format ./headers/*.gch)

all: test

test:
	$(CXX) $(STD) $(CXXFLAGS) $(TEST_CC_FILES) -c
	$(CXX) $(STD) $(CXXFLAGS) $(TEST_OBJ_FILES) -o tests_exe $(LINKER_OPTIONS)
	./tests_exe

gcov_report:
	$(CXX) $(STD) --coverage $(TEST_CC_FILES) $(LINKER_OPTIONS) -o tests_exe
	./tests_exe
	lcov -t "test_exe" -o test.info -c -d . --no-external
	genhtml -o report test.info
	open report/index.html

check_style:
	cp ../materials/linters/.clang-format ../src/headers
	cp ../materials/linters/.clang-format ../src/headers/iterators
	cp ../materials/linters/.clang-format ../src/headers/iterators/list_iterators
	cp ../materials/linters/.clang-format ../src/tests	
	cd headers && clang-format -n -style=google *.h
	cd headers/iterators && clang-format -n -style=google *.h
	cd headers/iterators/list_iterators && clang-format -n -style=google *.h
	cd tests && clang-format -n -style=google *.h

correct_style:
	cp ../materials/linters/.clang-format ../src/headers
	cp ../materials/linters/.clang-format ../src/headers/iterators
	cp ../materials/linters/.clang-format ../src/headers/iterators/list_iterators
	cp ../materials/linters/.clang-format ../src/tests
	cd headers && clang-format -i -style=google *.h
	cd headers/iterators && clang-format -i -style=google *.h
	cd headers/iterators/list_iterators && clang-format -i -style=google *.h	
	cd tests && clang-format -i -style=google *.h

check_mem: clean test
ifeq ($(shell uname -s), Linux)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tests_exe
else
	leaks -atExit -- ./tests_exe
endif

clean:
	rm -rf $(TRASH)
	rm -rf headers/.clang-format
	rm -rf tests/.clang-format
	rm -rf headers/iterators/.clang-format
	rm -rf headers/list_iterators/.clang-format

rebuild: clean all