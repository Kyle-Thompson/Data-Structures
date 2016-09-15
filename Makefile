FLAGS = -Wall -pedantic-errors -Werror -Wfatal-errors -std=c++14
COMP = g++ $(FLAGS) -o

FILES = list_tester

list:	list_tester.cc list.h
	$(COMP) list_tester list_tester.cc

redblack:	redblack_tester.cc redblack_tree.h
	$(COMP) redblack_test redblack_tester.h
