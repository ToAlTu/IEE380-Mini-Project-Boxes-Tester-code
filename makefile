EXEC = BoxProb
CC = g++
CFLAGS = -c -Wall
#
$(EXEC) :BoxesProblem.o
	$(CC) -o $(EXEC) BoxesProblem.o
#
BoxesProblem.o :BoxesProblem.cpp
	$(CC) $(CFLAGS) BoxesProblem.cpp