CC=g++
CFLAGS=-g -Wall

all: # make library


test: tictactoe_test.run
	./$<

tictactoe_test.run: tictactoe.o tictactoe_test.o
	$(CC) $(CFLAGS) $^ -o $@

tictactoe_test.o: tictactoe_test.cpp
	$(CC) $(CFLAGS) -c $<

tictactoe.o: tictactoe.cpp tictactoe.h
	$(CC) $(CFLAGS) -c $<



zip: tictactoe_test.cpp tictactoe.cpp tictactoe.h Makefile
	zip tictactoe.zip $^


.Phony: clean
clean:
	@rm -f *.run *.o *.zip
