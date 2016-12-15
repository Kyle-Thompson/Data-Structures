FLAGS = -Wall -pedantic-errors -Werror -Wfatal-errors -std=c++14
COMP = g++ $(FLAGS) -o

FILES = list_tester

all:	list redblack algorithm

list:	test_list.cc list.h
	$(COMP) test_list test_list.cc

redblack:	test_redblack_tree.cc redblack_tree.h
	$(COMP) redblack_test test_redblack_tree.cc

algorithm:	test_alg.cc algorithm.h
	$(COMP) test_alg test_alg.cc
