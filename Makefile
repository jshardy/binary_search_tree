CC = g++
CLFAGS = -g -Wall

DEPS = BST_Node.h BST_Tree.h
PROG = test

all: $(PROG)

bst_main.o: test.cpp $(DEPS)
	$(CC) -c $< $(CLFAGS)

bst_main: test.o
	$(CC) -o $@ $^ $(CLFAGS)

compress: clean
	tar -czvf $(PROG).tar.gz *

clean:
	rm -rf $(PROG) *.o *.dSYM
